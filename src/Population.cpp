#include "Population.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "Plugboard.h"

static std::random_device rd;
static std::mt19937 mt(rd());

Population::Population(const std::string& cipher) : citizens(POP_SIZE, Citizen(cipher)), cipher(cipher), genNumber(0), state(0) {
    Init();
}

void Population::Init() {
    for (Citizen& citizen : citizens) {
        citizen.Init(cipher);
    }
}

void Population::ShowPop() const {
    std::cout << "Generation: " << genNumber << " (Estado atual: " << state << ")\n";
    for (size_t i = 0; i < std::min(5UL, POP_SIZE); i++)
        std::cout << '\t' << "Fitness: " << citizens[i].Fitness() << '\n';
    std::cout << '\n';
}

void Population::Evaluate() {
    for (Citizen& citizen : citizens) {
        citizen.Evaluate(cipher);
    }
    sort(citizens.begin(), citizens.end());

    static double prevMaxFit = citizens[0].Fitness();
    static size_t stagnantCount = 0;
    if (std::abs(prevMaxFit - citizens[0].Fitness()) < 1e-5) {
        stagnantCount++;
        if (stagnantCount == STATE_SIZE[state]) {
            state = (state + 1) % NUMBER_OF_STATES;
            stagnantCount = 0UL;
        }
    } else
        stagnantCount = 0UL;

    prevMaxFit = citizens[0].Fitness();
}

// fit crossover with everyone followed by a mutation
void Population::Elitism() {
    for (size_t i = 1; i < citizens.size(); i++)
        citizens[i].Crossover(citizens[0].Gene());
}

void Population::TournamentSelection(size_t tournamentSize) {
    std::vector<Citizen> pastGenPop = citizens;
    tournamentSize = std::min(tournamentSize, POP_SIZE);

    for (size_t i = 1; i < POP_SIZE; i++) {
        std::shuffle(pastGenPop.begin(), pastGenPop.end(), mt);
        auto firstTourneyWinner = std::min_element(pastGenPop.begin(), pastGenPop.begin() + tournamentSize)->Gene();

        std::shuffle(pastGenPop.begin(), pastGenPop.end(), mt);
        auto secondTourneyWinner = std::min_element(pastGenPop.begin(), pastGenPop.begin() + tournamentSize)->Gene();

        citizens[i].Gene() = Citizen::Crossover(firstTourneyWinner, secondTourneyWinner);
    }
}

void Population::Mutate() {
    for (size_t i = 1; i < citizens.size(); i++)
        citizens[i].Mutate(state);
}

void Population::NextGeneration() {
    genNumber++;
    // Elitism();
    TournamentSelection(TOURNAMENT_SIZE);
    Mutate();
    Evaluate();

    if (!(genNumber % 100))
        ShowPop();
}

const std::vector<Citizen>& Population::Citizens() const { return citizens; }
const std::string& Population::Cipher() const { return cipher; }
const size_t& Population::GenNumber() const { return genNumber; }
std::vector<Citizen>& Population::Citizens() { return citizens; }
