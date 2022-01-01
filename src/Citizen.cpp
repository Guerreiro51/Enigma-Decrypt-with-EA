#include "Citizen.h"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>
#include <unordered_map>

static std::random_device rd;
static std::mt19937 mt(rd());

Citizen::Citizen(const std::string& cipher, const std::array<int, 3>& rotorNumbers, const std::array<int, 3>& rotorStartPositions, const std::array<int, 3>& rotorRingSettings, const std::vector<std::string>& plugConnections, char reflectorType)
    : gene(rotorNumbers, rotorStartPositions, rotorRingSettings, plugConnections, reflectorType) {
    Evaluate(cipher);
}

Citizen::Citizen(const std::string& cipher) : gene() {
    Evaluate(cipher);
}

void Citizen::Init(const std::string& cipher) {
    gene.Init();
    Evaluate(cipher);
}

double Citizen::indexOfCoincidence(const std::string& text) {
    std::array<double, 26> letters{};
    for (const char& letter : text) {
        if (isalpha(letter))
            letters[toupper(letter) - 'A']++;
    }

    double indexOfCoincidence = std::accumulate(letters.begin(), letters.end(), 0, [](double a, const double& f) { return a + f * (f - 1.0); });

    double textSize = std::accumulate(letters.begin(), letters.end(), 0.0);
    indexOfCoincidence = indexOfCoincidence * 26.0 / (textSize * (textSize - 1.0));

    return indexOfCoincidence;
}

void Citizen::Evaluate(const std::string& cipher) {
    std::string plaintext = gene.Decipher(cipher);
    fitness = fabs(indexOfCoincidence(plaintext) - ENGLISH_IOC);
}

void Citizen::Crossover(const Enigma& other) {
    std::array<Rotor, 3> rotors;
    Plugboard plugboard;

    // Reflector crossover (one or the other at random)
    auto rngBernoulli = std::bernoulli_distribution(CROSSOVER_REFLECTOR_CHANCE);
    Reflector reflector = (rngBernoulli(mt)) ? other.getReflector() : gene.getReflector();

    // Starts off equal to the caller
    for (size_t i = 0; i < gene.Rotors().size(); i++)
        rotors[i] = gene.Rotors()[i];

    // Rotor crossover. Checks if it is equal, a permutation or different
    // in the first case it does nothing
    // in the second case it makes them equal
    // in the third case it swaps a random rotor
    rngBernoulli = std::bernoulli_distribution(CROSSOVER_ROTOR_CHANCE);
    if (rngBernoulli(mt)) {
        // Checking if equal
        bool equal = true;
        for (size_t i = 0; i < gene.Rotors().size(); i++) {
            if (gene.Rotors()[i].RotorNumber() != other.Rotors()[i].RotorNumber()) {
                equal = false;
                break;
            }
        }

        if (!equal) {
            bool permutation = true;
            // Checking if they're a permutation
            std::unordered_map<int, int> exists;
            for (const Rotor& r : gene.Rotors())
                exists[r.RotorNumber()]++;
            for (const Rotor& r : other.Rotors()) {
                exists[r.RotorNumber()]--;
                if (exists[r.RotorNumber()])
                    permutation = false;
            }

            if (permutation) {
                for (size_t i = 0; i < rotors.size(); i++)
                    rotors[i].ChangeRotor(other.Rotors()[i].RotorNumber());
            } else {
                // uses the exists map to find elements that can be swapped
                int rotorNumberOut = std::find_if(exists.begin(), exists.end(),
                                                  [](std::pair<int, int>&& p) { return p.second == 1; })
                                         ->first;
                int rotorNumberIn = std::find_if(exists.begin(), exists.end(),
                                                 [](std::pair<int, int>&& p) { return p.second == -1; })
                                        ->first;
                auto swapped = std::find_if(rotors.begin(), rotors.end(),
                                            [&](const Rotor& r) { return r.RotorNumber() == rotorNumberOut; });

                swapped->ChangeRotor(rotorNumberIn);
            }
        }
    }

    // Rotor starting position and ring settings crossover
    for (size_t i = 0; i < rotors.size(); i++) {
        if (rotors[i].RotorNumber() == other.Rotors()[i].RotorNumber()) {
            rotors[i].ChangeStartingPos((rotors[i].StartingPos() + other.Rotors()[i].StartingPos()) / 2);
            rotors[i].ChangeRingSetting((rotors[i].RingSetting() + other.Rotors()[i].RingSetting()) / 2);
        }
    }

    gene.Init(rotors, reflector, plugboard);
}

void Citizen::Mutate() {
    static auto rngChanceRotor = std::bernoulli_distribution(MUTATE_ROTOR_CHANCE);
    static auto rngValueRotor = std::uniform_int_distribution<>(0, 7);
    static auto rngChanceRotorStartingPos = std::bernoulli_distribution(MUTATE_ROTOR_STARTINGPOS_CHANCE);
    static auto rngValueRotorStartingPos = std::uniform_int_distribution<>(0, 25);
    static auto rngChanceRotorRingSetting = std::bernoulli_distribution(MUTATE_ROTOR_RINGSETTING_CHANCE);
    static auto rngValueRotorRingSetting = std::uniform_int_distribution<>(0, 25);

    static auto rngChanceReflector = std::bernoulli_distribution(MUTATE_REFLECTOR_CHANCE);
    static auto rngValueReflector = std::uniform_int_distribution<>(0, 2);

    // Changes the reflector to a random one
    if (rngChanceReflector(mt))
        gene.getReflector().setReflector(rngValueReflector(mt) + 'A');

    // Changes one of the rotors to a random one
    if (rngChanceRotor(mt)) {
        auto rngInt = std::uniform_int_distribution<int>(0, 2);
        int swappedRotor = rngInt(mt);

        bool able;
        int newRotor;
        do {
            newRotor = rngValueRotor(mt);
            able = std::any_of(gene.Rotors().begin(), gene.Rotors().end(), [&](const Rotor& r) { return r.RotorNumber() == newRotor; });
        } while (able);

        gene.Rotors()[swappedRotor].ChangeRotor(newRotor);
        gene.Rotors()[swappedRotor].ChangeStartingPos(rngValueRotorStartingPos(mt));
        gene.Rotors()[swappedRotor].ChangeRingSetting(rngValueRotorRingSetting(mt));
    } else {
        if (rngChanceRotorStartingPos(mt)) {
            auto rngInt = std::uniform_int_distribution<int>(0, 2);
            int swappedRotor = rngInt(mt);
            gene.Rotors()[swappedRotor].ChangeStartingPos(rngValueRotorStartingPos(mt));
        }
        if (rngChanceRotorRingSetting(mt)) {
            auto rngInt = std::uniform_int_distribution<int>(0, 2);
            int swappedRotor = rngInt(mt);
            gene.Rotors()[swappedRotor].ChangeRingSetting(rngValueRotorRingSetting(mt));
        }
    }
}

const double& Citizen::Fitness() const { return fitness; }
const Enigma& Citizen::Gene() const { return gene; }
Enigma& Citizen::Gene() { return gene; }