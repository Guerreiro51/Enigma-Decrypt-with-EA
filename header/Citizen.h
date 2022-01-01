#ifndef CITIZEN_H
#define CITIZEN_H

#include <random>

#include "Enigma.h"

// Index of Coincidence for some languages
constexpr double ENGLISH_IOC = 1.73;
constexpr double PORTUGUESE_IOC = 1.94;

constexpr double MUTATION_RATE = 1.0;  // a multiplier of differents mutation rates

constexpr double CROSSOVER_ROTOR_CHANCE = 0.0;      // chance of inheriting some of the other's rotors
constexpr double CROSSOVER_REFLECTOR_CHANCE = 0.5;  // chance of inheriting the other's reflector

constexpr double MUTATE_ROTOR_CHANCE = 0.4;              // chance of randomly swapping a rotor
constexpr double MUTATE_ROTOR_STARTINGPOS_CHANCE = 0.1;  // change of randomly swapping the starting position
constexpr double MUTATE_ROTOR_RINGSETTING_CHANCE = 0.1;  // chance of randomly swapping the ring setting
constexpr double MUTATE_REFLECTOR_CHANCE = 0.25;         // chance of randomly swapping the reflector

class Citizen {
 private:
    Enigma gene;
    double fitness;

 public:
    Citizen(const std::string& cipher, const std::array<int, 3>& rotorNumbers, const std::array<int, 3>& rotorStartPositions, const std::array<int, 3>& rotorRingSettings, const std::vector<std::string>& plugConnections, char reflectorType);
    explicit Citizen(const std::string& cipher);
    void Init(const std::string& cipher);

    static double indexOfCoincidence(const std::string&);

    void Evaluate(const std::string&);
    void Crossover(const Enigma& other);
    void Mutate();

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
