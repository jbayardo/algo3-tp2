#ifndef ALGO3_TP2_EXERCISE2_H
#define ALGO3_TP2_EXERCISE2_H

#include "Exercise.h"
#include <vector>
#include <list>

class ShortestPath {
public:
	ShortestPath(int ifloors, int ilength, int portals);
	void addPortal(int fromFloor, int fromD, int toFloor, int toD);
	void connect(int from, int to);
	inline int getNodeIndex(int floor, int pos);
	int solve();
private:
	int floors;								//Cantidad de pisos
	int length;								//Longitud de pasillos
	int portalIndex;						//Indice de portales intermedios (para costo 2 de viaje por portales)
	int goal;								//La meta (el aula de algo 3)
	std::vector<std::list<int>> adjacency;	//Lista de adyacencia
};
class Exercise2 : public Exercise {
public:
    void read(std::string input);
    void solve(int runs, std::string output);
    virtual ~Exercise2() { }
private:
	std::list<ShortestPath> instances;
};


#endif //ALGO3_TP2_EXERCISE2_H
