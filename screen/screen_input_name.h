/**
 * @file screen_input_name.h
 * @author IalvinchangI
 * @brief 定義 `screen_input` 的參數
 * @version 0.6
 * @date 2024-07-12
 */


#ifndef screen_input_name_H_
    #define screen_input_name_H_

    /**
     * @brief 適用於`screen_input`的參數
     * `THETA`          : 單擺 和 X軸正向 的夾角
     * `ALPHA`          : 單擺的角加速度
     * `OMEGA`          : 單擺的角速度
     * `LENGTH`         : 單擺的長度
     * `TIME`           : 時間差
     * `TERMINAL_ANGLE` : 終端角度
     * `NONE`           : 沒在輸入
     */
    typedef enum __screen_input_name {
        NONE = -1,       // 沒在輸入
        THETA,           // 單擺 和 X軸正向 的夾角
        TERMINAL_ANGLE,  // 終端角度
        ALPHA,           // 單擺的角加速度
        OMEGA,           // 單擺的角速度
        LENGTH,          // 單擺的長度
        TIME,            // 時間差
    } screen_input_name;
#endif