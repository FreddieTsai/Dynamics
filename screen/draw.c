/**
 * @file draw.cpp
 * @author IalvinchangI
 * @brief 畫各個面板 (`clean_screen`, `draw_pendulum`, `draw_data_panel`, `draw_info_panel`, `screen_input`) (`draw_screen_input`) (`flash_TF`)
 * @version 0.7
 * @date 2024-07-10
 */


#include<stdlib.h>  // NULL
#include<string.h>  // strlen
#include<math.h>  // cos, sin, abs
#include<stdbool.h>  // bool, true, false

#include "screen_object.h"  // Screen, Layout, screen_input_name, screen_info_name
#include "vector.h"  // position, rectangle
#include "graph.h"  // all
static bool flash_TF(Screen screen);


// ================================== constant ==================================

#define STR_THETA   "Angle"
#define STR_ALPHA   "Angular_Acceleration"
#define STR_OMEGA   "Angular_Velocity"
#define STR_LENGTH  "Length"
#define STR_TIME    "Time"

static char *data_panel_contents[5] = {
    STR_THETA  "               "    STR_EQUAL, 
    STR_ALPHA  ""                   STR_EQUAL, 
    STR_OMEGA  "    "               STR_EQUAL, 
    STR_LENGTH "              "     STR_EQUAL, 
    STR_TIME   "                "   STR_EQUAL
};

static char *info_content[2] = {
    "Default Mode"  STR_COLON                       STR_LARGE_SPACE
    "C"             STR_COLON   "Continue"          STR_LARGE_SPACE
    "E"             STR_COLON   "Exit"              STR_LARGE_SPACE
    "P"             STR_COLON   "Pause"             STR_LARGE_SPACE
    "I"             STR_COLON   "Insert"
    , 
    "Insert Mode"   STR_COLON                       STR_LARGE_SPACE
    "A"             STR_COLON   STR_THETA           STR_SMALL_SPACE
    "T"             STR_COLON   STR_TIME            STR_SMALL_SPACE
    "L"             STR_COLON   STR_LENGTH          STR_LARGE_SPACE
    "C"             STR_COLON   "Exit Insert Mode"  STR_LARGE_SPACE
    "E"             STR_COLON   "Exit Program"
};


/**
 * @brief 使用者能輸入的數字長度 (包含小數點)
 */
unsigned short const INPUT_FIELD_LENGTH = 9;

// the width of data panel
unsigned short const DATA_PANEL_WIDTH = 34;
// the height of data panel
unsigned short const DATA_PANEL_HEIGHT = 11;

// the length of info content
unsigned short const INFO_LENGTH = 89;
// the height of info panel
unsigned short const INFO_PANEL_HEIGHT = 3;

// the minimum width the screen can have
// unsigned short const SCREEN_MINIMUM_WIDTH = INFO_LENGTH + 2;  // 91
unsigned short const SCREEN_MINIMUM_WIDTH = 91;
// the minimum height the screen can have
// unsigned short const SCREEN_MINIMUM_HEIGHT = DATA_PANEL_HEIGHT + 2 + INFO_PANEL_HEIGHT;  // 16
unsigned short const SCREEN_MINIMUM_HEIGHT = 16;


// the frequncy that screen_input flash
static unsigned char const INPUT_FLASH_FREQUENCY = 16;



// ================================== clean ==================================

/**
 * @brief 把螢幕清空，這樣就能畫新東西了
 * 
 * @param screen 螢幕物件
 * @return 傳入的螢幕物件 or NULL(執行失敗)
 */
Screen clean_screen(Screen screen) {
    for (int y = 0; y < screen -> height; y++) {
        for (int x = 0; x < screen -> width; x++) {
            print_char(screen, (position){x, y}, CHAR_SPACE);
        }
        screen -> ground[y][screen -> width] = CHAR_ENDLINE;  // end of the string
    }

    screen -> empty_TF = true;
    return screen;
}



// ================================== draw ==================================

/**
 * @brief 把 單擺 畫出來
 * 
 * @param screen 螢幕物件
 * @param theta 單擺 和 X軸正向 的夾角
 * @param length 單擺的長度
 * @return 傳入的螢幕物件 or NULL(執行失敗)
 */
