/**
 * @file screen.h
 * @author IalvinchangI
 * @brief 處理螢幕顯示
 * @version 0.1
 * @date 2024-07-03
 */


// ======================== Data Type ========================

/**
 * 螢幕指標，記錄了所有和螢幕顯示有關的資訊
 */
typedef struct _screen raw_screen;

/**
 * 螢幕物件，記錄了所有和螢幕顯示有關的資訊
 */
typedef raw_screen* Screen;


#include "__screen_input_name.h"



// ======================== Function ========================

/**
 * @brief 用來初始化 螢幕物件(`Screen`)
 * @return 初始化好的物件
 */
Screen create_screen();

/**
 * @brief 用來初始化 螢幕物件(`Screen`)
 * 
 * @param screen_width 螢幕顯示範圍的高度
 * @param screen_height 螢幕顯示範圍的寬度
 * @return 初始化好的物件
 */
Screen create_screen(int screen_width, int screen_height);


/**
 * @brief 根據視窗當前大小來設定顯示範圍
 * @attention 執行此函式會把螢幕清空
 */
void set_screen_size();

/**
 * @brief 用來設定顯示範圍
 * @attention 執行此函式會把螢幕清空
 * 
 * @param screen_width 螢幕顯示範圍的高度
 * @param screen_height 螢幕顯示範圍的寬度
 */
void set_screen_size(int screen_width, int screen_height);


/**
 * @brief 把螢幕清空，這樣就能畫新東西了
 */
void clean_screen();


/**
 * @brief 把 單擺 畫出來
 * 
 * @param theta 單擺 和 X軸正向 的夾角
 * @param length 單擺的長度
 */
void draw_pendulum(double theta, double length);


/**
 * @brief 把 顯示當前數值的面板 畫出來
 * 
 * @param theta 單擺 和 X軸正向 的夾角
 * @param alpha 單擺的角加速度
 * @param omega 單擺的角速度
 * @param length 單擺的長度
 * @param mass 單擺的質量
 */
void draw_data_panel(char* theta, char* alpha, char* omega, char* length, char* mass);


/**
 * @brief 把 等待輸入的符號(I) 畫出來
 * 
 * @param name 正在輸入哪個參數
 */
void screen_input(screen_input_name name);


/**
 * @brief 把 螢幕上的內容 顯示出來
 */
void screen_show();
