#include <conio.h>  // _getch()
#include <ctype.h> // toupper()
#include <winnt.h>  // HANDLE
#include <cassert>  // assert()
#include <process.h>  // _endthreadex()
#include <iostream>
#include <fstream>  // ofstream
#include "..\screen\screen.h"
#include "user.h"
#include "physical_info.h"
#include "..\calculator.h"

using namespace std;

const size_t DOUBLE_NUMBER_DIGITS = 32;  // maximun number of digits of physical variables

/********************  change mode according to user input  ***********************/
unsigned __stdcall user_input_thread( void *__input_info )
{
    pinput_info input_info = static_cast<pinput_info>(__input_info);

    ofstream err_msg( "err_msg.txt", ios::app );
    ofstream program_info_msg( "program_info_msg.txt", ios::app );
    if ( !err_msg )
        input_info->terminate_program_TF = true;
    if ( !program_info_msg )
        input_info->terminate_program_TF = true;

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
                err_msg << "enter \'I\' to insert values of physical information\n";
                break;

            default :
                err_msg << "invalid input\n";
                break;
        }
    }
    _endthreadex( 0 );
    return 0;
}

/******************************  insertion thread  ********************************/

unsigned __stdcall insertion_thread( void *__input_info )
{
    pinput_info input_info = static_cast<pinput_info>(__input_info);

    ofstream err_msg( "err_msg.txt", ios::app );
    ofstream program_info_msg( "program_info_msg.txt", ios::app );
    if ( !err_msg ){
        input_info->terminate_insertion_TF = true;
        input_info->terminate_program_TF = true;
    }
    if ( !program_info_msg ){
        input_info->terminate_insertion_TF = true;
        input_info->terminate_program_TF = true;
    }
    program_info_msg << "insertion thread start\n";

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
                if ( cin ) {
                    physical_info->omega = change_value;
                }
                else {
                    err_msg << "omega must be a number\n";
                    cin.clear();
                    cin.ignore( 1024, '\n' );
                }
                break;
            
            case 'A' :
                input_info->name = ALPHA;
                program_info_msg << "inserting alpha\n";
                cin >> change_value;
                if ( cin ) {
                    physical_info->alpha = change_value;
                }
                else {
                    err_msg << "alpha must be a number\n";
                    cin.clear();
                    cin.ignore( 1024, '\n' );
                }
                break;

            case 'L' :
                input_info->name = LENGTH;
                program_info_msg << "inserting length\n";
                cin >> change_value;
                if ( cin ) {
                    if ( change_value != 0 ) {
                        physical_info->length = change_value;
                    }
                    else {
                        err_msg << "length must > 0\n";
                    }
                }
                else {
                    err_msg << "length must be a number\n";
                    cin.clear();
                    cin.ignore( 1024, '\n' );
                }
                break;
            
            case 'M' :
                input_info->name = MASS;
                program_info_msg << "inserting mass\n";
                cin >> change_value;
                if ( cin ) {
                    physical_info->mass = change_value;
                }
                else {
                    err_msg << "mass must be a number\n";
                    cin.clear();
                    cin.ignore( 1024, '\n' );
                }
                break;

            case 'T' :
                input_info->name = THETA;
                program_info_msg << "inserting theta\n";
                cin >> change_value;
                if ( cin ) {
                    physical_info->theta = change_value;
                }
                else {
                    err_msg << "theta must be a number\n";
                    cin.clear();
                    cin.ignore( 1024, '\n' );
                }

            case 'C' :
                input_info->terminate_insertion_TF = true;
                input_info->name = NONE;
                break;
            
            case 'E' :
                input_info->terminate_insertion_TF = true;
                input_info->terminate_program_TF = true;
                input_info->name = NONE;
                break;

            default:
                err_msg << "invalid insertion\n";
                input_info->name = NONE;
                break;
        }
    }
    input_info->mode = 'D';
    program_info_msg << "insertion thread end\n";
    _endthreadex( 0 );
    return 0;
}

/***************************  insert mode  *********************************************/

void insert_mode( pinput_info input_info )
{
    ofstream err_msg( "err_msg.txt", ios::app );
    ofstream program_info_msg( "program_info_msg.txt", ios::app );
    if ( !err_msg ){
        input_info->terminate_insertion_TF = true;
        input_info->terminate_program_TF = true;
    }
    if ( !program_info_msg ) {
        input_info->terminate_insertion_TF = true;
        input_info->terminate_program_TF = true;
    }
    program_info_msg << "insert mode start\n";

    Screen screen = input_info->screen;
    Screen tmp_screen = screen;

    unsigned threadID;
    HANDLE hthread = (HANDLE)_beginthreadex(
        NULL, 0, insertion_thread, input_info, 0, &threadID
    );

    while ( !input_info->terminate_insertion_TF )
    {
        default_mode( input_info );
    }

    program_info_msg << "insert mode end\n";
    input_info->terminate_insertion_TF = false;
}

/********************************  pause mode  *****************************************/

void pause_mode( pinput_info input_info )
{
    draw_and_show_screen( input_info );   
}

/***********************************  default mode  **********************************/

void default_mode( pinput_info input_info )
{
    ofstream err_msg( "err_msg.txt", ios::app );
    ofstream program_info_msg( "program_info_msg.txt", ios::app );
    if ( !err_msg ){
        input_info->terminate_program_TF = true;
    }
    if ( !program_info_msg ){
        input_info->terminate_program_TF = true;
    }

    pphysical_info physical_info = input_info->physical_info;

    //calculate new physical info
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
    //program_info_msg << "calculation is done!\n";

    draw_and_show_screen( input_info );
}

/********************************  draw and show screen  *******************************/

void draw_and_show_screen( pinput_info input_info )
{
    ofstream err_msg( "err_msg.txt", ios::app );
    ofstream program_info_msg( "program_info_msg.txt", ios::app );
    if ( !err_msg ){
        input_info->terminate_program_TF = true;
    }
    if ( !program_info_msg ){
        input_info->terminate_program_TF = true;
    }

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
        err_msg << "fail to draw data panel\n";
        screen = tmp_screen;
    }
    //program_info_msg << "drawed data panel\n";

    screen = screen_input( screen, input_info->name );
    assert( screen != NULL );
    if ( screen == NULL ) {
        err_msg << "fail to screen input\n";
        screen = tmp_screen;
    }
    //program_info_msg << "screen inputed\n";

    screen  = draw_pendulum( screen, physical_info->theta, physical_info->length );
    assert( screen != NULL );
    if ( screen == NULL ) {
        err_msg << "fail to draw pendulum\n";
        screen = tmp_screen;
    }
    //program_info_msg << "drawed pendulum\n";

    if ( screen == NULL ) {
        screen_show(tmp_screen);
    }
    else {
        screen_show(screen);
    }
    //program_info_msg << "screen showed\n";
}

/****************************  convert double to char*  *******************************/

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