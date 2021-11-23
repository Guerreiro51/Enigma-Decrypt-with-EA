#ifndef REFLECTOR_H
#define REFLECTOR_H

using namespace std;
#include <string>

class Reflector{
    private:
    string  conections;
    
    public:
    Reflector(char type);
    int ReturnLetter(int input);
       
};
#endif