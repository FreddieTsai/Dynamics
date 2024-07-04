/**
 * @file draw.cpp
 * @author IalvinchangI
 * @brief 畫各個面板 (`clean_screen`, `draw_pendulum`, `draw_data_panel`, `screen_input`) (`draw_info_panel`) ()
 * @version 0.1
 * @date 2024-07-04
 */


#include<stdlib.h>  // NULL
#include<string.h>
#include<stdbool.h>  // true, false

#include "__screen_object.h"  // Screen, Layout, screen_input_name
#include "__vector.h"  // position
#include "__graph.h"  // all


// ================================== clean ==================================

/**
 * @brief 把螢幕清空，這樣就能畫新東西了
 * 
 * @param screen 螢幕物件
 * @return 傳入的螢幕物件 or NULL(執行失敗)
 */
Screen clean_screen(Screen screen) {
    // TODO

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
    // TODO

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
    // TODO

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
    // TODO

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
    // TODO

    screen -> empty_TF = false;
    return screen;
}
