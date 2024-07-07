/**
 * @file vector.h
 * @author IalvinchangI
 * @brief 定義 `position`, `vector`及其運算(`vectors_angle`), `rectangle`
 * @version 0.6
 * @date 2024-07-07
 */


#ifndef vector_H_
    #define vector_H_

    /**
     * @brief 螢幕座標 (x, y)
     */
    typedef struct {
        int x;
        int y;
    } position;


    /**
     * @brief 向量 (x, y)
     */
    typedef struct {
        double x;
        double y;
    } vector;

    #ifdef __cplusplus
    extern "C" {
    #endif

        double magnitude(vector v);
        double vectors_angle(vector v1, vector v2);

    #ifdef __cplusplus
    }
    #endif


    /**
     * @brief (左上角座標, 右下角座標)
     */
    typedef struct {
        position top_left;
        position bottom_right;
    } rectangle;

#endif
