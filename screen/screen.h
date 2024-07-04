/**
 * @file screen.h
 * @author IalvinchangI
 * @brief 處理螢幕顯示
 * @version 0.4
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


    /**
     * @brief 把螢幕清空，這樣就能畫新東西了
     * 
     * @param screen 螢幕物件
     * @return 傳入的螢幕物件 or NULL(執行失敗)
     */
    Screen clean_screen(Screen screen);


    /**
     * @brief 把 單擺 畫出來
     * 
     * @param screen 螢幕物件
     * @param theta 單擺 和 X軸正向 的夾角
     * @param length 單擺的長度
     * @return 傳入的螢幕物件 or NULL(執行失敗)
     */
    Screen draw_pendulum(Screen screen, double theta, double length);


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
    Screen draw_data_panel(Screen screen, char* theta, char* alpha, char* omega, char* length, char* mass);


    /**
     * @brief 把 等待輸入的符號(I) 畫出來
     * 
     * @param screen 螢幕物件
     * @param name 正在輸入哪個參數
     * @return 傳入的螢幕物件 or NULL(執行失敗)
     */
    Screen screen_input(Screen screen, screen_input_name name);


    /**
     * @brief 把 螢幕上的內容 顯示出來
     * 
     * @param screen 螢幕物件
     * @return 傳入的螢幕物件 or NULL(執行失敗)
     */
    Screen screen_show(Screen screen);

#endif
