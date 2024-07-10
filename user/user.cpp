#include <conio.h>  // for getch()
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

// log file ( defined in main.cpp )
extern string log_file_name;
extern ofstream program_info_msg;

// period of updating screen with ms ( defined in main.cpp )
extern const long SCREEN_UPDATE_PERIOD;


// number of digits of a double value
extern const size_t DOUBLE_NUMBER_OF_DIGITS = 9;


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
        key_input = getch();
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
        key_input = getch();
        key_input = toupper( key_input );
        double change_value = 0.0;

        switch ( key_input )
        {
            case 'A' :
                input_info->input_name = THETA;
                program_info_msg << "inserting theta\n";

                // get user input
                char ch = '0';

                // store new value about THETA
                char buffer[DOUBLE_NUMBER_OF_DIGITS];

                // record what digit will be inserted into buffer
                size_t idx = 0;

                while ( ch != '\r' )
                {
                    ch = getch();
                    update_physical_variable( input_info, buffer, idx );
                    physical_info->theta = char_to_double( buffer, idx );
                }

                input_info->input_name = NONE;

                break;
            
            case 'T' :
                input_info->input_name = TIME;
                program_info_msg << "inserting time\n";

                // get user input
                char ch = '0';

                // store new value about TIME
                char buffer[DOUBLE_NUMBER_OF_DIGITS];

                // record what digit will be inserted into buffer
                size_t idx = 0;

                while ( ch != '\r' )
                {
                    ch = getch();
                    update_physical_variable( input_info, buffer, idx );
                    physical_info->time = char_to_double( buffer, idx );
                }

                input_info->input_name = NONE;

                break;

            case 'L' :
                input_info->input_name = LENGTH;
                program_info_msg << "inserting length\n";

                // get user input
                char ch = '0';

                // store new value about TIME
                char buffer[DOUBLE_NUMBER_OF_DIGITS];

                // record what digit will be inserted into buffer
                size_t idx = 0;

                while ( ch != '\r' )
                {
                    ch = getch();
                    update_physical_variable( input_info, buffer, idx );
                    physical_info->length = char_to_double( buffer, idx );
                }

                input_info->input_name = NONE;

                break;

            // jump out of insert_mode
            case 'C' :
                input_info->terminate_insertion_TF = true;
                input_info->input_name = NONE;
                break;
            

            // jump out of insert_mode and terminate the program
            case 'E' :
                input_info->terminate_insertion_TF = true;
                input_info->terminate_program_TF = true;
                input_info->input_name = NONE;
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


/***************************  updating physical variable *******************************/


/**
 * @brief update values of physical variables
 * @param pinput_info input_info
 */
void update_physical_variable( pinput_info input_info, char *buffer, size_t &idx )
{
    pphysical_info physical_info = input_info->physical_info;

    // get user input
    char ch = getch();
    ch = toupper(ch);

    // terminate program
    if ( ch == 'E' ) {
        input_info->terminate_insertion_TF = true;
        input_info->terminate_program_TF = true;
    }

    // jump out insert_mode
    else if ( ch == 'C' ) {
        input_info->terminate_insertion_TF = true;
    }

    // invalid insertion to physical variables
    else if ( !((ch >= '0' && ch <= '9') || (ch == '.')) ) {
        program_info_msg << "***ERROR: insert an alphabet or other invalid key to physical variables***\n";
        return;
    }

    // update new value about physical variables
    else {
        if ( idx >= DOUBLE_NUMBER_OF_DIGITS ) {
            program_info_msg << "***ERROR: exceed maximum digit of a double value***\n";
            return;
        }

        if ( ch != '\r' ) {
            buffer[idx] = ch;
            idx += 1;
        }
    }

    return;
}


/**********************************  insert mode  **************************************/


/**
 * @brief insert_mode
 * @param pinput_info input_info
 */
void insert_mode( pinput_info input_info )
{

    // copy data from input_info
    Screen screen = input_info->screen;
    Screen tmp_screen = screen;


    // change info panel to INSERT_MODE
    input_info->info_name = INSERT_MODE;


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
        Sleep( SCREEN_UPDATE_PERIOD );
    }

    
    // change info panel back to DEFAULT_MODE
    input_info->info_name = DEFAULT_MODE;


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


    // show hot key info panel
    screen = draw_info_panel( screen, input_info->info_name );
    assert( screen != NULL );
    if ( screen == NULL ) {
        program_info_msg << "***ERROR: fail to draw info panel***\n";
        screen = tmp_screen;
    }


    // copy the values of physical variables into a char array
    // and use them to draw data panel
    char char_theta[DOUBLE_NUMBER_OF_DIGITS], 
         char_alpha[DOUBLE_NUMBER_OF_DIGITS], 
         char_omega[DOUBLE_NUMBER_OF_DIGITS], 
         char_length[DOUBLE_NUMBER_OF_DIGITS], 
         char_mass[DOUBLE_NUMBER_OF_DIGITS];


    screen = draw_data_panel(
        screen,
        double_to_char( char_theta, physical_info->theta, DOUBLE_NUMBER_OF_DIGITS ),
        double_to_char( char_alpha, physical_info->alpha, DOUBLE_NUMBER_OF_DIGITS ),
        double_to_char( char_omega, physical_info->omega, DOUBLE_NUMBER_OF_DIGITS ),
        double_to_char( char_length, physical_info->length, DOUBLE_NUMBER_OF_DIGITS ),
        double_to_char( char_mass, physical_info->time, DOUBLE_NUMBER_OF_DIGITS )
    );
    assert( screen != NULL );
    if (screen == NULL) {
        program_info_msg << "***ERROR: fail to draw data panel***\n";
        screen = tmp_screen;
    }


    // show which physical variable is waiting for user input or none of them
    screen = screen_input( screen, input_info->input_name );
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


/****************************  convertion between double and char*  *******************************/


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


/**
 * @brief get the double value from a char array
 * 
 * @param char *buffer
 * @param size_t sz : size of char array
 */
double char_to_double( char *buffer, size_t sz )
{
    // make sure buffer has content
    if ( sz <= 0 ) {
        return 0.0;
    }

    double double_value = 0.0;
    size_t i = 0;
    
    // get the integer part of double value
    for ( i = 0; i < sz && buffer[i] != '.'; i++ ) {

        double_value *= 10;
        double_value += (buffer[i]-'0');
    }

    // reach end of buffer (get all numbers in buffer)
    if ( i == sz ) {
        return double_value;
    }

    // to get the digit after the decimal point
    i += 1;

    // get the float part of double value
    for ( double offset = 0.1 ; i < sz; i++ ) {

        double_value += (offset * (buffer[i]-'0'));
        offset *= 0.1;
    }
    return double_value;
}