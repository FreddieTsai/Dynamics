/**
 * @file vector.cpp
 * @author IalvinchangI
 * @brief 定義 vector 運算 () (`vectors_angle`, `magnitude`) (, `dot_product`)
 * @version 0.4
 * @date 2024-07-07
 */


#include <math.h>  // sqrt, acos

#include "vector.h"  // vector


// return norm2 of vector v
double magnitude(vector v) {
    return sqrt(v.x * v.x + v.y * v.y);
}


/**
 * @brief compute the dot product between two vectors
 * @param v1 vector 1
 * @param v2 vector 2
 * @return dot product 
 */
static double dot_product(vector v1, vector v2) {
    return v1.x * v2.x + v1.y * v2.y;
}


/**
 * @brief compute the angle between two vectors
 * @param v1 vector 1
 * @param v2 vector 2
 * @return angle (rad)
 */
double vectors_angle(vector v1, vector v2) {
    return acos(dot_product(v1, v2) / (magnitude(v1) * magnitude(v2)));
}
