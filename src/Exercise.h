//
// Created by julian on 9/13/15.
//

#ifndef ALGO3_TP2_EXERCISE_H
#define ALGO3_TP2_EXERCISE_H

#include <string>
#include <list>
#include <sstream>

class Exercise {
public:
    Exercise() { };
    virtual void read(std::string input) = 0;
    virtual void solve(int runs) const = 0;
    virtual void write(std::string output) = 0;
    virtual ~Exercise() { };
};

std::list<std::string> split(std::string string, char delim) {
    std::list<std::string> output;
    std::string current;
    std::stringstream stream(string);

    while (std::getline(stream, current, delim)) {
        output.push_back(current);
    }

    return output;
}


#endif //ALGO3_TP2_EXERCISE_H
