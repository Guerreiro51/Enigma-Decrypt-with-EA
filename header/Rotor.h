#ifndef ROTOR_H
#define ROTOR_H
#pragma once

#include <array>
#include <string>
#include <unordered_map>

class Rotor {
 public:
    int rotorNumber;
    int notch;
    int ringSetting;
    int currentPos;
    int startingPos;
    std::array<int, 26> connections;
    std::array<int, 26> reverseConnections;

    static const std::array<std::string, 9> ROTOR_WIRINGS;
    static const std::array<char, 9> ROTOR_NOTCHES;

 public:
    Rotor(int rotorNumber, int startingPos, int ringSetting);
    Rotor() = default;

    void SetupConnections(const std::string& arrangement);

    int Forward(int input);
    int Backward(int input);
    void Rotate();
    bool IsAtNotch();

    void Reset();
    void ChangeRotor(int rotorNumber);

    friend class Enigma;
};
#endif
