#ifndef CITIZEN_H
#define CITIZEN_H

#include <random>

#include "Enigma.h"

class Citizen {
 private:
    Enigma gene;
    double fitness;

 public:
    Citizen(const std::string& cipher, const std::array<int, NUMBER_OF_ROTORS_INSTALLED>& rotorNumbers, const std::array<int, NUMBER_OF_ROTORS_INSTALLED>& rotorStartingPos, const std::array<int, NUMBER_OF_ROTORS_INSTALLED>& rotorRingSettings, const std::vector<std::string>& plugConnections, char reflectorType);
    explicit Citizen(const std::string& cipher);
    void Init(const std::string& cipher);

    static double indexOfCoincidence(const std::string&);

    void Evaluate(const std::string&);
    void Crossover(const Enigma& other);
    void Mutate(int state);

    const double& Fitness() const;
    const Enigma& Gene() const;
    Enigma& Gene();

    friend bool operator<(const Citizen& a, const Citizen& b) {
        return a.fitness < b.fitness;
    }
    friend bool operator>(const Citizen& a, const Citizen& b) {
        return a.fitness > b.fitness;
    }
};

#endif
