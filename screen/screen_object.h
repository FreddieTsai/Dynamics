/**
 * @file screen_object.h
 * @author IalvinchangI
 * @brief 定義 `Screen`, `Layout`，引入 `screen_input_name`, `screen_info_name`
 * @version 0.8
 * @date 2024-07-10
 */


#ifndef screen_object_H_
    #define screen_object_H_

    #include<stdbool.h>  // bool

    #include "vector.h"  // position, rectangle
    #include "screen_input_name.h"  // screen_input_name
    #include "screen_info_name.h"  // screen_info_name


    /**
     * @brief 各面板的位置
     */
    typedef struct {
        position pivot;       // 單擺轉軸位置
        rectangle pendulum_boundary;  // 單擺面板的繪圖範圍
        position data_panel;  // data_panel 的位置
        position info_panel_content;  // info內容 的位置
    } Layout;



    /**
     * @brief 螢幕物件，記錄了所有和螢幕顯示有關的資訊
     */
    typedef struct _screen {
        char** ground;                  // 螢幕
        unsigned int width;             // 螢幕寬度
        unsigned int height;            // 螢幕長度
        Layout layout;                  // 排版
        bool empty_TF;                  // 螢幕是否是空的
        screen_input_name input_name;   // 目前正在輸入的 data格
        unsigned char flash;            // 輸入的閃爍
        int pendulum_radius;            // 單擺的寬度半徑
    } raw_screen;

    /**
     * @brief 螢幕物件(含指標)，記錄了所有和螢幕顯示有關的資訊
     */
    typedef raw_screen* Screen;

#endif
