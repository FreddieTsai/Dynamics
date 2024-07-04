/**
 * @file __draw.h
 * @author IalvinchangI
 * @brief 畫各個面板 (`clean_screen`, `draw_pendulum`, `draw_data_panel`, `screen_input`) (`draw_info_panel`)
 * @version 0.1
 * @date 2024-07-04
 */


#ifndef __draw_H_
    #define __draw_H_
    
    #include "__screen_object.h"  // Screen, screen_input_name

    Screen clean_screen(Screen screen);

    Screen draw_pendulum(Screen screen, double theta, double length);
    Screen draw_data_panel(Screen screen, char* theta, char* alpha, char* omega, char* length, char* mass);
    Screen draw_info_panel(Screen screen);

    Screen screen_input(Screen screen, screen_input_name name);

#endif
