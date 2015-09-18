#ifndef ALGO3_TP2_EXERCISE3_H
#define ALGO3_TP2_EXERCISE3_H

#include "Exercise.h"
#include <vector>
#include <list>
#include <queue>
#include <limits>
#include <unordered_map>

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
 * TODO: ver si esta todo bien con que usemos un hash map, es una paja sino
 */
class WeightedGraph {
public:
    WeightedGraph() : sum(0) { }
    void connect(int from, int to, int weight);
    bool exists(int node) const;
    int getSum() const;
    std::size_t size() const;
    int prim();
private:
    std::unordered_map<int, std::list<Edge>> vertices;
    int sum;
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
