#ifndef CONFIG_H
#define CONFIG_H
#include <cmath>
#include <cstddef>

constexpr size_t POP_SIZE = 25;
constexpr size_t TOURNAMENT_SIZE = 2;

constexpr size_t NUMBER_OF_ROTORS_AVAILABLE = 5;
constexpr size_t NUMBER_OF_ROTORS_INSTALLED = 3;
constexpr size_t NUMBER_OF_LETTERS = 26;
constexpr size_t NUMBER_OF_REFLECTOR_TYPES = 3;

// Index of Coincidence for some languages
constexpr double ENGLISH_IOC = 1.73;
constexpr double PORTUGUESE_IOC = 1.94;

// number of evolutive states
constexpr size_t NUMBER_OF_STATES = 4;
constexpr size_t NUMBER_OF_GENES = 4;

constexpr double MUTATION_RATE = 1.0;  // a multiplier of differents mutation rates

constexpr double CROSSOVER_ROTOR_CHANCE = 0.6;      // chance of inheriting some of the other's rotors
constexpr double CROSSOVER_REFLECTOR_CHANCE = 0.5;  // chance of inheriting the other's reflector

// rotorNumber, startingPos, rotorSetting, reflector
constexpr double MUTATE_STATE_CHANCE[NUMBER_OF_GENES][NUMBER_OF_STATES] = {{0.18, 0.82, 0.00, 0.00},   // Estado 1
                                                                           {0.02, 0.98, 0.00, 0.00},   // Estado 2
                                                                           {0.00, 0.00, 1.00, 0.00},   // Estado 3
                                                                           {0.00, 0.00, 0.00, 1.00}};  // Estado 4
/*
// rotorNumber, startingPos, rotorSetting, reflector
constexpr double MUTATE_STATE_CHANCE[NUMBER_OF_GENES][NUMBER_OF_STATES] = {{1.00, 0.00, 0.00, 0.00},   // Estado 1
                                                                           {0.00, 1.00, 0.00, 0.00},   // Estado 2
                                                                           {0.00, 0.00, 1.00, 0.00},   // Estado 3
                                                                           {0.00, 0.00, 0.00, 1.00}};  // Estado 4
*/
// chance of randomly swapping a rotor
constexpr double MUTATE_ROTOR_CHANCE[NUMBER_OF_STATES] = {MUTATE_STATE_CHANCE[0][0],
                                                          MUTATE_STATE_CHANCE[0][1],
                                                          MUTATE_STATE_CHANCE[0][2],
                                                          MUTATE_STATE_CHANCE[0][3]};
// change of randomly swapping the starting position
constexpr double MUTATE_ROTOR_STARTINGPOS_CHANCE[NUMBER_OF_STATES] = {MUTATE_ROTOR_CHANCE[0] + MUTATE_STATE_CHANCE[1][0],
                                                                      MUTATE_ROTOR_CHANCE[1] + MUTATE_STATE_CHANCE[1][1],
                                                                      MUTATE_ROTOR_CHANCE[2] + MUTATE_STATE_CHANCE[1][2],
                                                                      MUTATE_ROTOR_CHANCE[3] + MUTATE_STATE_CHANCE[1][3]};
// chance of randomly swapping the ring setting
constexpr double MUTATE_ROTOR_RINGSETTING_CHANCE[NUMBER_OF_STATES] = {MUTATE_ROTOR_STARTINGPOS_CHANCE[0] + MUTATE_STATE_CHANCE[2][0],
                                                                      MUTATE_ROTOR_STARTINGPOS_CHANCE[1] + MUTATE_STATE_CHANCE[2][1],
                                                                      MUTATE_ROTOR_STARTINGPOS_CHANCE[2] + MUTATE_STATE_CHANCE[2][2],
                                                                      MUTATE_ROTOR_STARTINGPOS_CHANCE[3] + MUTATE_STATE_CHANCE[2][3]};
// chance of randomly swapping the reflector
constexpr double MUTATE_REFLECTOR_CHANCE[NUMBER_OF_STATES] = {MUTATE_ROTOR_RINGSETTING_CHANCE[0] + MUTATE_STATE_CHANCE[3][0],
                                                              MUTATE_ROTOR_RINGSETTING_CHANCE[1] + MUTATE_STATE_CHANCE[3][1],
                                                              MUTATE_ROTOR_RINGSETTING_CHANCE[2] + MUTATE_STATE_CHANCE[3][2],
                                                              MUTATE_ROTOR_RINGSETTING_CHANCE[3] + MUTATE_STATE_CHANCE[3][3]};

constexpr double factorial(double n) { return (n > 1) ? n * factorial(n - 1.0) : 1.0; }

constexpr double SEARCH_SPACE[NUMBER_OF_GENES] = {NUMBER_OF_ROTORS_INSTALLED * factorial(NUMBER_OF_ROTORS_AVAILABLE) / factorial(NUMBER_OF_ROTORS_AVAILABLE - NUMBER_OF_ROTORS_INSTALLED),
                                                  NUMBER_OF_LETTERS* NUMBER_OF_LETTERS* NUMBER_OF_LETTERS,
                                                  NUMBER_OF_LETTERS* NUMBER_OF_LETTERS* NUMBER_OF_LETTERS,
                                                  NUMBER_OF_REFLECTOR_TYPES};
constexpr double SEARCH_SPACE_TOTAL = SEARCH_SPACE[0] * SEARCH_SPACE[1] * SEARCH_SPACE[2] * SEARCH_SPACE[3];

static const size_t STATE_SIZE[NUMBER_OF_STATES] = {static_cast<size_t>(pow(SEARCH_SPACE[0], MUTATE_STATE_CHANCE[0][0]) * pow(SEARCH_SPACE[1], MUTATE_STATE_CHANCE[0][1]) * pow(SEARCH_SPACE[2], MUTATE_STATE_CHANCE[0][2]) * pow(SEARCH_SPACE[3], MUTATE_STATE_CHANCE[0][3])) / 3,
                                                    static_cast<size_t>(pow(SEARCH_SPACE[0], MUTATE_STATE_CHANCE[1][0]) * pow(SEARCH_SPACE[1], MUTATE_STATE_CHANCE[1][1]) * pow(SEARCH_SPACE[2], MUTATE_STATE_CHANCE[1][2]) * pow(SEARCH_SPACE[3], MUTATE_STATE_CHANCE[1][3])) / 3,
                                                    static_cast<size_t>(pow(SEARCH_SPACE[0], MUTATE_STATE_CHANCE[2][0]) * pow(SEARCH_SPACE[1], MUTATE_STATE_CHANCE[2][1]) * pow(SEARCH_SPACE[2], MUTATE_STATE_CHANCE[2][2]) * pow(SEARCH_SPACE[3], MUTATE_STATE_CHANCE[2][3])) / 3,
                                                    static_cast<size_t>(pow(SEARCH_SPACE[0], MUTATE_STATE_CHANCE[3][0]) * pow(SEARCH_SPACE[1], MUTATE_STATE_CHANCE[3][1]) * pow(SEARCH_SPACE[2], MUTATE_STATE_CHANCE[3][2]) * pow(SEARCH_SPACE[3], MUTATE_STATE_CHANCE[3][3])) / 3};
#endif