#ifndef ALGO3_TP2_EXERCISE3_H
#define ALGO3_TP2_EXERCISE3_H

#include "Exercise.h"
#include <vector>
#include <list>

class DisjointSet {
public:
	DisjointSet(std::size_t size)
		: rank(size, 1), parent(size, 0)
	{
		for (std::size_t i = 0; i < size; ++i)
		{
			parent[i] = i;
		}
	}

	void merge(int a, int b)
	{
		a = find(a);
		b = find(b);

		// Do not merge sets with the same representatives
		if (a == b) return;

		if (rank[a] < rank[b])
		{
			parent[a] = b;
		}
		else if (rank[a] > rank[b])
		{
			parent[b] = a;
		}
		else
		{
			parent[a] = b;
			rank[b] += 1;
		}
	}

	int find(int element)
	{
		int current = element;

		while (parent[current] != current)
		{
			current = parent[current];
		}

		while (parent[element] != current)
		{
			int next = parent[element];
			parent[element] = current;
			element = next;
		}

		return current;
	}
private:
	// rank[i] always keep the height of the tree rooted at i
	std::vector<int> rank;
	// parent[i] points to the parent of i. parent[i] = i \iff i is the root
	std::vector<int> parent;
};

struct Edge {
    Edge(int iFrom, int iTo, int iWeight) : from(iFrom), to(iTo), weight(iWeight) { }
    Edge(const Edge& e) : from(e.from), to(e.to), weight(e.weight) { }
    bool operator>(const Edge &other) const {
        return weight > other.weight;
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
    WeightedGraph(std::size_t iVertices) : sum(0), edges(0), vertices(iVertices) { }
    WeightedGraph(std::size_t iVertices, const std::list<Edge>& iEdges) : sum(0), edges(iEdges.size()),
                                                                          vertices(iVertices) {
        Timer timer("Excercise 3 Generate Graph Timer");
        for (auto &e: iEdges) {
            adjacency.push_back(Edge(e));
            sum += e.weight;
        }
    }
    void connect(int from, int to, int weight);
    int inline getEdgeSum() const;
    std::size_t inline getEdgeSize() const;
    WeightedGraph kruskal();
private:
    int sum;
    std::size_t edges;
    std::size_t vertices;
    std::list<Edge> adjacency;
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
