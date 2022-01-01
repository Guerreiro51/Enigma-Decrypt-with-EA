#ifndef ROTOR_H
#define ROTOR_H

#include <array>
#include <string>
#include <unordered_map>

class Rotor {
 private:
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
    void ChangeRotor(int newRotorNumber);
    void ChangeStartingPos(int newStartingPos);
    void ChangeRingSetting(int newRingSetting);

    const int& RotorNumber() const;
    const int& StartingPos() const;
    const int& RingSetting() const;
};
#endif
