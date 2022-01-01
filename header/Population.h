#ifndef POPULATION_H
#define POPULATION_H

#include <random>

#include "Citizen.h"

constexpr size_t POP_SIZE = 25;

class Population {
 private:
    // This vector must be ordered by fitness
    std::vector<Citizen> citizens;

    const std::string cipher;
    size_t genNumber;

 public:
    explicit Population(const std::string& cipher);
    void Init();

    void Evaluate();
    void Mutate();
    void Elitism();
    void NextGeneration();

    void ShowPop() const;

    const std::vector<Citizen>& Citizens() const;
    const std::string& Cipher() const;
    const size_t& GenNumber() const;
    std::vector<Citizen>& Citizens();
};

#endif