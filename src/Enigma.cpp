#include "Enigma.h"

#include <algorithm>
#include <random>
#include <sstream>

Enigma::Enigma(const std::array<int, 3>& rotorNumbers, const std::array<int, 3>& rotorStartPositions, const std::array<int, 3>& rotorRingSettings,
               const std::vector<std::string>& plugConnections, char reflectorType)
    : plugboard(plugConnections), reflector(reflectorType) {
    for (size_t i = 0; i < rotors.size(); i++)
        rotors[i] = Rotor(rotorNumbers[i], rotorStartPositions[i], rotorRingSettings[i]);
}
Enigma::Enigma(std::array<Rotor, 3>& rotors, Reflector& reflector, PlugBoard& plugboard) : rotors(rotors), reflector(reflector), plugboard(plugboard) {}

void Enigma::Init(const std::array<int, 3>& rotorNumbers, const std::array<int, 3>& rotorStartPositions, const std::array<int, 3>& rotorRingSettings, const std::vector<std::string>& plugConnections, char reflectorType) {
    for (size_t i = 0; i < rotors.size(); i++)
        rotors[i] = Rotor(rotorNumbers[i], rotorStartPositions[i], rotorRingSettings[i]);
    plugboard = plugConnections;
    reflector = reflectorType;
}

Enigma::Enigma() {
    static std::random_device rd;
    static std::mt19937 mt(rd());

    // Chooses random rotors
    std::array<int, 8> random1to8;
    std::iota(random1to8.begin(), random1to8.end(), 0);
    std::random_shuffle(random1to8.begin(), random1to8.end());
    std::array<int, 3> rotorNumbers = {random1to8[0], random1to8[1], random1to8[2]};

    // Chooses random starting position and ring settings
    auto rng = std::uniform_int_distribution<int>(0, 25);
    std::array<int, 3> rotorStartPositions = {0, 0, 0};
    std::array<int, 3> rotorRingSettings = {0, 0, 0};

    // Generates random plugConnections
    rng = std::uniform_int_distribution<int>(0, 10);  // uniform int distribution to generate the number of connections
    std::vector<std::string> plugConnections(0);
    std::array<char, 26> randomConnections;
    std::iota(randomConnections.begin(), randomConnections.end(), 'A');
    std::random_shuffle(randomConnections.begin(), randomConnections.end());
    for (size_t i = 0; i < plugConnections.size(); i++)
        plugConnections[i] = std::string() + randomConnections[2 * i] + randomConnections[2 * i + 1];

    // Generates random reflector type
    rng = std::uniform_int_distribution<int>(0, 2);
    char reflectorType = rng(mt) + 'A';

    Init(rotorNumbers, rotorStartPositions, rotorRingSettings, plugConnections, reflectorType);
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
    s << "Rotor Numbers: (" << rotors[0].rotorNumber + 1 << ", " << rotors[1].rotorNumber + 1 << ", " << rotors[2].rotorNumber + 1 << ")\n";
    s << "Rotor Position: (" << rotors[0].currentPos + 1 << ", " << rotors[1].currentPos + 1 << ", " << rotors[2].currentPos + 1 << ")\n";
    s << "Rotor RingSetting: (" << rotors[0].ringSetting + 1 << ", " << rotors[1].ringSetting + 1 << ", " << rotors[2].ringSetting + 1 << ")\n\n";

    s << "Plugboard connections: ";
    for (const auto& plugConnection : plugboard.connections)
        s << (char)(plugConnection.first + 'A') << (char)(plugConnection.second + 'A') << ' ';
    s << "\n\n";

    s << "Reflector: " << reflector.connections << '\n';

    return s.str();
}

void Enigma::Reset() {
    for (Rotor& rotor : rotors)
        rotor.Reset();
}

std::ostream& operator<<(std::ostream& os, const Enigma& e) {
    os << e.show();
    return os;
}
