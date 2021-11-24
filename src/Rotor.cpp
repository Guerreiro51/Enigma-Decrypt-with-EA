#include "Rotor.h"

const std::array<std::string, 9> Rotor::ROTOR_WIRINGS = {"EKMFLGDQVZNTOWYHXUSPAIBRCJ",
                                                         "AJDKSIRUXBLHWTMCQGZNPYFVOE",
                                                         "BDFHJLCPRTXVZNYEIWGAKMUSQO",
                                                         "ESOVPZJAYQUIRHXLNFTGKDCMWB",
                                                         "VZBRGITYUPSDNHLXAWMJQOFECK",
                                                         "JPGVOUMFYQBENHZRDKASXLICTW",
                                                         "NZJHGRCXMYSWBOUFAIVLPEKQDT",
                                                         "FKQHTLXOCBJSPDZRAMEWNIUYGV",
                                                         "ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

const std::array<char, 9> Rotor::ROTOR_NOTCHES = {'Q' - 'A',
                                                  'E' - 'A',
                                                  'V' - 'A',
                                                  'J' - 'A',
                                                  'Z' - 'A',
                                                  0, 0, 0, 0};

Rotor::Rotor(int rotorNumber, int startingPos, int ringSetting)
    : rotorNumber(rotorNumber), currentPos(startingPos), ringSetting(ringSetting) {
    SetupConnections(ROTOR_WIRINGS[rotorNumber - 1]);
    notch = ROTOR_NOTCHES[rotorNumber - 1];
}

int Rotor::Forward(int input) {
    int shift = currentPos - ringSetting;

    return (connections[(input + shift + 26) % 26] - shift + 26) % 26;
}

int Rotor::Backward(int input) {
    int shift = currentPos - ringSetting;

    return (reverseConnections[(input + shift + 26) % 26] - shift + 26) % 26;
}

bool Rotor::IsAtNotch() {
    if (rotorNumber > 5)
        return currentPos == 25 || currentPos == 12;
    return currentPos == notch;
}

void Rotor::Rotate() {
    currentPos = (currentPos + 1) % 26;
}

void Rotor::SetupConnections(const std::string& arrangement) {
    for (size_t i = 0; i < 26; i++) {
        connections[i] = arrangement[i] - 'A';
        reverseConnections[connections[i]] = i;
    }
}
