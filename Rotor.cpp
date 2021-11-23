#include "Rotor.h"

Rotor::Rotor(int type,int currentposition,int ringsetting)
{
    this->type = type;
    this->currentposition = currentposition;
    this->ringsetting = ringsetting;

    switch (type)
    {
    case 1:
        this->SetupConnections("EJMZALYXVBWFCRQUONTSPIKHGD");
        this->notch = 16;
        break;

    case 2:
        this->SetupConnections("YRUHQSLDPXNGOKMIEBFZCWVJAT");
        this->notch = 4;
        break;

    case 3:
        this->SetupConnections("FVPJIAOYEDRZXWGCTKUQSBNMHL");
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
    // if(this->type == 1)
    //     cout << "Input rotor " << this->type << ": " << input << endl;
 
    int shift = this->currentposition - this->ringsetting;

    // if(this->type == 1)
    //     cout << "Shift rotor " << this->type << ": " << shift << endl;

    // if(this->type == 1)
    //     cout << "Saida rotor " << this->type << ": " << (char) (this->conections[(input + shift + 26) % 26]+65)<< endl;

    // return  (this->conections[(input + shift + 26) % 26] - shift + 26) % 26;
    return  this->conections[(input + shift + 26) % 26];
}

int Rotor::Backward(int input)
{
    int shift = this->currentposition - this->ringsetting;
    // return  (this->reverseconections[(input + shift + 26) % 26] - shift + 26) % 26;
    return  this->reverseconections[(input + shift + 26) % 26];
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
        this->conections.push_back(arrangement[i]-65);
        this->reverseconections.push_back(arrangement[25-i]-65);
    }


}