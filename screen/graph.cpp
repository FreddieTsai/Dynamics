/**
 * @file graph.cpp
 * @author IalvinchangI
 * @brief 在螢幕上畫出字、圖 () (`print_string`, `print_line`, `print_char`) (`print_vertical_slice`, `print_horizontal_slice`, `in_boundary_TF`)
 * @version 0.3
 * @date 2024-07-05
 */


#include<stdbool.h>  // bool, true, false
#include<math.h>  // abs, acos

#include "__screen_object.h"  // Screen
#include "__vector.h"  // position, rectangle, vectors_angle

#include "__graph.h"  // CHAR_ENDLINE
void print_vertical_slice(Screen, position, int, char, rectangle);
void print_horizontal_slice(Screen, position, int, char, rectangle);
bool in_boundary_TF(position, rectangle);



// fill one cell by the character at pos
void print_char(Screen screen, position pos, char character) {
    screen -> ground[pos[1]][pos[0]] = character;
}


// put each char in the str onto the screen at pos
void print_string(Screen screen, position pos, char* str, int length) {
    for (int i = 0; i < length; i++) {
        if (str[i] == CHAR_ENDLINE) {
            return;
        }
        print_char(screen, (position){pos[0] + i, pos[1]}, str[i]);
    }
}


/**
 * @brief draw a line between start_pos and end_pos
 * 
 * @param screen screen object
 * @param start_pos where the line start
 * @param end_pos where the line end
 * @param width the width of the line
 * @param color the color of the line ('{a char you want to print}')
 * @param boundary the area that can be drawn
 */
void print_line(Screen screen, position start_pos, position end_pos, int width, char color, rectangle boundary) {
    int radius = width / 2;
    vector start_end = {end_pos[0] - start_pos[0], end_pos[1] - start_pos[1]};
    vector unit_start_end = normalize(start_end);

    // choose slice_function
    void (*slice_function)(Screen, position, int, char, rectangle);
    double angle = abs((PI / 2) - acos(dot_product(unit_start_end, (vector){1, 0})));
    if (angle <= (PI / 4)) {
        slice_function = print_horizontal_slice;
    }
    else {
        slice_function = print_vertical_slice;
    }

    // graph
}


void print_vertical_slice(Screen screen, position center, int radius, char color, rectangle boundary) {
    for (int i = -radius; i <= radius; i++) {
        position current_pos = {center[0], center[1] + i};
        if (in_boundary_TF(current_pos, boundary) == false) {  // out of boundary
            continue;
        }
        print_char(screen, current_pos, color);
    }
}

void print_horizontal_slice(Screen screen, position center, int radius, char color, rectangle boundary) {
    for (int i = -radius; i <= radius; i++) {
        position current_pos = {center[0] + i, center[1]};
        if (in_boundary_TF(current_pos, boundary) == false) {  // out of boundary
            continue;
        }
        print_char(screen, current_pos, color);
    }
}


bool in_boundary_TF(position pos, rectangle boundary) {
    return (boundary[0][0] <= pos[0] && pos[0] < boundary[1][0]) && (boundary[0][1] <= pos[1] && pos[1] < boundary[1][1]);
}
