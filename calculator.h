#ifndef CALCULATOR_H
#define CALCULATOR_H
#endif

//length: 棍子的長度
//degree: 棍子跟x軸正向夾角

double angSpeed (double length, double degree, double time);  
//運算角速度，回傳角速度給calculateDegree

double angAcceler (double length, double degree, double time); 
//運算角加速度，回傳角加速度給calculateDegree

double calculateDegree (double length, double degree, double time);
//運算棍落下的每個單位時間的棍子與x軸正向夾角回傳給main