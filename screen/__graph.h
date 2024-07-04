/**
 * @file __graph.h
 * @author IalvinchangI
 * @brief 在螢幕上畫出字、圖 () (`print_string`, `print_line`)
 * @version 0.1
 * @date 2024-07-04
 */


#ifndef __graph_H_
    #define __graph_H_

    #include "__vector.h"  // position

    void print_string(position pos, char* str);

    void print_line(position start_pos, position end_pos, int width, char* color);

#endif
