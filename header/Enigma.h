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
    std::array<Rotor, NUMBER_OF_ROTORS_INSTALLED> rotors;
    Reflector reflector;
    Plugboard plugboard;

 private:
    std::string show() const;

 public:
    Enigma(const std::array<int, NUMBER_OF_ROTORS_INSTALLED>& rotorNumbers, const std::array<int, NUMBER_OF_ROTORS_INSTALLED>& rotorStartingPos, const std::array<int, NUMBER_OF_ROTORS_INSTALLED>& rotorRingSettings, const std::vector<std::string>& plugConnections, char reflectorType);
    Enigma(const std::array<Rotor, NUMBER_OF_ROTORS_INSTALLED>& rotors, const Reflector& reflector, const Plugboard& plugboard);
    Enigma();

    void Init(const std::array<int, NUMBER_OF_ROTORS_INSTALLED>& rotorNumbers, const std::array<int, NUMBER_OF_ROTORS_INSTALLED>& rotorStartingPos, const std::array<int, NUMBER_OF_ROTORS_INSTALLED>& rotorRingSettings, const std::vector<std::string>& plugConnections, char reflectorType);
    void Init(const std::array<Rotor, NUMBER_OF_ROTORS_INSTALLED>& rotors, const Reflector& reflector, const Plugboard& plugboard);
    void Init();

    char EncryptChar(char letter);
    std::string Encipher(const std::string& PlainText);
    std::string Decipher(const std::string& CipherText);
    void Rotate();
    void Reset();

    const std::array<Rotor, NUMBER_OF_ROTORS_INSTALLED>& Rotors() const;
    const Reflector& getReflector() const;
    const Plugboard& getPlugboard() const;

    std::array<Rotor, NUMBER_OF_ROTORS_INSTALLED>& Rotors();
    Reflector& getReflector();
    Plugboard& getPlugboard();

    friend std::ostream& operator<<(std::ostream& os, const Enigma& e);
};
#endif
