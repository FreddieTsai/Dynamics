#include <iostream>
#include "calculator.h"

double angSpeed (double length, double degree){ 
    double squareOfAngSpeed,  AngSpeed;
    squareOfAngSpeed = 3 * 9.81 * sin(degree) / length;
    AngSpeed = pow(squareOfAngSpeed, 0.5); 
    return AngSpeed;
}

double angAcceler (double length, double degree){
    double AngAcceler;
    AngAcceler = 1.5 * 9.81 * cos(degree) / length;
    return AngAcceler;
}

double calculateDegree (double length, double degree){
    double t = 0.0001;
    degree = angSpeed(length, degree ) * t + 0.5 * angAcceler(length, degree) * t * t;
    return degree;
}