#include "Reflector.h"

const std::array<std::string, 4> Reflector::REFLECTOR_WIRINGS = {"EJMZALYXVBWFCRQUONTSPIKHGD",
                                                                 "YRUHQSLDPXNGOKMIEBFZCWVJAT",
                                                                 "FVPJIAOYEDRZXWGCTKUQSBNMHL",
                                                                 "ZYXWVUTSRQPONMLKJIHGFEDCBA"};
Reflector::Reflector(char type) {
    type = toupper(type) - 'A';
    if (type < 0 || type > 3) type = 3;
    connections = REFLECTOR_WIRINGS[type];
}

int Reflector::ReturnLetter(int input) {
    return connections[input] - 'A';
}

void Reflector::setReflector(char type) {
    type = toupper(type) - 'A';
    if (type < 0 || type > 3) type = 3;
    connections = REFLECTOR_WIRINGS[type];
}
