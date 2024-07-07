#include <iostream>
#include <math.h>

//length: 棍子的長度
//degree: 棍子跟x軸正向夾角
double angSpeed (double length, double degree){ 
    double squareOfAngSpeed,  AngSpeed;
    squareOfAngSpeed = 3 * 9.81 * sin(degree) / length; // 先算角速度的平方
    AngSpeed = pow(squareOfAngSpeed, 0.5); // 算出角速度值
    return AngSpeed;
}

//length: 棍子的長度
//degree: 棍子跟x軸正向夾角
double angAcceler (double length, double degree){
    double AngAcceler;
    AngAcceler = 1.5 * 9.81 * cos(degree) / length;  // 算角加速度
    return AngAcceler;
}

//length: 棍子的長度
//degree: 棍子跟x軸正向夾角
double calculateDegree (double length, double degree){
    
    double t = 0.0001;  
    // t 為單位時間
    // 設定單位時間 t = 0.0001

    degree = angSpeed(length, degree ) * t + 0.5 * angAcceler(length, degree) * t * t;
    return degree;
}