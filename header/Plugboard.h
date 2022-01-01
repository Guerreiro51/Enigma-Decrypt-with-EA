#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include <string>
#include <unordered_map>
#include <vector>

class Plugboard {
 private:
    std::unordered_map<int, int> connections;

 public:
    explicit Plugboard(const std::vector<std::string>& plugConnections);
    Plugboard() = default;

    void AddConnection(int input, int output);
    int ReturnLetter(int input);

    const std::unordered_map<int, int> Connections() const;
};
#endif
