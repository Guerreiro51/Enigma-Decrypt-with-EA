#include "Enigma.h"

using namespace std;
#include <iostream>




int main()
{
    string user_entry;
    Enigma* enigma;

    vector<int> rotor_types;
    char reflector_type;
    vector<int> rotor_start_positions;
    vector<int> rotor_ring_settings;
    vector<string> plugconnecetions;


    cout << "Digite V para personalizar enigma ou F para configuracao defaut" << endl;
    getline(cin,user_entry);
    if(user_entry == "V")
    {
        cout << "oi";
    }
    else
    {
        rotor_types = {1,2,3};
        reflector_type = 'B';
        rotor_start_positions = {0,0,25};
        rotor_ring_settings = {0,0,0};
        //plugconnecetions = {"AF","TV","KO","BL","RW"};
        
    }

    enigma = new Enigma(rotor_types,reflector_type,rotor_start_positions,rotor_ring_settings,plugconnecetions);

    string input = "RJKNGTERBUM";
    string output = "";

    int i;
    for(i=0;i<input.size();i++)
    {
        output += enigma->Encrypt(input[i]);
    }

    cout << output << endl;
    return 0;
}