/**
 * @file draw.h
 * @author IalvinchangI
 * @brief 畫各個面板 (`clean_screen`, `draw_pendulum`, `draw_data_panel`, `screen_input`) (`draw_info_panel`)
 * @version 0.5
 * @date 2024-07-12
 */


#ifndef draw_H_
    #define draw_H_
    
    #include "screen_object.h"  // Screen, screen_input_name, screen_info_name

    #ifdef __cplusplus
    extern "C" {
    #endif

        Screen clean_screen(Screen screen);

        Screen draw_pendulum(Screen screen, double theta, double length);
        Screen draw_data_panel(Screen screen, char* theta, char* terminal_angle, char* alpha, char* omega, char* length, char* time);
        Screen draw_info_panel(Screen screen, screen_info_name name);
        Screen draw_screen_input(Screen screen);

        Screen screen_input(Screen screen, screen_input_name name);

    #ifdef __cplusplus
    }
    #endif

#endif
