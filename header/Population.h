#ifndef POPULATION_H
#define POPULATION_H
#pragma once

#include <random>

#include "Enigma.h"

#define ENGLISH_IOC 1.73
#define PORTUGUESE_IOC 1.94

#define MUTATION_RATE 0.02

#define CROSSOVER_ROTOR_CHANCE 0.05
#define CROSSOVER_REFLECTOR_CHANCE 0.0
#define CROSSOVER_PLUGBOARD_CHANCE 0.0

#define MUTATE_ROTOR_CHANCE 0.08
#define MUTATE_ROTOR_STARTINGPOS_CHANCE 0.1
#define MUTATE_ROTOR_RINGSETTING_CHANCE 0.1
#define MUTATE_REFLECTOR_CHANCE 0.0
#define MUTATE_PLUGBOARD_CHANCE 0.0

#define POP_SIZE 25

struct Citizen {
    Enigma gene;
    float fitness;

    Citizen(const std::string& cipher, const std::array<int, 3>& rotorNumbers, const std::array<int, 3>& rotorStartPositions, const std::array<int, 3>& rotorRingSettings, const std::vector<std::string>& plugConnections, char reflectorType);
    Citizen(const std::string& cipher);

    friend bool operator<(const Citizen& a, const Citizen& b) {
        return a.fitness < b.fitness;
    }
    friend bool operator>(const Citizen& a, const Citizen& b) {
        return a.fitness > b.fitness;
    }
};

class Population {
    // The citizen with best fitness will always be the first one in the array
 public:
    std::vector<Citizen> citizens;

    const std::string cipher;

    size_t genNumber;
    float mutationRate;

    std::random_device rd;
    std::mt19937 mt;

 public:
    Population(const std::string& cipher);
    void Init();
    void Evaluate();
    void Elitism();
    void NextGeneration();
    void SortPop();
    static float fitnessFunction(std::string&);
    Enigma Crossover(const Enigma& e1, const Enigma& e2);
    void Mutate();
    void nextGeneration();

    void ShowPop();
};

#endif