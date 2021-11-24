#include "Enigma.h"

#include <sstream>

Enigma::Enigma(const std::array<int, 3>& rotorNumbers, const std::array<int, 3>& rotorStartPositions, const std::array<int, 3>& rotorRingSettings,
               const std::vector<std::string>& plugConnections, char reflectorType)
    : plugboard(plugConnections), reflector(reflectorType) {
    for (size_t i = 0; i < rotors.size(); i++)
        rotors[i] = Rotor(rotorNumbers[i], rotorStartPositions[i], rotorRingSettings[i]);
}

void Enigma::init(const std::array<int, 3>& rotorNumbers, const std::array<int, 3>& rotorStartPositions, const std::array<int, 3>& rotorRingSettings, const std::vector<std::string>& plugConnections, char reflectorType) {
    for (size_t i = 0; i < rotors.size(); i++)
        rotors[i] = Rotor(rotorNumbers[i], rotorStartPositions[i], rotorRingSettings[i]);
    plugboard = plugConnections;
    reflector = reflectorType;
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

std::ostream& operator<<(std::ostream& os, const Enigma& e) {
    os << e.show();
    return os;
}
