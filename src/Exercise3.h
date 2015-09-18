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
        if (weight < other.weight) {
            return true;
        } else {
            return false;
        }
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

    bool connected(int from, int to) {
        if (vertices.find(from) == vertices.end() || vertices.find(to) == vertices.end()) {
            return false;
        }

        int check;
        int which;

        if (vertices[from].size() < vertices[to].size()) {
            check = from;
            which = to;
        } else {
            check = to;
            which = from;
        }

        for (auto &edge : vertices[check]) {
            if (edge.to == which) {
                return true;
            }
        }

        return false;
    }

    void connect(int from, int to, int weight) {
        if (vertices.find(from) == vertices.end()) {
            vertices[from] = std::list<Edge>();
        }

        if (vertices.find(to) == vertices.end()) {
            vertices[to] = std::list<Edge>();
        }

        vertices[from].push_back(Edge(from, to, weight));
        vertices[to].push_back(Edge(to, from, weight));

        sum += weight;
    }

    bool exists(int node) const {
        if (vertices.find(node) == vertices.end()) {
            return false;
        }

        return true;
    }

    int getSum() const {
        return sum;
    }

    std::size_t size() const {
        return this->vertices.size();
    }

    int prim() {
        WeightedGraph output;
        std::priority_queue<Edge> queue;

        // Pongo todos los vertices que conectan la fuente con otro
        for (auto &edge : vertices[0]) {
            queue.push(edge);
        }

        // Hasta que no nos hallamos quedado sin aristas
        while (!queue.empty()) {
            // Tomamos la arista mas chica que conecta a un nodo que ya esta en
            // el arbol con algun otro nodo
            Edge current = queue.top();
            queue.pop();

            // Si el otro nodo no esta en el arbol
            if (!output.exists(current.to)) {
                // Lo conectamos!
                output.connect(current.from, current.to, current.weight);

                // Agregamos los vertices nuevos
                for (auto &edge : vertices[current.to]) {
                    queue.push(edge);
                }
            }
        }

        return output.getSum();
    }
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
