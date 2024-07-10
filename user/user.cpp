#include <conio.h>  // for _getch()
#include <ctype.h> // for toupper()
#include <windows.h>  // for Sleep()
#include <cassert>  // for assert()
#include <process.h>  // for _endthreadex()
#include <iostream>
#include <fstream>  // for ofstream


#include "..\calculator.h"
#include "user.h"
#include "input_info.h"


using namespace std;


extern string log_file_name;
extern ofstream program_info_msg;


/********************  change mode according to user input  ***********************/


/**
 * @brief thread waiting for user inputs
 * @param pinput_info input_info
 */
unsigned __stdcall user_input_thread( void *__input_info )
{

    // cast input_info from "void *" to "pinput_info"
    pinput_info input_info = static_cast<pinput_info>(__input_info);


    program_info_msg << "user input thread start\n";


    // before user enter a key, key_input should be under default mode
    char key_input = 'D';

    while ( !input_info->terminate_program_TF )
    {
        key_input = _getch();
        key_input = toupper( key_input );

        switch ( key_input )
        {
            case 'E' :
                input_info->terminate_program_TF = true;
                break;

            case 'C' :
                program_info_msg << "program continue\n";
                input_info->mode = 'D';
                break;

            case 'P' :
                program_info_msg << "program paused\n";
                input_info->mode = 'P';
                break;

            case 'I' :
                program_info_msg << "insert mode start\n";
                input_info->mode = 'I';
                insert_mode( input_info );
                break;

            case 'W' : case 'A' : case 'T' :
                program_info_msg << "***ERROR: enter \'W\' or \'A\' or \'T\'"
                                 << " but not in insert mode***\n";
                break;

            default :
                program_info_msg << "***ERROR: invalid input***\n";
                break;
        }
    }
    program_info_msg << "user input thread end\n";
    _endthreadex( 0 );
    return 0;
}


/******************************  insertion thread  ********************************/


/**
 * @brief thread waiting for user inputs in insert_mode
 * @param pinput_info input_info
 */
unsigned __stdcall insertion_thread( void *__input_info )
{

    // cast input_info from "void *" to "pinput_info"
    pinput_info input_info = static_cast<pinput_info>(__input_info);


    program_info_msg << "insertion thread start\n";


    // copy data from input_info
    pphysical_info physical_info = input_info->physical_info;
    Screen screen = input_info->screen;
    Screen tmp_screen = screen;
    screen_input_name name;


    char key_input;

    while ( (!input_info->terminate_program_TF) && (!input_info->terminate_insertion_TF) )
    {
        key_input = _getch();
        key_input = toupper( key_input );
        double change_value = 0.0;

        switch ( key_input )
        {
            case 'W' :
                input_info->name = OMEGA;
                program_info_msg << "inserting omega\n";
                cin >> change_value;
                input_info->name = NONE;

                // user input is valid for OMEGA
                if ( cin ) {
                    physical_info->omega = change_value;
                }
                else {
                    program_info_msg << "***ERROR: OMEGA inserted is invalid***\n";
                    cin.clear();
                    cin.ignore( 1024, '\n' );
                }
                break;
            
            case 'A' :
                input_info->name = ALPHA;
                program_info_msg << "inserting alpha\n";
                cin >> change_value;
                input_info->name = NONE;

                // user input is valid for ALPHA
                if ( cin ) {
                    physical_info->alpha = change_value;
                }
                else {
                    program_info_msg << "***ERROR: ALPHA inserted is invalid***\n";
                    cin.clear();
                    cin.ignore( 1024, '\n' );
                }
                break;

            case 'L' :
                input_info->name = LENGTH;
                program_info_msg << "inserting length\n";
                cin >> change_value;
                input_info->name = NONE;

                // user input is valid for LENGTH (the type is double),
                // but not assure the input is not 0
                if ( cin ) {

                    // length can't be 0
                    if ( change_value != 0 ) {
                        physical_info->length = change_value;
                    }

                    // when length is 0
                    else {
                        program_info_msg << "***ERROR: length inserted is 0***\n";
                    }
                }
                else {
                    program_info_msg << "***ERROR: LENGTH inserted is invalid***\n";
                    cin.clear();
                    cin.ignore( 1024, '\n' );
                }
                break;
            
            case 'M' :
                input_info->name = MASS;
                program_info_msg << "inserting mass\n";
                cin >> change_value;
                input_info->name = NONE;

                // user input is valid for MASS
                if ( cin ) {
                    physical_info->mass = change_value;
                }
                else {
                    program_info_msg << "***ERROR: MASS inserted is invalid***\n";
                    cin.clear();
                    cin.ignore( 1024, '\n' );
                }
                break;

            case 'T' :
                input_info->name = THETA;
                program_info_msg << "inserting theta\n";
                cin >> change_value;
                input_info->name = NONE;

                // user input is valid for THETA
                if ( cin ) {
                    physical_info->theta = change_value;
                }
                else {
                    program_info_msg << "***ERROR: THETA inserted is invalid***\n";
                    cin.clear();
                    cin.ignore( 1024, '\n' );
                }


            // jump out of insert_mode
            case 'C' :
                input_info->terminate_insertion_TF = true;
                input_info->name = NONE;
                break;
            

            // jump out of insert_mode and terminate the program
            case 'E' :
                input_info->terminate_insertion_TF = true;
                input_info->terminate_program_TF = true;
                input_info->name = NONE;
                break;

            default:
                program_info_msg << "***ERROR: input in insert_mode is invalid***\n";
                break;
        }
    }

    // change mode to default_mode when insertion is done
    input_info->mode = 'D';


    program_info_msg << "insertion thread end\n";
    _endthreadex( 0 );
    return 0;
}


