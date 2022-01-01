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
    : rotorNumber(rotorNumber), ringSetting(ringSetting), currentPos(startingPos), startingPos(startingPos) {
    SetupConnections(ROTOR_WIRINGS[rotorNumber]);
    notch = ROTOR_NOTCHES[rotorNumber];
}

int Rotor::Forward(int input) {
    int shift = currentPos - ringSetting;

    return (connections[(input + shift + NUMBER_OF_LETTERS) % NUMBER_OF_LETTERS] - shift + NUMBER_OF_LETTERS) % NUMBER_OF_LETTERS;
}

int Rotor::Backward(int input) {
    int shift = currentPos - ringSetting;

    return (reverseConnections[(input + shift + NUMBER_OF_LETTERS) % NUMBER_OF_LETTERS] - shift + NUMBER_OF_LETTERS) % NUMBER_OF_LETTERS;
}

bool Rotor::IsAtNotch() {
    if (rotorNumber >= 5)
        return currentPos == 25 || currentPos == 12;
    return currentPos == notch;
}

void Rotor::Rotate() {
    currentPos = (currentPos + 1) % NUMBER_OF_LETTERS;
}

void Rotor::SetupConnections(const std::string& arrangement) {
    for (size_t i = 0; i < NUMBER_OF_LETTERS; i++) {
        connections[i] = arrangement[i] - 'A';
        reverseConnections[connections[i]] = i;
    }
}

void Rotor::Reset() {
    currentPos = startingPos;
}

void Rotor::ChangeRotor(int newRotorNumber) {
    rotorNumber = newRotorNumber;
    SetupConnections(ROTOR_WIRINGS[newRotorNumber]);
    notch = ROTOR_NOTCHES[newRotorNumber];
}

void Rotor::ChangeStartingPos(int newStartingPos) {
    startingPos = newStartingPos;
    Reset();
}

void Rotor::ChangeRingSetting(int newRingSetting) {
    ringSetting = newRingSetting;
}

const int& Rotor::RotorNumber() const { return rotorNumber; }
const int& Rotor::StartingPos() const { return startingPos; }
const int& Rotor::RingSetting() const { return ringSetting; }