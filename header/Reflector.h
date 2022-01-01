#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <array>
#include <string>

#include "Config.h"

class Reflector {
 private:
    std::string connections;
    static const std::array<std::string, NUMBER_OF_REFLECTOR_TYPES + 1> REFLECTOR_WIRINGS;

 public:
    explicit Reflector(char type);
    Reflector() = default;

    int ReturnLetter(int input);
    void setReflector(char type);

    const std::string& Connections() const;
};
#endif
