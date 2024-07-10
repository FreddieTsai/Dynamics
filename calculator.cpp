#include <iostream>
#include <math.h>

using namespace std;


double angSpeed (double length, double degree){ 
    //length: 棍子的長度
    //degree: 棍子跟x軸正向夾角
    double squareOfAngSpeed,  AngSpeed;
    squareOfAngSpeed = 3 * 9.81 * sin(degree) / length; // 先算角速度的平方
    AngSpeed = pow(squareOfAngSpeed, 0.5); // 算出角速度值
    return AngSpeed;
}

double angAcceler (double length, double degree){
    //length: 棍子的長度
    //degree: 棍子跟x軸正向夾角
    double AngAcceler;
    AngAcceler = 1.5 * 9.81 * cos(degree) / length;  // 算角加速度
    return AngAcceler;
}


double calculateDegree (double length, double degree, double time){
    //length: 棍子的長度
    //degree: 棍子跟x軸正向夾角
    if( length == 0){
        cout << "Invalid input of the length of the rod." << endl;
        cout << "The length of the stick is nonzero." << endl;
        return 0;
    }
      
    // t 為單位時間
    // 設定單位時間 t = 0.0001

    degree = angSpeed(length, degree ) * time + 0.5 * angAcceler(length, degree) * time * time;
    return degree;
}