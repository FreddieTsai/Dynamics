/**
 * @file __screen_input_name.h
 * @author IalvinchangI
 * @brief 定義 `screen_input` 的參數
 * @version 0.1
 * @date 2024-07-03
 */


/**
 * @brief 適用於`screen_input`的參數
 * `THETA`  : 單擺 和 X軸正向 的夾角
 * `ALPHA`  : 單擺的角加速度
 * `OMEGA`  : 單擺的角速度
 * `LENGTH` : 單擺的長度
 * `MASS`   : 單擺的質量
 */
typedef enum __screen_input_name {
    THETA, 
    ALPHA, 
    OMEGA, 
    LENGTH, 
    MASS 
} screen_input_name;