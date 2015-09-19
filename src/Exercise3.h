#ifndef ALGO3_TP2_EXERCISE3_H
#define ALGO3_TP2_EXERCISE3_H

#include "Exercise.h"
#include <vector>
#include <list>

struct Edge {
    Edge(int iFrom, int iTo, int iWeight) : from(iFrom), to(iTo), weight(iWeight) { }

    bool operator<(const Edge &other) const {
        return weight < other.weight;
    }

    int from;
    int to;
    int weight;
};

/*
 * CUIDADO: conectar 2 veces seguidas no anda. Solo se conecta una vez.
 */
class WeightedGraph {
public:
    WeightedGraph(int maximum) : sum(0), vertices(maximum, std::list<Edge>()) { }
    void connect(int from, int to, int weight);
    bool exists(int node) const;
    int getSum() const;
    int prim();
private:
    int sum;
    std::vector<std::list<Edge>> vertices;
};

class Exercise3 : public Exercise {
public:
    void read(std::string input);
    void solve(int runs, std::string output);

    virtual ~Exercise3() { }
private:
    std::list<WeightedGraph> instances;
};


#endif //ALGO3_TP2_EXERCISE3_H
