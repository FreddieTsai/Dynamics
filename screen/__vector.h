/**
 * @file __vector.h
 * @author IalvinchangI
 * @brief 定義 `PI`, `position`, `vector`及其運算(`magnitude`, `dot_product`, `normalize`), `rectangle`
 * @version 0.3
 * @date 2024-07-05
 */


#ifndef __vector_H_
    #define __vector_H_


    #define PI (3.141592653589)

    /**
     * @brief 螢幕座標 (x, y)
     */
    typedef int position[2];


    /**
     * @brief 向量 (x, y)
     */
    typedef double vector[2];

    double magnitude(vector v);
    double dot_product(vector v1, vector v2);

    #define normalize(v) {v[0] / magnitude(v), v[1] / magnitude(v)}


    /**
     * @brief (左上角座標, 右下角座標)
     */
    typedef position rectangle[2];

#endif
