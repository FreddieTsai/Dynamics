/**
 * @file vector.cpp
 * @author IalvinchangI
 * @brief 定義 vector 運算 () (`magnitude`, `dot_product`) ()
 * @version 0.1
 * @date 2024-07-05
 */


#include <math.h>  // sqrt

#include <__vector.h>  // vector


// return norm2 of vector v
double magnitude(vector v) {
    return sqrt(v[0] * v[0] + v[1] * v[1]);
}


/**
 * @brief compute the dot product between two vectors
 * @param v1 vector 1
 * @param v2 vector 2
 * @return dot product 
 */
double dot_product(vector v1, vector v2) {
    return v1[0] * v2[0] + v1[1] * v2[1];
}
