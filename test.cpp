#include <iostream>
#include<cmath>
#include<iomanip>
//Ex17.11

double angSpeed (double length, double degree);
double angAcceler (double length, double degree);

using namespace std;

int main() {
    const double pi = 3.1415926535;
    double mass = 0, length = 0, initialDegree = 0, terminalDegree = 0, AngSpeed = 0, degree = 0, AngAcceler = 0;
    cout << "Please enter the mass." << endl;
    cin >> mass;
    cout << "Please enter the length." << endl;
    cin >> length;
    cout << "Please enter the initial degree";
    cin >> initialDegree; 
    initialDegree = (initialDegree / 180) * pi;
    cout << "Please enter the terminal degree";
    cin >> terminalDegree; 
    terminalDegree = (terminalDegree / 180) * pi;
    degree = initialDegree;
    cout << angSpeed (length, degree) << endl;
    cout <<  angAcceler(length, degree) << endl;
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