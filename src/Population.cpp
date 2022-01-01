#include "Population.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "Plugboard.h"

static std::random_device rd;
static std::mt19937 mt(rd());

Population::Population(const std::string& cipher) : citizens(POP_SIZE, Citizen(cipher)), cipher(cipher), genNumber(0), maxFit(NUMBER_OF_ITERATIONS), avgFit(NUMBER_OF_ITERATIONS), curState(0), state(NUMBER_OF_ITERATIONS) {}

void Population::Init() {
    for (Citizen& citizen : citizens) {
        citizen.Init(cipher);
    }
}

void Population::Evaluate() {
    for (Citizen& citizen : citizens) {
        citizen.Evaluate(cipher);
    }
    sort(citizens.begin(), citizens.end());
    maxFit[genNumber - 1] = citizens[0].Fitness();
    avgFit[genNumber - 1] = std::accumulate(citizens.begin(), citizens.end(), 0.0, [](double a, const Citizen& c) { return a + c.Fitness(); }) / (double)POP_SIZE;
    state[genNumber - 1] = curState;

    static double prevMaxFit = citizens[0].Fitness();
    static size_t stagnantCount = 0;
    if (std::abs(prevMaxFit - citizens[0].Fitness()) < 1e-5) {
        stagnantCount++;
        if (stagnantCount == STATE_SIZE[curState]) {
            curState = (curState + 1) % NUMBER_OF_STATES;
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
        citizens[i].Mutate(curState);
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

void Population::ShowPop() const {
    std::cout << "Generation: " << genNumber << " (Estado atual: " << curState + 1 << ")\n";
    for (size_t i = 0; i < std::min(5UL, POP_SIZE); i++)
        std::cout << '\t' << "Fitness: " << citizens[i].Fitness() << '\n';
    std::cout << '\n';
}

void Population::OutputData(std::ofstream& maxFit, std::ofstream& avgFit, std::ofstream& mutState) const {
    for (size_t gen = 1; gen <= NUMBER_OF_ITERATIONS; gen++) {
        maxFit << gen << ' ' << this->maxFit[gen - 1] << '\n';
        avgFit << gen << ' ' << this->avgFit[gen - 1] << '\n';
        mutState << gen << ' ' << this->state[gen - 1] + 1 << '\n';
    }
}

void Population::PlotData(std::ofstream& maxFit, std::ofstream& avgFit, std::ofstream& mutState) const {
    maxFit.flush();
    avgFit.flush();
    mutState.flush();

    FILE* gnuplot = popen("gnuplot", "w");
    fprintf(gnuplot, "set term pngcairo\nset output '../plots/fitness.png'\n");
    fprintf(gnuplot, "set title 'Fitness plot'\nset key outside\nset xlabel 'Generation'\nset ylabel 'Fitness'\n");
    fprintf(gnuplot, "plot '../data/maxFit.txt' title 'MaxFit' with lines, '../data/avgFit.txt' title 'AvgFit' with lines");
    fclose(gnuplot);

    FILE* gnuplot2 = popen("gnuplot", "w");
    fprintf(gnuplot2, "set term pngcairo\nset output '../plots/mutState.png'\n");
    fprintf(gnuplot2, "set title 'Mutation State'\nset key left top\nset xlabel 'Generation'\nset ylabel 'Mutation State'\n");
    fprintf(gnuplot2, "plot '../data/mutState.txt' title 'Mutation State' with lines");
    fclose(gnuplot2);
}

const std::vector<Citizen>& Population::Citizens() const { return citizens; }
const std::string& Population::Cipher() const { return cipher; }
const size_t& Population::GenNumber() const { return genNumber; }
std::vector<Citizen>& Population::Citizens() { return citizens; }
