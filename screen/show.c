/**
 * @file show.cpp
 * @author IalvinchangI
 * @brief 把螢幕上的內容顯示出來 (`screen_show`) () ()
 * @version 0.3
 * @date 2024-07-10
 */


#include<stdio.h>  // printf
#include<stdlib.h>  // system

#include "screen_object.h"  // Screen, screen_input_name.NONE
#include "draw.h"  // clean_screen, draw_info_panel


/**
 * @brief 把 螢幕上的內容 顯示出來
 * @attention 執行此函式會把螢幕清空
 * 
 * @param screen 螢幕物件
 * @return 傳入的螢幕物件 or NULL(執行失敗)
 */
Screen screen_show(Screen screen) {
    // draw last part
    draw_info_panel(screen, DEFAULT_MODE);
    draw_screen_input(screen);

    // clean cmd
    system("CLS");

    // print
    for (int y = 0; y < screen -> height ; y++) {
        printf("%s\n", screen -> ground[y]);
    }

    // clean screen
    clean_screen(screen);

    // clean input
    // screen_input(screen, NONE);

    return screen;
}
