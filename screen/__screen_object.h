/**
 * @file __screen_object.h
 * @author IalvinchangI
 * @brief 定義 `Screen`, `Layout`，引入 `screen_input_name`
 * @version 0.2
 * @date 2024-07-04
 */


#ifndef __screen_object_H_
    #define __screen_object_H_

    #include<stdbool.h>  // bool

    #include "__vector.h"  // position
    #include "__screen_input_name.h"  // screen_input_name


    /**
     * @brief 各面板的位置
     */
    typedef struct {
        position pivot;       // 單擺轉軸位置
        position data_panel;  // data_panel 的位置
        position info_panel;  // info_panel 的位置
    } Layout;



    /**
     * @brief 螢幕物件，記錄了所有和螢幕顯示有關的資訊
     */
    typedef struct _screen {
        char** ground;                  // 螢幕 (字是2格寬的)
        unsigned int width;             // 螢幕寬度
        unsigned int height;            // 螢幕長度
        Layout layout;                  // 排版
        bool empty_TF;                  // 螢幕是否是空的
        screen_input_name input_name;   // 目前正在輸入的 data格
    } raw_screen;

    /**
     * @brief 螢幕物件(含指標)，記錄了所有和螢幕顯示有關的資訊
     */
    typedef raw_screen* Screen;

#endif
