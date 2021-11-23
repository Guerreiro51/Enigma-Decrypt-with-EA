#include "Enigma.h"


Enigma::Enigma(vector<int> rotor_types, char reflector_type, vector<int>  rotor_start_positions, vector<int> rotor_ring_settings,vector<string> plugconnecetions)
{
    int i;

    this->plugboard = new PlugBoard(plugconnecetions);
    this->reflector = new Reflector(reflector_type);

    for(i=0;i<3;i++)
        this->rotors.push_back (new Rotor(rotor_types[i],rotor_start_positions[i],rotor_ring_settings[i]));
}

void Enigma::Rotate()
{
    if(this->rotors[1]->IsAtNotch())
    {
        this->rotors[0]->Rotate();
        this->rotors[1]->Rotate();
    }
    else if (this->rotors[2]->IsAtNotch())
        {
            this->rotors[1]->Rotate();
        }
    // if (this->rotors[2]->IsAtNotch())
    // {
    //     this->rotors[1]->Rotate();
    // }

    this->rotors[2]->Rotate();

}

char Enigma::Encrypt(char letter)
{
    this->Rotate();

    int caracter = (int)letter - 65;

    // caracter = this->plugboard->ReturnLetter(caracter);

    cout << "Primeira PlugBoard: " << (char)(caracter+65) << endl;

    caracter = this->rotors[2]->Forward(caracter);

    cout << "Primeira Rotor: " << (char)(caracter+65) << endl;

    caracter = this->rotors[1]->Forward(caracter);

    cout << "Segundo Rotor: " << (char)(caracter+65) << endl;

    caracter = this->rotors[0]->Forward(caracter);

    cout << "Terceiro Rotor: " << (char)(caracter+65) << endl;

    caracter = this->reflector->ReturnLetter(caracter);

    caracter = this->rotors[0]->Backward(caracter);
    caracter = this->rotors[1]->Backward(caracter);
    caracter = this->rotors[2]->Backward(caracter);

    caracter = this->plugboard->ReturnLetter(caracter);

    caracter = caracter+65;
    letter = (char)caracter;

    return letter;

}

