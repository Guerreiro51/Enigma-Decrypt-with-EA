#include "Citizen.h"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>
#include <unordered_map>

static std::random_device rd;
static std::mt19937 mt(rd());

Citizen::Citizen(const std::string& cipher, const std::array<int, NUMBER_OF_ROTORS_INSTALLED>& rotorNumbers, const std::array<int, NUMBER_OF_ROTORS_INSTALLED>& rotorStartingPos, const std::array<int, NUMBER_OF_ROTORS_INSTALLED>& rotorRingSettings, const std::vector<std::string>& plugConnections, char reflectorType)
    : gene(rotorNumbers, rotorStartingPos, rotorRingSettings, plugConnections, reflectorType) {
    Evaluate(cipher);
}

Citizen::Citizen(const std::string& cipher) : gene() {
    Evaluate(cipher);
}

void Citizen::Init(const std::string& cipher) {
    gene.Init();
    Evaluate(cipher);
}

float Citizen::indexOfCoincidence(const std::string& text) {
    std::array<float, NUMBER_OF_LETTERS> letters{};
    for (const char& letter : text) {
        if (isalpha(letter))
            letters[toupper(letter) - 'A']++;
    }

    float indexOfCoincidence = std::accumulate(letters.begin(), letters.end(), 0, [](float a, const float& f) { return a + f * (f - 1.0); });

    float textSize = std::reduce(letters.begin(), letters.end());
    indexOfCoincidence = indexOfCoincidence * NUMBER_OF_LETTERS * 1.0f / (textSize * (textSize - 1.0f));

    return indexOfCoincidence;
}

void Citizen::Evaluate(const std::string& cipher) {
    std::string plaintext = gene.Decipher(cipher);
    fitness = fabs(indexOfCoincidence(plaintext) - ENGLISH_IOC);
}

Enigma Citizen::Crossover(const Enigma& mom, const Enigma& dad) {
    std::array<Rotor, NUMBER_OF_ROTORS_INSTALLED> rotors;
    Plugboard plugboard;

    // Reflector crossover (one or the other at random)
    auto rngBernoulli = std::bernoulli_distribution(CROSSOVER_REFLECTOR_CHANCE);
    Reflector reflector = (rngBernoulli(mt)) ? dad.getReflector() : mom.getReflector();

    // Starts off equal to the mom
    for (size_t i = 0; i < mom.Rotors().size(); i++)
        rotors[i] = mom.Rotors()[i];

    // Rotor crossover. Checks if it is equal, a permutation or different
    // in the first case it does nothing
    // in the second case it makes them equal
    // in the third case it swaps a random rotor
    rngBernoulli = std::bernoulli_distribution(CROSSOVER_ROTOR_CHANCE);
    if (rngBernoulli(mt)) {
        // Checking if equal
        bool equal = true;
        for (size_t i = 0; i < mom.Rotors().size(); i++) {
            if (mom.Rotors()[i].RotorNumber() != dad.Rotors()[i].RotorNumber()) {
                equal = false;
                break;
            }
        }

        if (!equal) {
            bool permutation = true;
            // Checking if they're a permutation
            std::unordered_map<int, int> exists;
            for (const Rotor& r : mom.Rotors())
                exists[r.RotorNumber()]++;
            for (const Rotor& r : dad.Rotors()) {
                exists[r.RotorNumber()]--;
                if (exists[r.RotorNumber()])
                    permutation = false;
            }

            if (permutation) {
                for (size_t i = 0; i < rotors.size(); i++)
                    rotors[i].ChangeRotor(dad.Rotors()[i].RotorNumber());
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
        if (rotors[i].RotorNumber() == dad.Rotors()[i].RotorNumber()) {
            rotors[i].ChangeStartingPos((rotors[i].StartingPos() + dad.Rotors()[i].StartingPos()) / 2);
            rotors[i].ChangeRingSetting((rotors[i].RingSetting() + dad.Rotors()[i].RingSetting()) / 2);
        }
    }

    return Enigma(rotors, reflector, plugboard);
}
void Citizen::Crossover(const Enigma& other) {
    gene = Crossover(gene, other);
}

void Citizen::Mutate(int state) {
    static auto rngChance = std::uniform_real_distribution<float>(0.0f, 1.0f);
    float rng = rngChance(mt);

    static auto rngValueRotor = std::uniform_int_distribution<>(0, NUMBER_OF_ROTORS_AVAILABLE - 1);
    static auto rngValueRotorStartingPos = std::uniform_int_distribution<>(0, NUMBER_OF_LETTERS - 1);
    static auto rngValueRotorRingSetting = std::uniform_int_distribution<>(0, NUMBER_OF_LETTERS - 1);

    static auto rngValueReflector = std::uniform_int_distribution<>(0, NUMBER_OF_REFLECTOR_TYPES - 1);

    // Changes one of the rotors to a random one
    if (rng <= MUTATE_ROTOR_CHANCE[state]) {
        auto rngInt = std::uniform_int_distribution<int>(0, NUMBER_OF_ROTORS_INSTALLED - 1);
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
    }

    // Changes the starting position to a random one
    else if (rng <= MUTATE_ROTOR_STARTINGPOS_CHANCE[state]) {
        auto rngInt = std::uniform_int_distribution<int>(0, NUMBER_OF_ROTORS_INSTALLED - 1);
        int swappedRotor = rngInt(mt);
        gene.Rotors()[swappedRotor].ChangeStartingPos(rngValueRotorStartingPos(mt));
    }

    // Changes the ring setting to a random one
    else if (rng <= MUTATE_ROTOR_RINGSETTING_CHANCE[state]) {
        auto rngInt = std::uniform_int_distribution<int>(0, NUMBER_OF_ROTORS_INSTALLED - 1);
        int swappedRotor = rngInt(mt);
        gene.Rotors()[swappedRotor].ChangeRingSetting(rngValueRotorRingSetting(mt));
    }

    // Changes the reflector to a random one
    else if (rng <= MUTATE_REFLECTOR_CHANCE[state])
        gene.getReflector().setReflector(rngValueReflector(mt) + 'A');
}

const float& Citizen::Fitness() const { return fitness; }
const Enigma& Citizen::Gene() const { return gene; }
Enigma& Citizen::Gene() { return gene; }