#ifndef PHYSICAL_INFO_H
    #define PHYSICAL_INFO_H

    #include "..\screen\PI.h"

    /**
     * @param theta
     * @param terminal_angle
     * @param alpha
     * @param omega
     * @param length
     * @param time
     */
    typedef struct physical_info{
        double theta;
        double terminal_angle;
        double alpha;
        double omega;
        double length;
        double time;
    } physical_info, *pphysical_info;
    
#endif