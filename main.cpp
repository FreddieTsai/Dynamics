#include <process.h>  // _beginthreadex()
#include <winnt.h>  // HANDLE
#include <cassert>  // assert()
#include <iostream>
#include "screen\screen.h"
#include "screen\screen_input_name.h"
#include "user\user.h"
#include "user\physical_info.h"

using namespace std;

int main()
{
    cout << "program start\n";

    //initialize objects
    Screen screen = create_screen();
    Screen tmp_screen = screen;
    assert( screen != NULL );

    bool terminate_program_TF = false;
    bool terminate_insertion_TF = false;
    char mode = 'D';
    screen_input_name name = NONE;
    physical_info __physical_info{ 1.0, 1.0, 1.0, 1.0, 1.0 };
    pphysical_info physical_info = &__physical_info;
    
    input_info __input_info{
        terminate_program_TF, terminate_insertion_TF, mode, name, physical_info, screen
    };
    pinput_info input_info = &__input_info;

    //create another thread about user input
    unsigned threadID;
    HANDLE hthread = (HANDLE)_beginthreadex(
        NULL, 0, user_input_thread, input_info, 0, &threadID
    );

    //show screen
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
                cout << "invalid mode\n";
                break;
        }
    }

    return 0;
}