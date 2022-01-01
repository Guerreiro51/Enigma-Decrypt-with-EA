#ifndef ENIGMA_H
#define ENIGMA_H

#include <array>
#include <string>
#include <vector>

#include "Plugboard.h"
#include "Reflector.h"
#include "Rotor.h"

class Enigma {
 private:
    std::array<Rotor, 3> rotors;
    Reflector reflector;
    Plugboard plugboard;

 private:
    std::string show() const;

 public:
    Enigma(const std::array<int, 3>& rotorNumbers, const std::array<int, 3>& rotorStartPositions, const std::array<int, 3>& rotorRingSettings, const std::vector<std::string>& plugConnections, char reflectorType);
    Enigma(const std::array<Rotor, 3>& rotors, const Reflector& reflector, const Plugboard& plugboard);
    Enigma();

    void Init(const std::array<int, 3>& rotorNumbers, const std::array<int, 3>& rotorStartPositions, const std::array<int, 3>& rotorRingSettings, const std::vector<std::string>& plugConnections, char reflectorType);
    void Init(const std::array<Rotor, 3>& rotors, const Reflector& reflector, const Plugboard& plugboard);
    void Init();

    char EncryptChar(char letter);
    std::string Encipher(const std::string& PlainText);
    std::string Decipher(const std::string& CipherText);
    void Rotate();
    void Reset();

    const std::array<Rotor, 3>& Rotors() const;
    const Reflector& getReflector() const;
    const Plugboard& getPlugboard() const;

    std::array<Rotor, 3>& Rotors();
    Reflector& getReflector();
    Plugboard& getPlugboard();

    friend std::ostream& operator<<(std::ostream& os, const Enigma& e);
};
#endif
