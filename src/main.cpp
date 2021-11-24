#include <iostream>
#include <random>

#include "Enigma.h"

int main() {
    // Generate a random initial condition
    std::random_device rd;
    std::mt19937 mt(rd());

    auto rng = std::uniform_int_distribution<int>(0, 8);
    std::array<int, 3> rotorNumbers = {rng(mt), rng(mt), rng(mt)};
    rng = std::uniform_int_distribution<int>(0, 25);
    std::array<int, 3> rotorStartingPositions = {rng(mt), rng(mt), rng(mt)};
    std::array<int, 3> rotor_ring_settings = {rng(mt), rng(mt), rng(mt)};
    std::vector<std::string> plugConnections = {"AF", "TV", "KO", "BL", "RW"};
    rng = std::uniform_int_distribution<int>(0, 2);
    char reflector_type = rng(mt) + 'A';

    Enigma enigma(rotorNumbers, rotorStartingPositions, rotor_ring_settings, plugConnections, reflector_type);
    std::cout << enigma << '\n';

    std::string input = "I propose to consider the question, ‘Can machines think?’ This should begin with definitions of the meaning of the terms ‘machine’ and ‘think’. The definitions might be framed so as to reflect so far as possible the normal use of the words, but this attitude is dangerous. If the meaning of the words ‘machine’ and ‘think’ are to be found by examining how they are commonly used it is difficult to escape the conclusion that the meaning and the answer to the question, ‘Can machines think?’ is to be sought in a statistical survey such as a Gallup poll. But this is absurd. Instead of attempting such a definition I shall replace the question by another, which is closely related to it and is expressed in relatively unambiguous words.";
    std::string output = enigma.Encipher(input);
    std::cout << "Cipher: " << output << "\n\n";

    input = output;
    enigma.init(rotorNumbers, rotorStartingPositions, rotor_ring_settings, plugConnections, reflector_type);  // Reset to initial state
    output = enigma.Decipher(input);
    std::cout << output << '\n';
}
