#include "PlugBoard.h"

#include <iostream>

PlugBoard::PlugBoard(const std::vector<std::string>& plugConnections) {
    for (auto const& connection : plugConnections)
        AddConnection(connection[0] - 'A', connection[1] - 'A');
}

void PlugBoard::AddConnection(int input, int output) {
    // in case one of the letters is already connected, do nothing
    if (connections.find(input) != connections.end() || connections.find(output) != connections.end()) {
        std::cout << "Connection " << 'A' + 65 << 'A' + output << " not established\n";
        std::cout << "At least one of the keys is already connected\n";
        return;
    }

    connections[input] = output;
    connections[output] = input;
}

int PlugBoard::ReturnLetter(int input) {
    if (connections.find(input) != connections.end())
        return connections[input];

    return input;
}
