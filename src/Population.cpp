#include "Population.h"

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "PlugBoard.h"

Population::Population(const std::string& cipher) : cipher(cipher), mt(rd()) {
    Init();
}

Citizen::Citizen(const std::string& cipher, const std::array<int, 3>& rotorNumbers, const std::array<int, 3>& rotorStartPositions, const std::array<int, 3>& rotorRingSettings, const std::vector<std::string>& plugConnections, char reflectorType)
    : gene(rotorNumbers, rotorStartPositions, rotorRingSettings, plugConnections, reflectorType) {
    std::string plaintext = gene.Decipher(cipher);
    gene.Reset();
    fitness = Population::fitnessFunction(plaintext);
}

Citizen::Citizen(const std::string& cipher) : gene() {
    std::string plaintext = gene.Decipher(cipher);
    gene.Reset();
    fitness = Population::fitnessFunction(plaintext);
}

float Population::fitnessFunction(std::string& text) {
    std::array<size_t, 26> letters{};
    size_t i = 0;
    for (const char& letter : text) {
        if (isalpha(letter))
            letters[toupper(letter) - 'A']++;
    }

    float indexOfCoincidence = 0.0f;
    for (size_t freq : letters) {
        indexOfCoincidence += freq * (freq - 1.0f);
    }
    size_t textSize = std::accumulate(letters.begin(), letters.end(), 0);
    indexOfCoincidence = 26.0f * indexOfCoincidence / float(textSize * (textSize - 1.0f));

    return fabs(indexOfCoincidence - ENGLISH_IOC);
}

void Population::Init() {
    for (size_t i = 0; i < POP_SIZE; i++) {
        /*
        // Chooses random rotors
        std::array<int, 8> random1to8;
        std::iota(random1to8.begin(), random1to8.end(), 0);
        std::random_shuffle(random1to8.begin(), random1to8.end());
        std::array<int, 3> rotorNumbers = {random1to8[0], random1to8[1], random1to8[2]};

        // Chooses random starting position and ring settings
        auto rng = std::uniform_int_distribution<int>(0, 25);
        std::array<int, 3> rotorStartPositions = {rng(mt), rng(mt), rng(mt)};
        std::array<int, 3> rotorRingSettings = {rng(mt), rng(mt), rng(mt)};

        // Generates random plugConnections
        rng = std::uniform_int_distribution<int>(0, 10);  // uniform int distribution to generate the number of connections
        std::vector<std::string> plugConnections(1);
        std::array<char, 26> randomConnections;
        std::iota(randomConnections.begin(), randomConnections.end(), 'A');
        std::random_shuffle(randomConnections.begin(), randomConnections.end());
        for (size_t i = 0; i < plugConnections.size(); i++)
            plugConnections[i] = std::string() + randomConnections[2 * i] + randomConnections[2 * i + 1];

        // Generates random reflector type
        rng = std::uniform_int_distribution<int>(0, 2);
        char reflectorType = rng(mt) + 'A';


        citizens.emplace_back(cipher, rotorNumbers, rotorStartPositions, rotorRingSettings, plugConnections, reflectorType);
        */
        // std::cout << enigma << '\n';
        citizens.emplace_back(cipher);
    }
}

void Population::SortPop() {
    sort(citizens.begin(), citizens.end());
}
void Population::ShowPop() {
    std::cout << "Generation: " << genNumber << '\n';
    for (const auto& citizen : citizens)
        std::cout << '\t' << "Fitness: " << citizen.fitness << '\n';
    std::cout << '\n';
}

void Population::Evaluate() {
    for (Citizen& citizen : citizens) {
        std::string plaintext = citizen.gene.Decipher(cipher);
        citizen.gene.Reset();
        citizen.fitness = fitnessFunction(plaintext);
    }
    SortPop();
}

