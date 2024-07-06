/**
 * @file vector.h
 * @author IalvinchangI
 * @brief 定義 `PI`, `position`, `vector`及其運算(`vectors_angle`), `rectangle`
 * @version 0.5
 * @date 2024-07-06
 */


#ifndef vector_H_
    #define vector_H_


    #define PI (3.141592653589)

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
