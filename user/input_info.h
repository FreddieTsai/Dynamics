#ifndef INPUT_INFO_H
    #define INPUT_INFO_H
    #include "..\screen\screen.h"
    #include "physical_info.h"
    //#include "output.h"

    /**
     * @param terminate_program_TF determine program is terminated or not
     * @param terminate_insertion_TF determine insertion is terminated or not
     * @param mode program is under which mode
     * @param name determine which physical variable is being inserted
     * @param screen
     */
    typedef struct __input_info {
        bool &terminate_program_TF;
        bool &terminate_insertion_TF;
        char &mode;
        screen_input_name &name;
        pphysical_info physical_info;
        Screen screen;
        //plog_info log_info;
    } input_info, *pinput_info;

#endif