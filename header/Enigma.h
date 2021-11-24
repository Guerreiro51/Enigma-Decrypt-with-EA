#ifndef ENIGMA_H
#define ENIGMA_H
#pragma once

#include <array>
#include <string>
#include <vector>

#include "PlugBoard.h"
#include "Reflector.h"
#include "Rotor.h"

class Enigma {
 private:
    std::array<Rotor, 3> rotors;
    PlugBoard plugboard;
    Reflector reflector;

    std::string show() const;

 public:
    Enigma(const std::array<int, 3>& rotorNumbers, const std::array<int, 3>& rotorStartPositions, const std::array<int, 3>& rotorRingSettings, const std::vector<std::string>& plugConnections, char reflectorType);
    void init(const std::array<int, 3>& rotorNumbers, const std::array<int, 3>& rotorStartPositions, const std::array<int, 3>& rotorRingSettings, const std::vector<std::string>& plugConnections, char reflectorType);
    char EncryptChar(char letter);
    std::string Encipher(const std::string& PlainText);
    std::string Decipher(const std::string& CipherText);
    void Rotate();

    friend std::ostream& operator<<(std::ostream& os, const Enigma& e);
};
#endif
