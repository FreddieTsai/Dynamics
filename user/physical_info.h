#ifndef PHYSICAL_INFO_H
    #define PHYSICAL_INFO_H

    const size_t DOUBLE_NUMBER_DIGITS = 32;  // maximun number of digits of physical variables

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