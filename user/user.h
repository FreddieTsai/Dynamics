#ifndef USER_H
    #define USER_H
    #include <string>
    #include "..\screen\screen.h"
    #include "input_info.h"

    unsigned __stdcall user_input_thread( void * );
    
    unsigned __stdcall insertion_thread( void * );

    void default_mode( pinput_info );

    void pause_mode( pinput_info );

    void insert_mode( pinput_info );

    void draw_and_show_screen( pinput_info );

    char *double_to_char( char *, double, size_t sz );

#endif