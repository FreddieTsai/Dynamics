#include <process.h>  // for _beginthreadex()
#include <windows.h>  // for Sleep()
#include <cassert>  // for assert()
#include <iostream>
#include <fstream>  // for ofstream


#include "screen\screen.h"
#include "user\user.h"
#include "user\physical_info.h"


using namespace std;

int main()
{

    // create fostream of err_msg and program_info_msg
    ofstream program_info_msg( "program_info_msg.txt", ios::app );


    // make sure file "program_info_msg.txt" is created
    if ( !program_info_msg )
        return 1;

    program_info_msg << "program start\n";


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
    screen_input_name name = NONE;


    // initialize values of physical variables
    physical_info __physical_info{ 20.0, 1.0, 1.0, 20.0, 1.0 };
    pphysical_info physical_info = &__physical_info;
    

    // initialize input info
    input_info __input_info{
        terminate_program_TF, terminate_insertion_TF, mode, name, physical_info, screen
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
        Sleep( 500L );
    }

    program_info_msg << "program end\n";
    return 0;
}