/**
 * @file graph.cpp
 * @author IalvinchangI
 * @brief 在螢幕上畫出字、圖 () (`print_string`, `print_line`, `print_char`) (`print_vertical_slice`, `print_horizontal_slice`, `in_boundary_TF`)
 * @version 0.4
 * @date 2024-07-06
 */


#include<stdio.h>
#include<stdbool.h>  // bool, true, false
#include<math.h>  // abs, acos

#include "screen_object.h"  // Screen
#include "vector.h"  // position, rectangle, vectors_angle

#include "graph.h"  // CHAR_ENDLINE
static void print_vertical_slice(Screen, position, int, char, rectangle);
static void print_horizontal_slice(Screen, position, int, char, rectangle);
static bool in_boundary_TF(position, rectangle);



// fill one cell by the character at pos
void print_char(Screen screen, position pos, char character) {
    screen -> ground[pos.y][pos.x] = character;
}


// put each char in the str onto the screen at pos
void print_string(Screen screen, position pos, char* str, int length) {
    printf("start print_string\n");
    for (int i = 0; i < length; i++) {
        if (str[i] == CHAR_ENDLINE) {
            return;
        }
        print_char(screen, (position){pos.x + i, pos.y}, str[i]);
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
    vector start_end = {end_pos.x - start_pos.x, end_pos.y - start_pos.y};

    // choose slice_function
    void (*slice_function)(Screen, position, int, char, rectangle);
    double angle = abs((PI / 2) - vectors_angle(start_end, (vector){1, 0}));
    if (angle <= (PI / 4)) {
        slice_function = print_horizontal_slice;
    }
    else {
        slice_function = print_vertical_slice;
    }

    // graph
    position current_pos = start_pos;
    int sx = (end_pos.x > current_pos.x) ? 1 : -1;  // x direction
    int sy = (end_pos.y > current_pos.y) ? 1 : -1;  // y direction
    int error = start_end.y - start_end.x;  // approaching to x-axis, it will decrease; approaching to y-axis, it will increase
    while (1) {
        slice_function(screen, current_pos, radius, color, boundary);  // graph the slice of line

        if (current_pos.x == end_pos.x && current_pos.y == end_pos.y) {  // reach the end point
            break;
        }

        if (error <= 0) {  // is closer to x-axis
            current_pos.x += sx;  // move 1 step horizontally (sx points to the direction of left/right)
            error += start_end.y;  // the line between end point and current point becomes closer to y-axis
        }
        if (error >= 0) {  // is closer to y-axis
            current_pos.y += sy;  // move 1 step vertically (sy points to the direction of up/down)
            error -= start_end.x;  // the line between end point and current point becomes closer to x-axis
        }
    }
}


static void print_vertical_slice(Screen screen, position center, int radius, char color, rectangle boundary) {
    for (int i = -radius; i <= radius; i++) {
        position current_pos = {center.x, center.y + i};
        if (in_boundary_TF(current_pos, boundary) == false) {  // out of boundary
            continue;
        }
        print_char(screen, current_pos, color);
    }
}

static void print_horizontal_slice(Screen screen, position center, int radius, char color, rectangle boundary) {
    for (int i = -radius; i <= radius; i++) {
        position current_pos = {center.x + i, center.y};
        if (in_boundary_TF(current_pos, boundary) == false) {  // out of boundary
            continue;
        }
        print_char(screen, current_pos, color);
    }
}


static bool in_boundary_TF(position pos, rectangle boundary) {
    return (boundary.top_left.x <= pos.x && pos.x < boundary.bottom_right.x) && (boundary.top_left.y <= pos.y && pos.y < boundary.bottom_right.y);
}
