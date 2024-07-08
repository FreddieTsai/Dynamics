/**
 * @file setting.cpp
 * @author IalvinchangI
 * @brief `Screen`的設定、刪除 (`set_screen_size`, `create_screen`, `set_pendulum_radius`, `delete_screen`) () (`set_layout`, `delete_ground`, `init_screen`)
 * @version 0.7
 * @date 2024-07-07
 */


#include<stdlib.h>  // malloc, free, NULL
#include<stdbool.h>  // true
#include<windows.h>  // HANDLE, GetStdHandle, STD_OUTPUT_HANDLE, INVALID_HANDLE_VALUE, CONSOLE_SCREEN_BUFFER_INFO, GetConsoleScreenBufferInfo

#include "screen_object.h"  // Screen, Layout, screen_input_name.NONE
#include "draw.h" // clean_screen
#include "panel_constant.h"  // DATA_PANEL_WIDTH, DATA_PANEL_HEIGHT, INFO_LENGTH, SCREEN_MINIMUM_WIDTH, SCREEN_MINIMUM_HEIGHT




// ================================== delete ==================================

// free screen -> ground
static void delete_ground(Screen screen) {
    if (screen -> ground != NULL) {
        for (int y = 0; y < screen -> height; y++) {
            free(screen -> ground[y]);
        }
        free(screen -> ground);
        screen -> ground = NULL;
    }
}


/**
 * @brief 把 螢幕物件 回收
 * 
 * @param screen 螢幕物件
 */
void delete_screen(Screen screen) {
    if (screen != NULL) {
        delete_ground(screen);
        free(screen);
        screen = NULL;
    }
}




// ================================== set_pendulum_radius ==================================

/**
 * @brief 設定 單擺的寬度半徑
 * 
 * @param screen 螢幕物件
 * @param radius 寬度半徑
 * @return 傳入的螢幕物件 or NULL(執行失敗) 
 */
Screen set_pendulum_radius(Screen screen, int radius) {
    screen -> pendulum_radius = radius;
    return screen;
}




// ================================== set_screen_size ==================================

// according to the size of screen, this function will adjust the position of each panel
static Screen set_layout(Screen screen) {
    // free ground
    delete_ground(screen);

    // set ground
    screen -> ground = (char**) malloc(sizeof(char*) * (screen -> height));
    if (screen -> ground == NULL) {  // <error> cannot allocate memory
        return NULL;
    }
    for (int y = 0; y < screen -> height; y++) {
        screen -> ground[y] = (char*) malloc(sizeof(char) * (screen -> width + 1));  // +1 for '\0'
        if (screen -> ground[y] == NULL) {  // <error> cannot allocate memory
            return NULL;
        }
    }
    clean_screen(screen);

    int pendulum_panel_width = screen -> width - DATA_PANEL_WIDTH - 1;  // -1 for padding
    int pendulum_panel_height = screen -> height - INFO_PANEL_HEIGHT;

    // set the position of pivot
    screen -> layout.pivot.x = (int)(pendulum_panel_width / 2);
    screen -> layout.pivot.y = (int)(pendulum_panel_height / 5) + 1.;

    // set the boundary of pendulum panel
    screen -> layout.pendulum_boundary.top_left.x = 0;
    screen -> layout.pendulum_boundary.top_left.y = 0;
    screen -> layout.pendulum_boundary.bottom_right.x = pendulum_panel_width;
    screen -> layout.pendulum_boundary.bottom_right.y = pendulum_panel_height;

    // set the position of data_panel
    screen -> layout.data_panel.x = pendulum_panel_width;
    screen -> layout.data_panel.y = (int)((pendulum_panel_height - DATA_PANEL_HEIGHT) / 2);

    // set the position of info_panel_content
    screen -> layout.info_panel_content.x = (int)((screen -> width - INFO_LENGTH) / 2);
    screen -> layout.info_panel_content.y = pendulum_panel_height + 1;

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
    // check the input value is greater than or equal to minimum size
    if (screen_width < SCREEN_MINIMUM_WIDTH || screen_height < SCREEN_MINIMUM_HEIGHT) {
        return NULL;
    }

    // set size
    screen -> width = screen_width;
    screen -> height = screen_height;

    // set layout
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
    int console_height = console_info.srWindow.Bottom - console_info.srWindow.Top;  // there is one line for user input at bottom

    // setting
    return set_screen_size(screen, console_width, console_height);
}




// ================================== create_screen ==================================

// malloc and initialize `empty_TF` and `input_name`
static Screen init_screen() {
    Screen screen = (Screen) malloc(sizeof(raw_screen));
    if (screen == NULL) {
        return NULL;  // <error> cannot allocate memory
    }
    screen -> ground = NULL;  // does not init
    screen -> empty_TF = true;  // screen is empty
    screen -> input_name = NONE;  // it is not inputting
    screen -> pendulum_radius = 1;  // the radius of pendulum is 1
    return screen;  // succeed
}


/**
 * @brief 初始化 螢幕物件(`Screen`)，並根據視窗當前大小來設定顯示範圍
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
 * @brief 初始化 螢幕物件(`Screen`)
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