Screen draw_pendulum(Screen screen, double theta, double length) {
    position end_pos = {
        screen -> layout.pivot.x + (int)(cos(theta) * length), 
        screen -> layout.pivot.y + (int)(sin(theta) * length)
    };

    // body
    print_line(screen, screen -> layout.pivot, end_pos, screen -> pendulum_radius, '@', screen -> layout.pendulum_boundary);

    // start, end
    print_solid_circle(screen, end_pos               , screen -> pendulum_radius, '@', screen -> layout.pendulum_boundary);
    print_solid_circle(screen, screen -> layout.pivot, screen -> pendulum_radius, 'O', screen -> layout.pendulum_boundary);

    screen -> empty_TF = false;
    return screen;
}


/**
 * @brief 把 顯示當前數值的面板 畫出來
 * 
 * @param screen 螢幕物件
 * @param theta 單擺 和 X軸正向 的夾角
 * @param alpha 單擺的角加速度
 * @param omega 單擺的角速度
 * @param length 單擺的長度
 * @param mass 單擺的質量
 * @return 傳入的螢幕物件 or NULL(執行失敗)
 */
Screen draw_data_panel(Screen screen, char* theta, char* alpha, char* omega, char* length, char* mass) {
    char *input_data[5] = {theta, alpha, omega, length, mass};
    int data_panel_content_length = strlen(data_panel_contents[0]);
    position current_pos = {
        screen -> layout.data_panel.x + 1, 
        screen -> layout.data_panel.y + 1, 
    };

    // print
    for (int i = 0; i < 5; i++) {
        // print and move
        print_string(screen, current_pos, data_panel_contents[i], data_panel_content_length);
        current_pos.x += data_panel_content_length;
        print_string(screen, current_pos, input_data[i], INPUT_FIELD_LENGTH);

        // reset x
        current_pos.x = screen -> layout.data_panel.x + 1;

        // update y
        current_pos.y += 2;
    }

    screen -> empty_TF = false;
    return screen;
}


/**
 * @brief 把 等待輸入的符號 畫出來
 * @attention screen_input 只是把要印在哪點出來而已
 * 
 * @param screen 螢幕物件
 * @return 傳入的螢幕物件 or NULL(執行失敗) 
 */
Screen draw_screen_input(Screen screen) {
    if (screen -> input_name != NONE && flash_TF(screen)) {  // print input?
        position current_pos = {
            screen -> layout.data_panel.x + 1 + DATA_PANEL_WIDTH - INPUT_FIELD_LENGTH, 
            screen -> layout.data_panel.y + 1 + screen -> input_name * 2, 
        };
        for (int i = 0; i <= INPUT_FIELD_LENGTH; i++) {
            if (screen -> ground[current_pos.y][current_pos.x] == CHAR_SPACE) {
                print_char(screen, current_pos, CHAR_INPUT);
                screen -> empty_TF = false;
                return screen;
            }
            current_pos.x++;
        }
        return NULL;
    }
    return screen;
}


/**
 * @brief 把 顯示快捷鍵的面板 畫出來
 * 
 * @param screen 螢幕物件
 * @param name 顯示哪個面板
 * @return 傳入的螢幕物件 or NULL(執行失敗)
 */
Screen draw_info_panel(Screen screen, screen_info_name name) {
    // print info
    if (name != NO_INFO) {
        print_string(screen, screen -> layout.info_panel_content, info_content[name], strlen(info_content[name]));
    }

    // print ===
    for (int i = 0; i < screen -> width; i++) {
        print_char(screen, (position){i, screen -> layout.info_panel_content.y - 1}, CHAR_EQUAL);
        print_char(screen, (position){i, screen -> layout.info_panel_content.y + 1}, CHAR_EQUAL);
    }

    screen -> empty_TF = false;
    return screen;
}


/**
 * @brief 把 等待輸入的符號 畫出來
 * 
 * @param screen 螢幕物件
 * @param name 正在輸入哪個參數
 * @return 傳入的螢幕物件 or NULL(執行失敗)
 */
Screen screen_input(Screen screen, screen_input_name name) {
    screen -> input_name = name;
    if (name == NONE) {
        screen -> flash = 0;
    }
    return screen;
}


// return wheather to display the screen_input(flash) and update the value of flash
static bool flash_TF(Screen screen) {
    // check
    bool output = screen -> flash & INPUT_FLASH_FREQUENCY;
    // update
    screen -> flash++;
    // output
    return output;
}
