#ifndef INPUT_INFO_H
    #define INPUT_INFO_H
    #include "..\screen\screen.h"
    #include "physical_info.h"
    //#include "output.h"

    /**
     * @param terminate_program_TF determine program is terminated or not
     * @param terminate_insertion_TF determine insertion is terminated or not
     * @param mode program is under which mode
     * @param input_name determine which physical variable is being inserted
     * @param info_name determine which hot key panel is going to present
     * @param screen
     */
    typedef struct __input_info {
        bool &terminate_program_TF;
        bool &terminate_insertion_TF;
        char &mode;
        screen_input_name &input_name;
        screen_info_name &info_name;
        pphysical_info physical_info;
        Screen screen;
        //plog_info log_info;
    } input_info, *pinput_info;

#endif