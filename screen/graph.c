/**
 * @file graph.cpp
 * @author IalvinchangI
 * @brief 在螢幕上畫出字、圖 () (`print_string`, `print_line`, `print_solid_circle`, `print_char`) (`print_vertical_slice`, `print_horizontal_slice`, `in_boundary_TF`)
 * @version 0.5
 * @date 2024-07-07
 */


#include<stdbool.h>  // bool, true, false
#include<math.h>  // abs, acos

#include "screen_object.h"  // Screen
#include "vector.h"  // position, rectangle, vectors_angle, magnitude
#include "PI.h"  // PI

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
    for (int i = 0; i < length; i++) {
        if (str[i] == CHAR_ENDLINE) {
            return;
        }
        print_char(screen, (position){pos.x + i, pos.y}, str[i]);
    }
}


/**
 * @brief draw a solid circle according to the given radius and position
 * 
 * @param screen screen object
 * @param center the position of the center fo the circle
 * @param radius the radius of the circle
 * @param color the color of the circle ('{a char you want to print}')
 * @param boundary the area that can be drawn
 */
void print_solid_circle(Screen screen, position center, int radius, char color, rectangle boundary) {
    int slice_radius = 0;
    double error_radius = radius + 0.2;
    for (int delta_y = radius; delta_y > 0; delta_y--) {  // change the horizontal line
        for (; slice_radius <= radius + 1; slice_radius++) {  // find arc
            if (magnitude((vector){slice_radius, delta_y}) > error_radius) {  // point(delta_x, slice_radius) is out of circle
                // fill
                print_horizontal_slice(screen, (position){center.x, center.y - delta_y}, slice_radius - 1, color, boundary);
                print_horizontal_slice(screen, (position){center.x, center.y + delta_y}, slice_radius - 1, color, boundary);
                break;
            }
        }
    }
    print_horizontal_slice(screen, center, radius, color, boundary);  // delta_x = 0
}


/**
 * @brief draw a line between start_pos and end_pos
 * 
 * @param screen screen object
 * @param start_pos where the line start
 * @param end_pos where the line end
 * @param radius the radius of the line
 * @param color the color of the line ('{a char you want to print}')
 * @param boundary the area that can be drawn
 */
void print_line(Screen screen, position start_pos, position end_pos, int radius, char color, rectangle boundary) {
    vector abs_start_end = {abs(end_pos.x - start_pos.x), abs(end_pos.y - start_pos.y)};

    // choose slice_function
    void (*slice_function)(Screen, position, int, char, rectangle);
    double angle = vectors_angle(abs_start_end, (vector){1, 0});
    if (angle >= (PI / 4)) {
        slice_function = print_horizontal_slice;
    }
    else {
        slice_function = print_vertical_slice;
    }

    // print line
    position current_pos = start_pos;
    int sx = (end_pos.x > current_pos.x) ? 1 : -1;  // x direction
    int sy = (end_pos.y > current_pos.y) ? 1 : -1;  // y direction
    int error = abs_start_end.y - abs_start_end.x;  // approaching to x-axis, it will decrease; approaching to y-axis, it will increase
    while (1) {
        slice_function(screen, current_pos, radius, color, boundary);  // graph the slice of line

        if (current_pos.x == end_pos.x && current_pos.y == end_pos.y) {  // reach the end point
            break;
        }

        if (error <= 0) {  // is closer to x-axis
            current_pos.x += sx;  // move 1 step horizontally (sx points to the direction of left/right)
            error += abs_start_end.y;  // the line between end point and current point becomes closer to y-axis
        }
        if (error >= 0) {  // is closer to y-axis
            current_pos.y += sy;  // move 1 step vertically (sy points to the direction of up/down)
            error -= abs_start_end.x;  // the line between end point and current point becomes closer to x-axis
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
