#ifndef CONFIG_H
#define CONFIG_H
#include <cmath>
#include <cstddef>

constexpr size_t POP_SIZE = 100;
constexpr size_t NUMBER_OF_PROTECTED = 1;
constexpr size_t TOURNAMENT_SIZE = 2;
constexpr size_t NUMBER_OF_EATEN = 10;
constexpr size_t RANDOM_PREDATION_GEN = 10;
constexpr size_t NUMBER_OF_ITERATIONS = 200000;
constexpr size_t NUMBER_OF_ITERATIONS_TO_SHOW = 500;
constexpr size_t NUMBER_OF_CITIZENS_SHOWN = 10;
constexpr bool OUTPUT_DATA_FILES = false;

constexpr const char* MAXFIT_PATH = "../!data/maxFit.txt";
constexpr const char* AVGFIT_PATH = "../!data/avgFit.txt";
constexpr const char* MUTSTATE_PATH = "../!data/mutState.txt";

constexpr size_t NUMBER_OF_ROTORS_AVAILABLE = 5;
constexpr size_t NUMBER_OF_ROTORS_INSTALLED = 3;
constexpr size_t NUMBER_OF_LETTERS = 26;
constexpr size_t NUMBER_OF_REFLECTOR_TYPES = 3;

// Index of Coincidence for some languages
constexpr float ENGLISH_IOC = 1.73f;
constexpr float PORTUGUESE_IOC = 1.94f;

// number of evolutive states
constexpr size_t NUMBER_OF_STATES = 4;
constexpr size_t NUMBER_OF_GENES = 4;

constexpr float CROSSOVER_ROTOR_CHANCE = 0.3f;      // chance of inheriting some of the other's rotors
constexpr float CROSSOVER_REFLECTOR_CHANCE = 0.5f;  // chance of inheriting the other's reflector

// rotorNumber, startingPos, ringSetting, reflector
constexpr float MUTATE_STATE_CHANCE[NUMBER_OF_STATES][NUMBER_OF_GENES] = {{0.14f, 0.809f, 0.05f, 0.001f},  // Estado 1
                                                                          {0.019f, 0.93f, 0.05f, 0.001f},  // Estado 2
                                                                          {0.00f, 0.00f, 1.00f, 0.00f},    // Estado 3
                                                                          {0.00f, 0.00f, 0.00f, 1.00f}};   // Estado 4
/*
// rotorNumber, startingPos, rotorSetting, reflector
constexpr float MUTATE_STATE_CHANCE[NUMBER_OF_GENES][NUMBER_OF_STATES] = {{1.00f, 0.00f, 0.00f, 0.00f},    // Estado 1
                                                                           {0.00f, 1.00f, 0.00f, 0.00f},   // Estado 2
                                                                           {0.00f, 0.00f, 1.00f, 0.00f},   // Estado 3
                                                                           {0.00f, 0.00f, 0.00f, 1.00f}};  // Estado 4
*/
// chance of randomly swapping a rotor
constexpr float MUTATE_ROTOR_CHANCE[NUMBER_OF_STATES] = {MUTATE_STATE_CHANCE[0][0],
                                                         MUTATE_STATE_CHANCE[0][1],
                                                         MUTATE_STATE_CHANCE[0][2],
                                                         MUTATE_STATE_CHANCE[0][3]};
// change of randomly swapping the starting position
constexpr float MUTATE_ROTOR_STARTINGPOS_CHANCE[NUMBER_OF_STATES] = {MUTATE_ROTOR_CHANCE[0] + MUTATE_STATE_CHANCE[1][0],
                                                                     MUTATE_ROTOR_CHANCE[1] + MUTATE_STATE_CHANCE[1][1],
                                                                     MUTATE_ROTOR_CHANCE[2] + MUTATE_STATE_CHANCE[1][2],
                                                                     MUTATE_ROTOR_CHANCE[3] + MUTATE_STATE_CHANCE[1][3]};
