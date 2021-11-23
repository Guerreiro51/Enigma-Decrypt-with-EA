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

    rotor_types = {2,5,3};
    reflector_type = 'B';
    rotor_start_positions = {7,4,19};
    rotor_ring_settings = {12,2,20};
    plugconnecetions = {"AF","TV","KO","BL","RW"};

    enigma = new Enigma(rotor_types,reflector_type,rotor_start_positions,rotor_ring_settings,plugconnecetions);

    string input = "OZLUDYAKMGMXVFVARPMJIKVWPMBVWMOIDHYPLAYUWGBZFAFAFUQFZQISLEZMYPVBRDDLAGIHIFUJDFADORQOOMIZPYXDCBPWDSSNUSYZTJEWZPWFBWBMIEQXRFASZLOPPZRJKJSPPSTXKPUWYSKNMZZLHJDXJMMMDFODIHUBVCXMNICNYQBNQODFQLOGPZYXRJMTLMRKQAUQJPADHDZPFIKTQBFXAYMVSZPKXIQLOQCVRPKOBZSXIUBAAJBRSNAFDMLLBVSYXISFXQZKQJRIQHOSHVYJXIFUZRMXWJVWHCCYHCXYGRKMKBPWRDBXXRGABQBZRJDVHFPJZUSEBHWAEOGEUQFZEEBDCWNDHIAQDMHKPRVYHQGRDYQIOEOLUBGBSNXWPZCHLDZQBWBEWOCQDBAFGUVHNGCIKXEIZGIZHPJFCTMNNNAUXEVWTWACHOLOLSLTMDRZJZEVKKSSGUUTHVXXODSKTFGRUEIIXVWQYUIPIDBFPGLBYXZTCOQBCAHJYNSGDYLREYBRAKXGKQKWJEKWGAPTHGOMXJDSQKYHMFGOLXBSKVLGNZOAXGVTGXUIVFTGKPJU";
    string output = "";

    output = enigma->Encrypt(input);

    cout << output <<  endl;

    return 0;
}