/**
 * @file setting.cpp
 * @author IalvinchangI
 * @brief `Screen`的設定 (`set_screen_size`, `create_screen`) () (`set_layout`, `init_screen`)
 * @version 0.3
 * @date 2024-07-04
 */


#include<stdlib.h>  // malloc, free, NULL
#include<stdbool.h>  // true
#include<Windows.h>  // HANDLE, GetStdHandle, STD_OUTPUT_HANDLE, INVALID_HANDLE_VALUE, CONSOLE_SCREEN_BUFFER_INFO, GetConsoleScreenBufferInfo

#include "__screen_object.h"  // Screen, Layout, screen_input_name.NONE


// ================================== set_screen_size ==================================

// according to the size of screen, this function will adjust the position of each panel
Screen set_layout(Screen screen) {
    // set ground

    // set the position of pivot

    // set the position of data_panel

    // set the position of info_panel

    return screen;
}


/**
 * @brief 用來設定顯示範圍
 * @attention 執行此函式會把螢幕清空
 * 
 * @param screen 螢幕物件
 * @param screen_width 螢幕顯示範圍的高度
 * @param screen_height 螢幕顯示範圍的寬度
 * @return 傳入的螢幕物件 or NULL(執行失敗)
 */
Screen set_screen_size(Screen screen, int screen_width, int screen_height) {
    // set size
    screen -> width = screen_width;
    screen -> height = screen_height;

    // set layout
    screen -> empty_TF = true;  // screen is empty
    return set_layout(screen);
}

/**
 * @brief 根據視窗當前大小來設定顯示範圍
 * @attention 執行此函式會把螢幕清空
 * 
 * @param screen 螢幕物件
 * @return 傳入的螢幕物件 or NULL(執行失敗)
 */
Screen set_screen_size(Screen screen) {
    // get window size
    HANDLE handle_console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (handle_console == INVALID_HANDLE_VALUE || handle_console == NULL) {  // fail to get StdHandle
        return NULL;
    }

    CONSOLE_SCREEN_BUFFER_INFO console_info;
    if (!GetConsoleScreenBufferInfo(handle_console, &console_info)) {  // fail to get info
        return NULL;
    }

    int console_width = console_info.srWindow.Right - console_info.srWindow.Left + 1;
    int console_height = console_info.srWindow.Bottom - console_info.srWindow.Top + 1;

    // setting
    return set_screen_size(screen, console_width, console_height);
}




// ================================== create_screen ==================================

// malloc and initialize `empty_TF` and `input_name`
Screen init_screen() {
    Screen screen = (Screen) malloc(sizeof(Screen));
    if (screen == NULL) {
        return NULL;  // fail
    }
    screen -> empty_TF = true;  // screen is empty
    screen -> input_name = NONE;  // it is not inputting
    return screen;  // succeed
}


/**
 * @brief 用來初始化 螢幕物件(`Screen`)
 * @return 初始化好的物件 or NULL(初始化失敗)
 */
Screen create_screen() {
    // init
    Screen screen = init_screen();

    // set size
    if (screen != NULL) {
        set_screen_size(screen);
    }
    return screen;
}

/**
 * @brief 用來初始化 螢幕物件(`Screen`)
 * 
 * @param screen_width 螢幕顯示範圍的高度
 * @param screen_height 螢幕顯示範圍的寬度
 * @return 初始化好的物件 or NULL(初始化失敗)
 */
Screen create_screen(int screen_width, int screen_height) {
    // init
    Screen screen = init_screen();

    // set size
    if (screen != NULL) {
        set_screen_size(screen, screen_width, screen_height);
    }
    return screen;
}