// fit crossover with everyone followed by a mutation
void Population::Elitism() {
    static unsigned stagnantCount = 0;                  // number of times the maxFit guy has been the same
    static float previousMaxFit = citizens[0].fitness;  // previous maxFit guy
                                                        // static std::uniform_real_distribution<float> dist(-1.0f, 1.0f);  // rng

    // mutating the mutation_rate
    if (abs(citizens[0].fitness - previousMaxFit) <= 1e-3) {
        stagnantCount++;
        if (stagnantCount == 10) {
            stagnantCount = 0;
            mutationRate *= 2.0f;
        }
    } else {
        stagnantCount = 0;
        mutationRate = MUTATION_RATE;
    }
    previousMaxFit = citizens[0].fitness;

    for (size_t i = 1; i < citizens.size(); i++) {
        // Crossover
        citizens[i].gene = Crossover(citizens[0].gene, citizens[i].gene);
    }
}

Enigma Population::Crossover(const Enigma& e1, const Enigma& e2) {
    std::array<Rotor, 3> rotors;
    std::vector<std::string> vazio;
    PlugBoard plugboard(vazio);

    // Reflector crossover
    auto rngBernoulli = std::bernoulli_distribution(CROSSOVER_REFLECTOR_CHANCE);
    Reflector reflector = (rngBernoulli(mt)) ? e1.reflector : e2.reflector;

    // Rotor crossover
    for (size_t i = 0; i < e2.rotors.size(); i++)
        rotors[i] = e2.rotors[i];

    rngBernoulli = std::bernoulli_distribution(CROSSOVER_ROTOR_CHANCE);
    if (rngBernoulli(mt)) {
        auto rngInt = std::uniform_int_distribution<int>(0, 2);
        int chosen = rngInt(mt);
        bool able = true;

        for (Rotor rotor : rotors) {
            if (rotor.rotorNumber == e1.rotors[chosen].rotorNumber)
                able = false;
        }

        if (able)
            rotors[chosen] = e1.rotors[chosen];
    }

    // Rotor starting position and ring settings crossover

    for (size_t i = 0; i < e1.rotors.size(); i++)
        for (size_t j = 0; j < e2.rotors.size(); j++)
            if (e1.rotors[i].rotorNumber == rotors[j].rotorNumber) {
                rotors[j].startingPos = (rotors[j].startingPos + e1.rotors[i].startingPos) / 2;
                rotors[j].ringSetting = (rotors[j].ringSetting + e1.rotors[i].ringSetting) / 2;
            }

    // Plugboard crossover
    std::unordered_map<std::string, int> plugsCount;
    for (auto connection : e1.plugboard.connections) {
        if (connection.first < connection.second) {
            char connectionStr[3];
            connectionStr[0] = connection.first + 'A';
            connectionStr[1] = connection.second + 'A';
            connectionStr[2] = '\0';
            plugsCount[connectionStr]++;
        }
    }

    for (auto connection : e2.plugboard.connections) {
        if (connection.first < connection.second) {
            char connectionStr[3];
            connectionStr[0] = connection.first + 'A';
            connectionStr[1] = connection.second + 'A';
            connectionStr[2] = '\0';
            plugsCount[connectionStr]++;
        }
    }

    std::unordered_set<int> notEquals;
    size_t numberOfConnections = 0;
    for (auto plug : plugsCount) {
        if (plug.second == 2) {
            plugboard.AddConnection(plug.first[0] - 'A', plug.first[1] - 'A');
            numberOfConnections++;
        } else {
            notEquals.insert(plug.first[0]);
            notEquals.insert(plug.first[1]);
        }
    }
    auto notEqualsVector = std::vector<int>(notEquals.begin(), notEquals.end());
    if (notEqualsVector.size() % 2)
        notEqualsVector.erase(notEqualsVector.end() - 1);

    std::random_shuffle(notEqualsVector.begin(), notEqualsVector.end());

    // Changing the quantity of plugs
    rngBernoulli = std::bernoulli_distribution(CROSSOVER_PLUGBOARD_CHANCE);
    int connectionsLimit = 0;
    if (rngBernoulli(mt)) {
        connectionsLimit = (e1.plugboard.connections.size() + e2.plugboard.connections.size()) / 4;
    } else {
        connectionsLimit = e2.plugboard.connections.size() / 2;
    }

    for (size_t i = 0; i < notEqualsVector.size() / 2; i++) {
        plugboard.AddConnection(notEqualsVector[2 * i] - 'A', notEqualsVector[2 * i + 1] - 'A');
        numberOfConnections++;
        if (numberOfConnections >= connectionsLimit)
            break;
    }

    return Enigma(rotors, reflector, plugboard);
}

