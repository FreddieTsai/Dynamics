#ifndef PHYSICAL_INFO_H
    #define PHYSICAL_INFO_H

    /**
     * @param theta
     * @param alpha
     * @param omega
     * @param length
     * @param mass
     */
    typedef struct physical_info{
        double theta;
        double alpha;
        double omega;
        double length;
        double mass;
    } physical_info, *pphysical_info;
    
#endif