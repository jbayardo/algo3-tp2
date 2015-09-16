#ifndef ALGO3_TP2_EXERCISE1_H
#define ALGO3_TP2_EXERCISE1_H

#include "Exercise.h"

class Exercise1 : public Exercise {
public:
    Exercise1();
    void read(std::string input);
    void solve(int runs) const;
    void write(std::string output);

    ~Exercise1() { }
private:
    int floors;

};


#endif //ALGO3_TP2_EXERCISE1_H
