#ifndef ALGO3_TP2_EXERCISE_H
#define ALGO3_TP2_EXERCISE_H

#include <string>
#include <list>
#include <sstream>

class Exercise {
public:
    Exercise() { };
    virtual void read(std::string input) = 0;
    virtual void solve(int runs, std::string output) = 0;
    virtual ~Exercise() { };
};

extern std::list<std::string> split(std::string string, char delim);

#endif //ALGO3_TP2_EXERCISE_H
