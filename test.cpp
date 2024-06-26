#include <iostream>
#include<cmath>
#include<iomanip>
//Ex17.11

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
    cout << "Angular Velocity" << "    " << "Angualar Acceleration";
    do{
        AngAcceler = 1.5 * 9.81 * cos(degree) / length;
        double squareOfAngSpeed;
        squareOfAngSpeed = 3 * 9.81 * sin(degree) / length;
        AngSpeed = pow(squareOfAngSpeed, 0.5); 
        degree += ((1 / 180) * pi);
        cout << setw(5) << AngSpeed << setw(5) << AngAcceler << endl;
    } while (degree == terminalDegree);
    return 0;
}