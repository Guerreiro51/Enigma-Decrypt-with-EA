#ifndef ROTOR_H
#define ROTOR_H

using namespace std;
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <array>

class Rotor{
    private:
    int type;
    int notch;
    int ringsetting;
    array<int,26> conections;
    array<int,26> reverseconections;
    int currentposition;

    public:
    Rotor(int type,int currentposition,int ringsetting);
    int Forward(int input);
    int Backward(int input);
    void SetupConnections(string arrangement);
    bool IsAtNotch();
    void Rotate();
};
#endif