/***************************  insert mode  *********************************************/


/**
 * @brief insert_mode
 * @param pinput_info input_info
 */
void insert_mode( pinput_info input_info )
{

    // copy data from input_info
    Screen screen = input_info->screen;
    Screen tmp_screen = screen;


    // create a thread waiting user inputs in insert_mode
    unsigned threadID;
    HANDLE hthread = (HANDLE)_beginthreadex(
        NULL, 0, insertion_thread, input_info, 0, &threadID
    );


    // while waiting user input, show screen in default way
    while ( !input_info->terminate_insertion_TF )
    {
        default_mode( input_info );

        //lower the frequency of updating screen
        Sleep( 10L );
    }

    
    // set up terminate_insertion_TF to 'false' after insertion is done
    input_info->terminate_insertion_TF = false;
}

/********************************  pause mode  *****************************************/


/**
 * @brief pause_mode, show screen but not update the values of
 * @brief physical variables
 * 
 * @param pinput_info input_info
 */
void pause_mode( pinput_info input_info )
{
    draw_and_show_screen( input_info );   
}


/***********************************  default mode  **********************************/


/**
 * @brief default_mode, update values of physical variables
 * @brief and show screen
 * 
 * @param pinput_info input_info
 */
void default_mode( pinput_info input_info )
{

    pphysical_info physical_info = input_info->physical_info;


    //calculate new  values of physical variables
    physical_info->theta += calculateDegree(
        physical_info->length,
        physical_info->theta
    );

    physical_info->omega = angSpeed(
        physical_info->length,
        physical_info->theta
    );

    physical_info->alpha = angAcceler(
        physical_info->length,
        physical_info->theta
    );

    draw_and_show_screen( input_info );
}


/********************************  draw and show screen  *******************************/


/**
 * @brief draw and show screen
 * @param pinput_info input_info
 */
void draw_and_show_screen( pinput_info input_info )
{

    // copy data form input_info
    Screen screen = input_info->screen;

    // tmp_screen is a backup of screen when draw tools return NULL to screen
    Screen tmp_screen = screen;
    assert( screen != NULL );

    pphysical_info physical_info = input_info->physical_info;


    // copy the values of physical variables into a char array
    // and use them to draw data panel
    char char_theta[32], char_alpha[32], char_omega[32], char_length[32], char_mass[32];

    screen = draw_data_panel(
        screen,
        double_to_char( char_theta, physical_info->theta, DOUBLE_NUMBER_DIGITS ),
        double_to_char( char_alpha, physical_info->alpha, DOUBLE_NUMBER_DIGITS ),
        double_to_char( char_omega, physical_info->omega, DOUBLE_NUMBER_DIGITS ),
        double_to_char( char_length, physical_info->length, DOUBLE_NUMBER_DIGITS ),
        double_to_char( char_mass, physical_info->mass, DOUBLE_NUMBER_DIGITS )
    );
    assert( screen != NULL );
    if (screen == NULL) {
        program_info_msg << "***ERROR: fail to draw data panel***\n";
        screen = tmp_screen;
    }


    // show which physical variable is waiting for user input or none of them
    screen = screen_input( screen, input_info->name );
    assert( screen != NULL );
    if ( screen == NULL ) {
        program_info_msg << "***ERROR: fail to screen input***\n";
        screen = tmp_screen;
    }


    // draw pendulum
    screen  = draw_pendulum( screen, physical_info->theta, physical_info->length );
    assert( screen != NULL );
    if ( screen == NULL ) {
        program_info_msg << "***ERROR: fail to draw pendulum***\n";
        screen = tmp_screen;
    }


    // show screen
    if ( screen == NULL ) {
        screen_show(tmp_screen);
        program_info_msg << "***ERROR: screen is NULL***\n";
    }
    else {
        screen_show(screen);
    }
}


/****************************  convert double to char*  *******************************/


/**
 * @brief copy the value of a double into a char array
 * 
 * @param char *buffer : target char array
 * @param double double_value
 * @param size_t sz : size of target char array
 * 
 * @return target char array
 */
char *double_to_char( char *buffer, double double_value, size_t sz )
{
    snprintf( buffer, sz-1, "%f", double_value );
    for ( size_t i = 0; i < sz; i++ ) {
        if ( !((buffer[i] >= '0' && buffer[i] <= '9') || buffer[i] == '.') ) {
            buffer[i] = '0';
        }
    }

    return buffer;
}