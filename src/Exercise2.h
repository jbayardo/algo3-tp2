#ifndef ALGO3_TP2_EXERCISE2_H
#define ALGO3_TP2_EXERCISE2_H

#include "Exercise.h"

class Exercise2 : public Exercise {
public:
    void read(std::string input);
    void solve(int runs, std::string output);
    virtual ~Exercise2() { }
private:
};


#endif //ALGO3_TP2_EXERCISE2_H
