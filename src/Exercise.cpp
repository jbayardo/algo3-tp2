#include "Exercise.h"

std::list<std::string> split(std::string string, char delim) {
    std::list<std::string> output;
    std::string current;
    std::stringstream stream(string);

    while (std::getline(stream, current, delim)) {
        output.push_back(current);
    }

    return output;
}