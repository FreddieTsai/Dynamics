/**
 * @file screen.h
 * @author IalvinchangI
 * @brief 處理螢幕顯示
 * @version 0.5
 * @date 2024-07-04
 */


#ifndef SCREEN_H_
    #define SCREEN_H_

    // ======================== Data Type ========================

    /**
     * @brief 螢幕物件，記錄了所有和螢幕顯示有關的資訊
     */
    typedef struct _screen raw_screen;

    /**
     * @brief 螢幕物件指標，記錄了所有和螢幕顯示有關的資訊
     */
    typedef raw_screen* Screen;


    #include "__screen_input_name.h"



    // ======================== Function ========================

    Screen create_screen();
    Screen create_screen(int screen_width, int screen_height);


    Screen set_screen_size(Screen screen);
    Screen set_screen_size(Screen screen, int screen_width, int screen_height);

 
    Screen clean_screen(Screen screen);

    Screen draw_pendulum(Screen screen, double theta, double length);

    Screen draw_data_panel(Screen screen, char* theta, char* alpha, char* omega, char* length, char* mass);

    Screen screen_input(Screen screen, screen_input_name name);


    Screen screen_show(Screen screen);

#endif