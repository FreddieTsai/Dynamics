/**
 * @file __graph.h
 * @author IalvinchangI
 * @brief 在螢幕上畫出字、圖，以及一些常用的符號 () (`print_string`, `print_line`, `print_char`)
 * @version 0.3
 * @date 2024-07-05
 */


#ifndef __graph_H_
    #define __graph_H_

    #include "__vector.h"  // position, rectangle


    // useful word

    #define CHAR_SPACE      ' '
    #define CHAR_ENDLINE    '\0'
    #define CHAR_EQUAL      '='

    #define CHAR_INPUT      'I'

    #define STR_COLON       ": "
    #define STR_SMALL_SPACE "  "
    #define STR_LARGE_SPACE "   "
    #define STR_EQUAL       " = "


    // function

    void print_char(Screen screen, position pos, char character);

    void print_string(Screen screen, position pos, char* str, int length);

    void print_line(Screen screen, position start_pos, position end_pos, int width, char color, rectangle boundary);

#endif
