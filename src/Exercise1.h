#ifndef ALGO3_TP2_EXERCISE1_H
#define ALGO3_TP2_EXERCISE1_H

#include "Exercise.h"
#include <vector>

class Maximize {
public:
    Maximize(int iFloors);
    int solve();
    void addPortal(int from, int to);
    virtual ~Maximize();
private:
    int floors;
    int portals;
    bool **adjacency;
};

class Exercise1 : public Exercise {
public:
    void read(std::string input);
    void solve(int runs, std::string output);
    virtual ~Exercise1() { }
private:
    std::list<Maximize> instances;
};


#endif //ALGO3_TP2_EXERCISE1_H
