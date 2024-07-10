/**
 * @file screen_info_name.h
 * @author IalvinchangI
 * @brief 定義 `draw_info_panel` 的參數
 * @version 0.1
 * @date 2024-07-10
 */



#ifndef screen_info_name_H_
    #define screen_info_name_H_

    /**
     * @brief 適用於`draw_info_panel`的參數
     * `DEFAULT_MODE` : default mode
     * `INSERT_MODE`  : insert mode
     * `NO_INFO`      : 沒有 info
     */
    typedef enum __screen_info_name {
        NO_INFO = -1,   // 沒有 info
        DEFAULT_MODE,   // default mode
        INSERT_MODE     // insert mode
    } screen_info_name;
#endif