#include <process.h>  // for _beginthreadex()
#include <windows.h>  // for Sleep()
#include <cassert>  // for assert()
#include <iostream>
#include <fstream>  // for ofstream


#include "user\user.h"
#include "user\input_info.h"


using namespace std;


// log file
ofstream program_info_msg;
string log_file_name( "program_info_msg.txt" );

// period of updating screen with ms
extern const long SCREEN_UPDATE_PERIOD = 30L;


int main()
{

    // create fostream of program_info_msg with append mode
    program_info_msg.open( log_file_name, ios::app );


    // make sure log file is created
    if ( !program_info_msg )
        return 1;

    program_info_msg << "\nprogram start\n";


    // initialize objects
    Screen screen = create_screen();

    // tmp_screen is a backup of screen when screen becomes NULL
    Screen tmp_screen = screen;
    assert( screen != NULL );


    bool terminate_program_TF = false;
    bool terminate_insertion_TF = false;


    // mode should be initialized as default mode
    char mode = 'D';


    // user insertion should be initialized as NONE
    screen_input_name input_name = NONE;


    // info panel should be initialized as DEFAULT_MODE
    screen_info_name info_name = DEFAULT_MODE;


    // initialize values of physical variables
    physical_info __physical_info{ 20.0, 1.0, 1.0, 20.0, 0.01 };
    pphysical_info physical_info = &__physical_info;
    

    // initialize input info
    input_info __input_info{
        terminate_program_TF, terminate_insertion_TF,
        mode, input_name, info_name, physical_info, screen,
    };
    pinput_info input_info = &__input_info;


    // create another thread waiting user inputs
    unsigned threadID;
    HANDLE hthread = (HANDLE)_beginthreadex(
        NULL, 0, user_input_thread, input_info, 0, &threadID
    );


    // switch mode based on the value of mode
    while ( !terminate_program_TF )
    {
        switch ( mode )
        {
            case 'P' :
                pause_mode( input_info );
                break;
            
            case 'I' :
                break;

            case 'D' :
                default_mode( input_info );
                break;

            default :
                default_mode( input_info );
                program_info_msg << "***ERROR: invalid mode***\n";
                break;
        }

        // lower the frequency of updating screen
        Sleep( SCREEN_UPDATE_PERIOD );
    }

    program_info_msg << "program end\n";
    return 0;
}