void Population::Mutate() {
    auto rngChanceRotor = std::bernoulli_distribution(MUTATE_ROTOR_CHANCE);
    auto rngValueRotor = std::uniform_int_distribution(0, 7);
    auto rngChanceRotorStartingPos = std::bernoulli_distribution(MUTATE_ROTOR_STARTINGPOS_CHANCE);
    auto rngValueRotorStartingPos = std::uniform_int_distribution(0, 25);
    auto rngChanceRotorRingSetting = std::bernoulli_distribution(MUTATE_ROTOR_RINGSETTING_CHANCE);
    auto rngValueRotorRingSetting = std::uniform_int_distribution(0, 25);

    auto rngChanceReflector = std::bernoulli_distribution(MUTATE_REFLECTOR_CHANCE);
    auto rngValueReflector = std::uniform_int_distribution(0, 2);

    auto rngChancePlugboard = std::bernoulli_distribution(MUTATE_PLUGBOARD_CHANCE);
    auto rngValuePlugboard = std::uniform_int_distribution(-1, 1);

    int count = 0;
    for (Citizen& citizen : citizens) {
        count++;
        if (count == 1)
            continue;

        if (rngChanceReflector(mt))
            citizen.gene.reflector.setReflector(rngValueReflector(mt) + 'A');

        if (rngChanceRotor(mt)) {
            auto rngInt = std::uniform_int_distribution<int>(0, 2);
            int swappedRotor = rngInt(mt);

            bool able;
            int newRotor;
            do {
                able = false;
                newRotor = rngValueRotor(mt);
                for (Rotor rotor : citizen.gene.rotors) {
                    if (rotor.rotorNumber == newRotor)
                        able = true;
                }
            } while (able);

            citizen.gene.rotors[swappedRotor].ChangeRotor(newRotor);

            if (false) {
                citizen.gene.rotors[swappedRotor].startingPos = rngValueRotorStartingPos(mt);
                citizen.gene.rotors[swappedRotor].Reset();
                citizen.gene.rotors[swappedRotor].ringSetting = rngValueRotorRingSetting(mt);
            }

        } else {
            if (rngChanceRotorStartingPos(mt)) {
                auto rngInt = std::uniform_int_distribution<int>(0, 2);
                int swappedRotor = rngInt(mt);
                citizen.gene.rotors[swappedRotor].startingPos = rngValueRotorStartingPos(mt);
                citizen.gene.rotors[swappedRotor].Reset();
            }
            if (rngChanceRotorRingSetting(mt)) {
                auto rngInt = std::uniform_int_distribution<int>(0, 2);
                int swappedRotor = rngInt(mt);
                citizen.gene.rotors[swappedRotor].ringSetting = rngValueRotorRingSetting(mt);
            }
        }

        if (rngChancePlugboard(mt)) {
            switch (rngValuePlugboard(mt)) {
                case -1: {  // remove 1
                    // auto p = *citizen.gene.plugboard.connections.begin();
                    // citizen.gene.plugboard.connections.erase(p.first);
                    // citizen.gene.plugboard.connections.erase(p.second);
                    break;
                }

                case 0: {  // altera 1
                    break;
                }

                case 1: {  // adiciona 1
                    break;
                }
            }
        }
    }
}

void Population::nextGeneration() {
    genNumber++;
    Elitism();
    Mutate();
    Evaluate();

    if (!(genNumber % 1000))
        ShowPop();
}
