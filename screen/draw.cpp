/**
 * @file draw.cpp
 * @author IalvinchangI
 * @brief 畫各個面板 (`clean_screen`, `draw_pendulum`, `draw_data_panel`, `screen_input`) (`draw_info_panel`) ()
 * @version 0.2
 * @date 2024-07-05
 */


#include<stdlib.h>  // NULL
#include<string.h>  // strlen
#include<math.h>  // cos, sin
#include<stdbool.h>  // true, false

#include "__screen_object.h"  // Screen, Layout, screen_input_name
#include "__vector.h"  // position, rectangle
#include "__graph.h"  // all



// ================================== constant ==================================

#define STR_THETA   "Angle"
#define STR_ALPHA   "Angular Acceleration"
#define STR_OMEGA   "Angular Velocity"
#define STR_LENGTH  "Length"
#define STR_MASS    "Mass"

static char *data_panel_contents[5] = {
    STR_THETA  "               "    STR_EQUAL, 
    STR_ALPHA  ""                   STR_EQUAL, 
    STR_OMEGA  "    "               STR_EQUAL, 
    STR_LENGTH "              "     STR_EQUAL, 
    STR_MASS   "                "   STR_EQUAL
};
static int data_panel_content_length = strlen(data_panel_contents[0]);

static char *info_content = "insert"   STR_COLON "I"           STR_SMALL_SPACE
                            STR_THETA  STR_COLON "T"           STR_SMALL_SPACE
                            STR_ALPHA  STR_COLON "A"           STR_SMALL_SPACE
                            STR_OMEGA  STR_COLON "W"           STR_LARGE_SPACE
                            "pause"    STR_COLON "P"           STR_LARGE_SPACE
                            "continue" STR_COLON "C"           STR_LARGE_SPACE
                            "end"      STR_COLON "E | ctrl+c"
;
static int info_content_length = strlen(info_content);


/**
 * @brief 使用者能輸入的數字長度 (包含小數點)
 */
unsigned short const INPUT_FIELD_LENGTH = 9;

// the width of data panel
unsigned short const DATA_PANEL_WIDTH = 34;
// the height of data panel
unsigned short const DATA_PANEL_HEIGHT = 11;

// the length of info content
unsigned short const INFO_LENGTH = 108;
// the height of info panel
unsigned short const INFO_PANEL_HEIGHT = 3;

// the minimum width the screen can have
unsigned short const SCREEN_MINIMUM_WIDTH = INFO_LENGTH + 2;  // 110
// the minimum height the screen can have
unsigned short const SCREEN_MINIMUM_HEIGHT = DATA_PANEL_HEIGHT + 2 + INFO_PANEL_HEIGHT;  // 16



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
        screen -> layout.pivot[0] + (int)( cos(theta) * length), 
        screen -> layout.pivot[1] + (int)(-sin(theta) * length)
    };

    // body
    print_line(screen, screen -> layout.pivot, end_pos, 5, '@', screen -> layout.pendulum_boundary);

    // start, end
    // TODO print_circle

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
    position current_pos = {
        screen -> layout.data_panel[0] + 1, 
        screen -> layout.data_panel[1] + 1, 
    };

    // print
    for (int i = 0; i < 5; i++) {
        // update y
        current_pos[1] += i * 2;

        // print and move
        print_string(screen, current_pos, data_panel_contents[i], data_panel_content_length);
        current_pos[0] += data_panel_content_length;
        print_string(screen, current_pos, input_data[i], INPUT_FIELD_LENGTH);
        
        if ((screen -> input_name != NONE) && (i == screen -> input_name)) {  // print input?
            int input_length = strlen(input_data[i]);
            current_pos[0] += (input_length <= INPUT_FIELD_LENGTH ? input_length : INPUT_FIELD_LENGTH);
            print_char(screen, current_pos, CHAR_INPUT);
        }

        // reset x
        current_pos[0] = screen -> layout.data_panel[0] + 1;
    }

    screen -> empty_TF = false;
    return screen;
}


/**
 * @brief 把 顯示快捷鍵的面板 畫出來
 * 
 * @param screen 螢幕物件
 * @return 傳入的螢幕物件 or NULL(執行失敗)
 */
Screen draw_info_panel(Screen screen) {
    print_string(screen, screen -> layout.info_panel_content, info_content, info_content_length);

    screen -> empty_TF = false;
    return screen;
}


/**
 * @brief 把 等待輸入的符號(I) 畫出來
 * 
 * @param screen 螢幕物件
 * @param name 正在輸入哪個參數
 * @return 傳入的螢幕物件 or NULL(執行失敗)
 */
Screen screen_input(Screen screen, screen_input_name name) {
    screen -> input_name = name;
    return screen;
}
