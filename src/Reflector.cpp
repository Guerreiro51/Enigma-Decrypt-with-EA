#include "Reflector.h"

const std::array<std::string, NUMBER_OF_REFLECTOR_TYPES + 1> Reflector::REFLECTOR_WIRINGS = {"EJMZALYXVBWFCRQUONTSPIKHGD",
                                                                                             "YRUHQSLDPXNGOKMIEBFZCWVJAT",
                                                                                             "FVPJIAOYEDRZXWGCTKUQSBNMHL",
                                                                                             "ZYXWVUTSRQPONMLKJIHGFEDCBA"};
Reflector::Reflector(char type) {
    type = toupper(type) - 'A';
    if (type < 0 || type > NUMBER_OF_REFLECTOR_TYPES) type = NUMBER_OF_REFLECTOR_TYPES;
    connections = REFLECTOR_WIRINGS[type];
}

int Reflector::ReturnLetter(int input) {
    return connections[input] - 'A';
}

void Reflector::setReflector(char type) {
    type = toupper(type) - 'A';
    if (type < 0 || type > (char)NUMBER_OF_REFLECTOR_TYPES) type = (char)NUMBER_OF_REFLECTOR_TYPES;
    connections = REFLECTOR_WIRINGS[type];
}

const std::string& Reflector::Connections() const { return connections; }
