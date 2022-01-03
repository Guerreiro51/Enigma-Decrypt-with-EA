#ifndef POPULATION_H
#define POPULATION_H

#include <future>
#include <random>

#include "Citizen.h"

class Population {
 private:
    // This vector must be ordered by fitness
    std::vector<Citizen> citizens;

    const std::string cipher;

    size_t genNumber;
    std::vector<float> maxFit;
    std::vector<float> avgFit;

    int curState;
    std::vector<int> state;

 public:
    explicit Population(const std::string& cipher);
    void Init();

    void Evaluate();
    void Mutate();
    void Elitism();
    void TournamentSelection();
    void NextGeneration();

    void RandomPredation();
    void Genocide();

    void ShowPop() const;
    void OutputData(std::ofstream& maxFit, std::ofstream& avgFit, std::ofstream& mutState) const;
    void DumpData(std::ofstream& maxFit, std::ofstream& avgFit, std::ofstream& mutState) const;
    void PlotDataMatplotlib() const;
    void PlotDataGnuplot() const;

    const std::vector<Citizen>& Citizens() const;
    const std::string& Cipher() const;
    const size_t& GenNumber() const;
    std::vector<Citizen>& Citizens();
};

#endif