// chance of randomly swapping the ring setting
constexpr float MUTATE_ROTOR_RINGSETTING_CHANCE[NUMBER_OF_STATES] = {MUTATE_ROTOR_STARTINGPOS_CHANCE[0] + MUTATE_STATE_CHANCE[2][0],
                                                                     MUTATE_ROTOR_STARTINGPOS_CHANCE[1] + MUTATE_STATE_CHANCE[2][1],
                                                                     MUTATE_ROTOR_STARTINGPOS_CHANCE[2] + MUTATE_STATE_CHANCE[2][2],
                                                                     MUTATE_ROTOR_STARTINGPOS_CHANCE[3] + MUTATE_STATE_CHANCE[2][3]};
// chance of randomly swapping the reflector
constexpr float MUTATE_REFLECTOR_CHANCE[NUMBER_OF_STATES] = {MUTATE_ROTOR_RINGSETTING_CHANCE[0] + MUTATE_STATE_CHANCE[3][0],
                                                             MUTATE_ROTOR_RINGSETTING_CHANCE[1] + MUTATE_STATE_CHANCE[3][1],
                                                             MUTATE_ROTOR_RINGSETTING_CHANCE[2] + MUTATE_STATE_CHANCE[3][2],
                                                             MUTATE_ROTOR_RINGSETTING_CHANCE[3] + MUTATE_STATE_CHANCE[3][3]};

constexpr float factorial(float n) { return (n > 1) ? n * factorial(n - 1.0f) : 1.0f; }

constexpr float SEARCH_SPACE[NUMBER_OF_GENES] = {NUMBER_OF_ROTORS_INSTALLED * factorial(NUMBER_OF_ROTORS_AVAILABLE) / factorial(NUMBER_OF_ROTORS_AVAILABLE - NUMBER_OF_ROTORS_INSTALLED),
                                                 NUMBER_OF_LETTERS* NUMBER_OF_LETTERS* NUMBER_OF_LETTERS,
                                                 NUMBER_OF_LETTERS* NUMBER_OF_LETTERS* NUMBER_OF_LETTERS,
                                                 NUMBER_OF_REFLECTOR_TYPES};
constexpr float SEARCH_SPACE_TOTAL = SEARCH_SPACE[0] * SEARCH_SPACE[1] * SEARCH_SPACE[2] * SEARCH_SPACE[3];

static const size_t STATE_SIZE[NUMBER_OF_STATES] = {1000, 700, 1000, 10};
/*
static const size_t STATE_SIZE[NUMBER_OF_STATES] = {static_cast<size_t>(pow(SEARCH_SPACE[0], MUTATE_STATE_CHANCE[0][0]) * pow(SEARCH_SPACE[1], MUTATE_STATE_CHANCE[0][1]) * pow(SEARCH_SPACE[2], MUTATE_STATE_CHANCE[0][2]) * pow(SEARCH_SPACE[3], MUTATE_STATE_CHANCE[0][3])) / 3,
                                                    static_cast<size_t>(pow(SEARCH_SPACE[0], MUTATE_STATE_CHANCE[1][0]) * pow(SEARCH_SPACE[1], MUTATE_STATE_CHANCE[1][1]) * pow(SEARCH_SPACE[2], MUTATE_STATE_CHANCE[1][2]) * pow(SEARCH_SPACE[3], MUTATE_STATE_CHANCE[1][3])) / 3,
                                                    static_cast<size_t>(pow(SEARCH_SPACE[0], MUTATE_STATE_CHANCE[2][0]) * pow(SEARCH_SPACE[1], MUTATE_STATE_CHANCE[2][1]) * pow(SEARCH_SPACE[2], MUTATE_STATE_CHANCE[2][2]) * pow(SEARCH_SPACE[3], MUTATE_STATE_CHANCE[2][3])) / 3,
                                                    static_cast<size_t>(pow(SEARCH_SPACE[0], MUTATE_STATE_CHANCE[3][0]) * pow(SEARCH_SPACE[1], MUTATE_STATE_CHANCE[3][1]) * pow(SEARCH_SPACE[2], MUTATE_STATE_CHANCE[3][2]) * pow(SEARCH_SPACE[3], MUTATE_STATE_CHANCE[3][3])) / 3};
*/
#endif