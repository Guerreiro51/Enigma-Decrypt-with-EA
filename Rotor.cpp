#include "Rotor.h"

Rotor::Rotor(int type,int currentposition,int ringsetting)
{
    this->type = type;
    this->currentposition = currentposition;
    this->ringsetting = ringsetting;

    switch (type)
    {
    case 1:
        this->SetupConnections("EKMFLGDQVZNTOWYHXUSPAIBRCJ");
        this->notch = 16;
        break;

    case 2:
        this->SetupConnections("AJDKSIRUXBLHWTMCQGZNPYFVOE");
        this->notch = 4;
        break;

    case 3:
        this->SetupConnections("BDFHJLCPRTXVZNYEIWGAKMUSQO");
        this->notch = 21;
        break;
    case 4:
        this->SetupConnections("ESOVPZJAYQUIRHXLNFTGKDCMWB");
        this->notch = 9;
        break;

    case 5:
        this->SetupConnections("VZBRGITYUPSDNHLXAWMJQOFECK");
        this->notch = 25;
        break;

    //Double Notch
    case 6:
        this->SetupConnections("JPGVOUMFYQBENHZRDKASXLICTW");
        break;

    //Double Notch
    case 7:
        this->SetupConnections("NZJHGRCXMYSWBOUFAIVLPEKQDT");
        break;

    //Double Notch
    case 8:
        this->SetupConnections("FKQHTLXOCBJSPDZRAMEWNIUYGV");
        break;

    default:
        this->SetupConnections("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        this->notch = 0;
        break;
    }
}

int Rotor::Forward(int input)
{ 
    int shift = this->currentposition - this->ringsetting;

    return  (this->conections[(input + shift + 26) % 26] - shift + 26) % 26;
}

int Rotor::Backward(int input)
{
    int shift = this->currentposition - this->ringsetting;
    
    return  (this->reverseconections[(input + shift + 26) % 26] - shift + 26) % 26;
    
}


bool Rotor::IsAtNotch()
{
    if(this->type > 5)
    {
        return currentposition == 25 || currentposition == 12;
    }
    return currentposition == this->notch;

}

 void Rotor::Rotate()
 {
    this->currentposition =  (this->currentposition + 1) % 26;
 }

void Rotor::SetupConnections(string arrangement)
{
    int i;

    for(i=0;i<26;i++)
    {
        this->conections[i]=(arrangement[i]-65);
        this->reverseconections[arrangement[i]-65] = i;
    }

}