#ifndef ALGO3_TP2_EXERCISE2_H
#define ALGO3_TP2_EXERCISE2_H

#include "Exercise.h"
#include <vector>
#include <set>

class ShortestPath {
public:
	ShortestPath(int iFloors, int length, int iPortals);
	void addPortal(int fromFloor, int fromD, int toFloor, int toD);
	void connect(int from, int to);
	inline int getNodeIndex(int floor, int pos);
	int solve();
private:
	int floors;								//Cantidad de pisos
	int length;								//Longitud de pasillos
	int portalIndex;						//Indice de portales intermedios (para costo 2 de viaje por portales)
	int goal;								//La meta (el aula de algo 3)
	std::vector<std::set<int>> adjacency;	//Lista de adyacencia
	std::vector<bool> isPortal;				//Guardo si en una posicion de un piso hay un portal (para chequear que el input este bien)
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
