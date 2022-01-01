#include "Population.h"

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "Plugboard.h"

Population::Population(const std::string& cipher) : citizens(POP_SIZE, Citizen(cipher)), cipher(cipher), genNumber(0) {
    Init();
}

void Population::Init() {
    for (Citizen& citizen : citizens) {
        citizen.Init(cipher);
    }
}

void Population::ShowPop() const {
    std::cout << "Generation: " << genNumber << '\n';
    for (size_t i = 0; i < std::min(5UL, POP_SIZE); i++)
        std::cout << '\t' << "Fitness: " << citizens[i].Fitness() << '\n';
    std::cout << '\n';
}

void Population::Evaluate() {
    for (Citizen& citizen : citizens) {
        citizen.Evaluate(cipher);
    }
    sort(citizens.begin(), citizens.end());
}

// fit crossover with everyone followed by a mutation
void Population::Elitism() {
    for (size_t i = 1; i < citizens.size(); i++)
        citizens[i].Crossover(citizens[0].Gene());
}

void Population::Mutate() {
    for (size_t i = 1; i < citizens.size(); i++)
        citizens[i].Mutate();
}

void Population::NextGeneration() {
    genNumber++;
    Elitism();
    Mutate();
    Evaluate();

    if (!(genNumber % 100))
        ShowPop();
}

const std::vector<Citizen>& Population::Citizens() const { return citizens; }
const std::string& Population::Cipher() const { return cipher; }
const size_t& Population::GenNumber() const { return genNumber; }
std::vector<Citizen>& Population::Citizens() { return citizens; }
