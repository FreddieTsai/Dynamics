#include <iostream>
#include<cmath>
#include<iomanip>
//Ex17.11 棍子一端固定，從0度開始往下掉到一角度停止並且顯示影像

double angSpeed (double length, double degree);
double angAcceler (double length, double degree);

using namespace std;

int main() {
    const double pi = 3.1415926535;
    double mass = 0, length = 0, /*initialDegree = 0*/ terminalDegree = 0, AngSpeed = 0, degree = 0, AngAcceler = 0;
    double location = 0;
    cout << "Please enter the mass." << endl;
    cin >> mass;
    cout << "Please enter the length." << endl;
    cin >> length;
    cout << "Please enter the terminal degree";
    cin >> terminalDegree; 
    terminalDegree = (terminalDegree / 180) * pi;
    //degree = initialDegree;
    //t = 0.01, t是時間
    while( degree < terminalDegree){
        degree = angSpeed(length, degree) * 0.01 + 0.5 * angAcceler(length, degree) *0.0001;
    }
    //問題 : degree 代表著不同的位置，每試驗因為結束位置不一樣，要怎麼樣有一個伸縮自如的儲存空間
    return 0;
}

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