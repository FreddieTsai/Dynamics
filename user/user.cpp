#include <conio.h>  // _getch()
#include <ctype.h> // toupper()
#include <winnt.h>  // HANDLE
#include <cassert>  // assert()
#include <process.h>  // _endthreadex()
#include <iostream>
#include "user.h"
#include "physical_info.h"
#include "..\calculator.h"

using namespace std;

const size_t DOUBLE_NUMBER_DIGITS = 32;  // maximun number of digits of physical variables

/********************  change mode according to user input  ***********************/
unsigned __stdcall user_input_thread( void *__input_info )
{
    pinput_info input_info = static_cast<pinput_info>(__input_info);
    char key_input = 'D';
    while ( !input_info->terminate_program_TF )
    {
        key_input = _getch();
        key_input = toupper( key_input );

        switch ( key_input )
        {
            case 'E' : 
                cout << "exit the program? \'y\' or \'n\'\n";
                char ch;
                while ( true )
                {
                    ch = _getch();
                    if ( ch == 'y' || ch == 'n' ) {
                        break;
                    }
                }
                if ( ch == 'y' ) {
                    break;
                }
                else if ( ch == 'n' ) {
                    continue;
                }
                break;

            case 'C' :
                input_info->mode = 'D';
                break;

            case 'P' :
                input_info->mode = 'P';
                break;

            case 'I' :
                input_info->mode = 'I';
                insert_mode( input_info );
                break;

            case 'W' : case 'A' : case 'T' :
                cout << "enter \'I\' to insert values of physical information\n";
                break;

            default :
                cout << "invalid input\n";
                break;
        }
    }
    input_info->terminate_program_TF = true;
    _endthreadex( 0 );
    return 0;
}

/******************************  insertion thread  ********************************/

unsigned __stdcall insertion_thread( void *__input_info )
{
    pinput_info input_info = static_cast<pinput_info>(__input_info);
    pphysical_info physical_info = input_info->physical_info;
    Screen screen = input_info->screen;
    Screen tmp_screen = screen;
    screen_input_name name;
    char key_input;
    
    while ( true )
    {
        key_input = _getch();
        key_input = toupper( key_input );
        double change_value = 0.0;

        switch ( key_input )
        {
            case 'W' :
                cin >> change_value;
                if ( cin ) {
                    physical_info->omega = change_value;
                    input_info->name = OMEGA;
                }
                else {
                    cout << "omega must be a number\n";
                    cin.clear();
                    cin.ignore( 1024, '\n' );
                }
                break;
            
            case 'A' :
                cin >> change_value;
                if ( cin ) {
                    physical_info->alpha = change_value;
                    input_info->name = ALPHA;
                }
                else {
                    cout << "alpha must be a number\n";
                    cin.clear();
                    cin.ignore( 1024, '\n' );
                }
                break;

            case 'L' :
                cin >> change_value;
                if ( cin ) {
                    physical_info->length = change_value;
                    input_info->name = LENGTH;
                }
                else {
                    cout << "length must be a number\n";
                    cin.clear();
                    cin.ignore( 1024, '\n' );
                }
                break;
            
            case 'M' :
                cin >> change_value;
                if ( cin ) {
                    physical_info->mass = change_value;
                    input_info->name = MASS;
                }
                else {
                    cout << "mass must be a number\n";
                    cin.clear();
                    cin.ignore( 1024, '\n' );
                }
                break;

            case 'T' :
                cin >> change_value;
                if ( cin ) {
                    physical_info->theta = change_value;
                    input_info->name = THETA;
                }
                else {
                    cout << "theta must be a number\n";
                    cin.clear();
                    cin.ignore( 1024, '\n' );
                }

            case 'C' : case 'E' : 
                input_info->name = NONE;
                break;

            default:
                cout << "invalid input\n";
                input_info->name = NONE;
                break;
        }

        if ( key_input == 'C' ) {
            break;
        }
        if ( key_input == 'E' ) {
            cout << "exit the program? \'y\' or \'n\'\n";
                char ch;
                while ( true )
                {
                    ch = _getch();
                    if ( ch == 'y' || ch == 'n' ) {
                        break;
                    }
                }
                if ( ch == 'y' ) {
                    input_info->terminate_program_TF = true;
                }
            break;
        }
    }
    input_info->terminate_insertion_TF = true;
    input_info->mode = 'D';
    _endthreadex( 0 );
    return 0;
}

/***************************  insert mode  *********************************************/

void insert_mode( pinput_info input_info )
{
    Screen screen = input_info->screen;
    Screen tmp_screen = screen;

    unsigned threadID;
    HANDLE hthread = (HANDLE)_beginthreadex(
        NULL, 0, user_input_thread, input_info, 0, &threadID
    );

    while ( !input_info->terminate_insertion_TF )
    {
        screen = screen_input( screen, input_info->name );
        if ( screen == NULL ) {
            cout << "fail to screen input\n";
            screen = tmp_screen;
        }
        draw_and_show_screen( input_info );
    }
}

/********************************  pause mode  *****************************************/

void pause_mode( pinput_info input_info )
{
    draw_and_show_screen( input_info );   
}

/***********************************  default mode  **********************************/

void default_mode( pinput_info input_info )
{
    pphysical_info physical_info = input_info->physical_info;

    //calculate new physical info
    physical_info->theta = calculateDegree(
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
    cout << "calculation is done!\n";

    draw_and_show_screen( input_info );
}

/********************************  draw and show screen  *******************************/

void draw_and_show_screen( pinput_info input_info )
{
    Screen screen = input_info->screen;
    Screen tmp_screen = screen;
    assert( screen != NULL );

    pphysical_info physical_info = input_info->physical_info;

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
        cout << "fail to draw data panel\n";
        screen = tmp_screen;
    }
    cout << "drawed data panel\n";

    screen  = draw_pendulum( screen, physical_info->theta, physical_info->length );
    assert( screen != NULL );
    if ( screen == NULL ) {
        cout << "fail to draw pendulum\n";
        screen = tmp_screen;
    }
    cout << "drawed pendulum\n";

    if ( screen == NULL ) {
        screen_show(tmp_screen);
    }
    else {
        screen_show(screen);
    }
    cout << "screen showed\n";
}

/****************************  convert double to char*  *******************************/

char *double_to_char( char *buffer, double double_value, size_t sz )
{
    snprintf( buffer, sz, "%f", double_value );
    for ( size_t i = 0; i < sz; i++ ) {
        if ( !((buffer[i] >= '0' && buffer[i] <= '9') || buffer[i] == '.') ) {
            buffer[i] = '0';
        }
    }

    return buffer;
}