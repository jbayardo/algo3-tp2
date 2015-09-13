//
// Created by julian on 9/13/15.
//

#ifndef ALGO3_TP2_EXERCISE_H
#define ALGO3_TP2_EXERCISE_H

#include <string>

class Exercise {
public:
    Exercise() { };
    virtual void read(std::string) = 0;
    virtual void solve() const = 0;
    virtual void write(std::string) = 0;
    virtual ~Exercise() { };
};


#endif //ALGO3_TP2_EXERCISE_H
