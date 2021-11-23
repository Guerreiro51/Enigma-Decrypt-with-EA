#ifndef ENIGMA_H
#define ENIGMA_H

using namespace std;

#include "Reflector.h"
#include "Rotor.h"
#include "PlugBoard.h"
#include <vector>


class Enigma{
    private:
    vector<Rotor*> rotors;
    PlugBoard* plugboard;
    Reflector* reflector;
    
    public:
    Enigma(vector<int> rotor_types, char reflector_type, vector<int>  rotor_start_positions, vector<int> rotor_ring_settings,vector<string> plugconnecetions);
    char Encrypt(char letter);
    void Rotate();
    void SetUpPlugBoard(vector<string> plugconnecetions);
       
};
#endif