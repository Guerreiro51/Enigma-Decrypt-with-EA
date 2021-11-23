#include "Reflector.h"

Reflector::Reflector(char type)
{
    switch (type)
    {
    case 'A':
        this->conections = "EJMZALYXVBWFCRQUONTSPIKHGD";
        break;
    case 'B':
        this->conections = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
        break;
    case 'C':
        this->conections = "FVPJIAOYEDRZXWGCTKUQSBNMHL";
        break;
     
    default:
        this->conections = "ZYXWVUTSRQPONMLKJIHGFEDCBA";
        break;
    }
}

int Reflector::ReturnLetter(int input)
{
    return (int)this->conections[input] -65;
}