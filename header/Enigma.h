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
    std::string show() const;

 public:
    std::array<Rotor, 3> rotors;
    Reflector reflector;
    PlugBoard plugboard;

    Enigma(const std::array<int, 3>& rotorNumbers, const std::array<int, 3>& rotorStartPositions, const std::array<int, 3>& rotorRingSettings, const std::vector<std::string>& plugConnections, char reflectorType);
    Enigma(std::array<Rotor, 3>& rotors, Reflector& reflector, PlugBoard& plugboard);
    Enigma();
    void Init(const std::array<int, 3>& rotorNumbers, const std::array<int, 3>& rotorStartPositions, const std::array<int, 3>& rotorRingSettings, const std::vector<std::string>& plugConnections, char reflectorType);
    char EncryptChar(char letter);
    std::string Encipher(const std::string& PlainText);
    std::string Decipher(const std::string& CipherText);
    void Rotate();
    void Reset();

    friend std::ostream& operator<<(std::ostream& os, const Enigma& e);
};
#endif
