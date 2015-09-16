#ifndef ALGO3_TP2_EXERCISE2_H
#define ALGO3_TP2_EXERCISE2_H

#include "Exercise.h"

class Exercise2 : public Exercise {
public:
    Exercise2();
    void read(std::string);
    void solve(int runs) const;
    void write(std::string);

    ~Exercise2() { }
private:
    int floors;
    int portals;
};


#endif //ALGO3_TP2_EXERCISE2_H
