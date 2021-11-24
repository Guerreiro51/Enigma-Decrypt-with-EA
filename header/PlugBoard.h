#ifndef PLUGBOARD_H
#define PLUGBOARD_H
#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class PlugBoard {
 private:
    std::unordered_map<int, int> connections;

 public:
    PlugBoard(const std::vector<std::string>& plugConnections);
    void AddConnection(int input, int output);
    int ReturnLetter(int input);

    friend class Enigma;
};
#endif
