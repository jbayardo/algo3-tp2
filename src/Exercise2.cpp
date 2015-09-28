#include <fstream>
#include <iostream>
#include <stdexcept>
#include "Exercise2.h"
#include <queue>
#include <limits>

/*Basicamente se que de una tengo un vertice por posicion posible en el edificio N pisos, L posiciones por piso = N*L vertices.
Luego, como la consigna pide que un viaje por portal tenga un costo de 2 metros, lo que hacemos es, en ves de conectar las
posiciones que conecta ese portal directamente, lo hacemos a travez de un intermediario:
(fromFloor, fromD) -> intermediario -> (toFloor, toD)

El edificio se puede ver como una matriz de ixj siendo i pisos y j longuitud de los pasillos. De ahi viene la transformacion
de una posicion a un indice en el vector de adyacencia, para convertir una direccion x,y en una direccion lineal.

Los intermediarios los dejo a lo ultimo de la lista.*/
ShortestPath::ShortestPath(int ifloors, int ilength, int portals) : 
	floors(ifloors), 
	length(ilength), 
	portalIndex(floors * length),
	goal((floors * length) - 1),
	adjacency(std::vector<std::set<int>>(floors * length + portals)) {
	//Conecto las posiciones dentro de cada piso
	for (int floor = 0; floor < floors; ++floor) {
		for (int pos = 0; pos < length - 1; ++pos) {
			connect(getNodeIndex(floor, pos), getNodeIndex(floor, pos + 1));
		}
	}
}

void ShortestPath::addPortal(int fromFloor, int fromD, int toFloor, int toD) {
	//Obtengo los indices de los vertices segun el piso y la posicion dentro del piso
	int from = getNodeIndex(fromFloor, fromD);
	int to = getNodeIndex(toFloor, toD);
	//Si esas posiciones no tienen un portal, entonces hago la conexion, sino hay un error con el input
	//Los conecto a traves de un intermediario, asi cumple los 2 metros de costo para viajes por portales
	connect(from, portalIndex);
	connect(portalIndex, to);

	//Incremento el indice para apuntar al siguiente vertices intermediario
	portalIndex++;
}

void ShortestPath::connect(int nodef, int nodet) {
	//Si no estan conectados, los conecto, sino aviso que el pedido es inesperado 
	if (adjacency[nodef].find(nodet) == adjacency[nodef].end()) {
		adjacency[nodef].insert(nodet);
		adjacency[nodet].insert(nodef);
	} else {
		std::cout << "Unexpected request: Already connected" << std::endl;
	}
}

//Mapea la posicion especifica a un vertice del grafo
inline int ShortestPath::getNodeIndex(int floor, int pos) {
	return (floor * this->length) + pos;
}

void printp(std::vector<int> &p, int floors, int length) {
	for (int x = floors - 1; x >= 0; --x) {
		for (int y = 0; y < length; ++y) {
			printf("%2d ", p[x*length + y]);
		}
		std::cout << std::endl;
	}
	std::cin.ignore();
}

int ShortestPath::solve() {
	//Cola
	std::queue<int> Q;
	//Distancias desde el vertice inicial
	std::vector<int> distance(this->adjacency.size(), -1);
	std::vector<int> parent(this->adjacency.size(), -1);
	//Inicializo el vertice inicial y lo introduzco lentamente en la cola
	distance[0] = 0;
	Q.push(0);

	while (!Q.empty()) {
		//Desencolo
		auto now = Q.front();
		Q.pop();
		//Itero por los vecinos del vertice actual (a lo sumo 3)
		for (auto neighbor : this->adjacency[now]) {
			//Si no lo habia alcanzado hasta ahora, actualizo su distancia y lo introduzco en la cola
			if (distance[neighbor] == -1) {
				distance[neighbor] = distance[now] + 1;
				parent[neighbor] = now;
				Q.push(neighbor);
			}
			if (neighbor == this->goal) {
				return distance[neighbor];
			}
		}
	}
	//Devuelvo la distancia hasta el objetivo, si es -1 es que no se puede alcanzar desde el vertice inicial
	//printp(distance, this->floors, this->length);
	return distance[this->goal];
}


/***********************************************************************************************************************
 *                                              Entrada y Salida
 **********************************************************************************************************************/
void Exercise2::read(std::string input) {
    int test = 0;
    std::ifstream handle;
    handle.open(input, std::ifstream::in);

    if (!handle.is_open()) {
        throw std::runtime_error("Fallo al abrir el archivo de tests para el ejercicio 2");
    }

    int floors;

    // Mientras que podamos leer un piso
    while (handle >> floors) {
        int length;
        
		handle >> length;
        std::string line;
		//TODO: Preguntar (fijarse caso uno test catedra)
		floors++; 
		length++;

        // Leemos una linea no vacia
        while (line.length() == 0 && !handle.fail()) {
            std::getline(handle, line);
        }

        // Si no hubo errores, tenemos una linea no vacia
		std::list<std::string> portals = split(line, ';');
		ShortestPath instance(floors, length, portals.size());

        if (!handle.fail()) {
            // Splitteamos por ; y procesamos individualmente
			for (auto &portal : portals) {
                int from, dFrom, to, dTo;
                std::stringstream endpoints(portal);
                endpoints >> from >> dFrom >> to >> dTo;
				instance.addPortal(from, dFrom, to, dTo);
            }
        } else {
            // Hubo un error, abortar!
            handle.close();
            throw std::runtime_error("Fallo al leer el archivo de tests para el ejercicio 2");
        }
		this->instances.push_back(instance);
        ++test;
    }

    handle.close();
}

/* Resuelve runs veces por caso de test!
 */
void Exercise2::solve(int runs, std::string output) {
	std::ofstream handle(output.c_str(), std::ofstream::out | std::ofstream::trunc);

	for (auto &instance : instances) {
		for (auto i = 0; i < runs - 1; ++i) {
			instance.solve();
		}

		handle << instance.solve() << std::endl;
	}

	handle.close();
}