#include "Enigma.h"

#include <algorithm>
#include <random>
#include <sstream>

Enigma::Enigma(const std::array<int, NUMBER_OF_ROTORS_INSTALLED>& rotorNumbers, const std::array<int, NUMBER_OF_ROTORS_INSTALLED>& rotorStartingPos, const std::array<int, NUMBER_OF_ROTORS_INSTALLED>& rotorRingSettings,
               const std::vector<std::string>& plugConnections, char reflectorType)
    : reflector(reflectorType), plugboard(plugConnections) {
    for (size_t i = 0; i < rotors.size(); i++)
        rotors[i] = Rotor(rotorNumbers[i], rotorStartingPos[i], rotorRingSettings[i]);
}

Enigma::Enigma(const std::array<Rotor, NUMBER_OF_ROTORS_INSTALLED>& rotors, const Reflector& reflector, const Plugboard& plugboard)
    : rotors(rotors), reflector(reflector), plugboard(plugboard) {}

Enigma::Enigma() {
    Init();
}

void Enigma::Init(const std::array<int, NUMBER_OF_ROTORS_INSTALLED>& rotorNumbers, const std::array<int, NUMBER_OF_ROTORS_INSTALLED>& rotorStartingPos, const std::array<int, NUMBER_OF_ROTORS_INSTALLED>& rotorRingSettings, const std::vector<std::string>& plugConnections, char reflectorType) {
    for (size_t i = 0; i < rotors.size(); i++)
        rotors[i] = Rotor(rotorNumbers[i], rotorStartingPos[i], rotorRingSettings[i]);
    plugboard = Plugboard(plugConnections);
    reflector = Reflector(reflectorType);
}

void Enigma::Init(const std::array<Rotor, NUMBER_OF_ROTORS_INSTALLED>& rotors, const Reflector& reflector, const Plugboard& plugboard) {
    for (size_t i = 0; i < rotors.size(); i++)
        this->rotors[i] = rotors[i];
    this->plugboard = plugboard;
    this->reflector = reflector;
}

void Enigma::Init() {
    static std::random_device rd;
    static std::mt19937 mt(rd());

    // Chooses random rotors
    std::array<int, NUMBER_OF_ROTORS_AVAILABLE> random1to8;
    std::iota(random1to8.begin(), random1to8.end(), 0);
    std::shuffle(random1to8.begin(), random1to8.end(), mt);
    std::array<int, NUMBER_OF_ROTORS_INSTALLED> rotorNumbers = {random1to8[0], random1to8[1], random1to8[2]};

    // Chooses random starting position and ring settings
    auto rng = std::uniform_int_distribution<int>(0, NUMBER_OF_LETTERS-1);
    std::array<int, NUMBER_OF_ROTORS_INSTALLED> rotorStartingPos = {rng(mt), rng(mt), rng(mt)};
    std::array<int, NUMBER_OF_ROTORS_INSTALLED> rotorRingSettings = {rng(mt), rng(mt), rng(mt)};

    // Generates random plugConnections
    rng = std::uniform_int_distribution<int>(0, 10);  // uniform int distribution to generate the number of connections
    std::vector<std::string> plugConnections(0);
    std::array<char, NUMBER_OF_LETTERS> randomConnections;
    std::iota(randomConnections.begin(), randomConnections.end(), 'A');
    std::shuffle(randomConnections.begin(), randomConnections.end(), mt);
    for (size_t i = 0; i < plugConnections.size(); i++)
        plugConnections[i] = std::string() + randomConnections[2 * i] + randomConnections[2 * i + 1];

    // Generates random reflector type
    rng = std::uniform_int_distribution<int>(0, NUMBER_OF_REFLECTOR_TYPES-1);
    char reflectorType = rng(mt) + 'A';

    Init(rotorNumbers, rotorStartingPos, rotorRingSettings, plugConnections, reflectorType);
}

void Enigma::Rotate() {
    if (rotors[1].IsAtNotch()) {
        rotors[0].Rotate();
        rotors[1].Rotate();
    } else if (rotors[2].IsAtNotch()) {
        rotors[1].Rotate();
    }

    rotors[2].Rotate();
}

std::string Enigma::Encipher(const std::string& PlainText) {
    std::string output("");
    for (const auto& c : PlainText) {
        if (!isalpha(c)) {
            output += c;
        } else if (islower(c)) {
            output += tolower(EncryptChar(toupper(c)));
        } else {
            output += EncryptChar(c);
        }
    }
    Reset();
    return output;
}

std::string Enigma::Decipher(const std::string& CipherText) {
    return Encipher(CipherText);
}

char Enigma::EncryptChar(char letter) {
    Rotate();

    int letterIndex = letter - 'A';

    // Pass thorugh the plugboard
    letterIndex = plugboard.ReturnLetter(letterIndex);

    // Pass thorugh the rotors
    letterIndex = rotors[2].Forward(letterIndex);
    letterIndex = rotors[1].Forward(letterIndex);
    letterIndex = rotors[0].Forward(letterIndex);

    // Pass thorugh the reflector
    letterIndex = reflector.ReturnLetter(letterIndex);

    // Pass thorugh the rotors in reverse
    letterIndex = rotors[0].Backward(letterIndex);
    letterIndex = rotors[1].Backward(letterIndex);
    letterIndex = rotors[2].Backward(letterIndex);

    // Pass thorugh the plugboard again
    letterIndex = plugboard.ReturnLetter(letterIndex);

    return letterIndex + 'A';
}

std::string Enigma::show() const {
    std::stringstream s;
    s << "Rotor Numbers: (" << rotors[0].RotorNumber() + 1 << ", " << rotors[1].RotorNumber() + 1 << ", " << rotors[2].RotorNumber() + 1 << ")\n";
    s << "Rotor Position: (" << rotors[0].StartingPos() + 1 << ", " << rotors[1].StartingPos() + 1 << ", " << rotors[2].StartingPos() + 1 << ")\n";
    s << "Rotor RingSetting: (" << rotors[0].RingSetting() + 1 << ", " << rotors[1].RingSetting() + 1 << ", " << rotors[2].RingSetting() + 1 << ")\n\n";

    s << "Plugboard connections: ";
    for (const auto& plugConnection : plugboard.Connections())
        s << (char)(plugConnection.first + 'A') << (char)(plugConnection.second + 'A') << ' ';
    s << "\n\n";

    s << "Reflector: " << reflector.Connections() << '\n';

    return s.str();
}

void Enigma::Reset() {
    for (Rotor& rotor : rotors)
        rotor.Reset();
}

std::array<Rotor, NUMBER_OF_ROTORS_INSTALLED>& Enigma::Rotors() { return rotors; }
Reflector& Enigma::getReflector() { return reflector; }
Plugboard& Enigma::getPlugboard() { return plugboard; }

const std::array<Rotor, NUMBER_OF_ROTORS_INSTALLED>& Enigma::Rotors() const { return rotors; }
const Reflector& Enigma::getReflector() const { return reflector; }
const Plugboard& Enigma::getPlugboard() const { return plugboard; }

std::ostream& operator<<(std::ostream& os, const Enigma& e) {
    os << e.show();
    return os;
}
