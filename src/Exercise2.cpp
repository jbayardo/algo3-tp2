#include <fstream>
#include <iostream>
#include <stdexcept>
#include "Exercise2.h"
#include <queue>
#include "Statistics.h"

/*Básicamente sé que de una tengo un vértice por posición posible en el edificio de N pisos, L posiciones por piso = N*L vertices.
Luego, como la consigna pide que un viaje por portal tenga un costo de 2 segundos, lo que hacemos es, en vez de conectar las
posiciones que conecta ese portal directamente, lo hacemos a través de un intermediario:
(fromFloor, fromD) -> intermediario -> (toFloor, toD)

El edificio se puede ver como una matriz de ixj siendo i pisos y j longuitud de los pasillos. De ahí viene la transformación
de una posición a un índice en el vector de adyacencia, para convertir una dirección x,y en una dirección lineal.

Los intermediarios los dejo a lo último de la lista.*/
ShortestPath::ShortestPath(int ifloors, int ilength, int portals) : 
	floors(ifloors), 
	length(ilength), 
	portalIndex(floors * length),
	goal((floors * length) - 1),
	adjacency(std::vector<std::list<int>>(floors * length + portals)) {

	Timer timer("Excercise 2 Generate Graph Timer");

	// Conecto las posiciones dentro de cada piso
	for (int floor = 0; floor < floors; ++floor) {
		for (int pos = 0; pos < length - 1; ++pos) {
			connect(getNodeIndex(floor, pos), getNodeIndex(floor, pos + 1));
		}
	}
}

void ShortestPath::addPortal(int fromFloor, int fromD, int toFloor, int toD) {
	// Obtengo los indices de los vertices segun el piso y la posicion dentro del piso
	int from = getNodeIndex(fromFloor, fromD);
	int to = getNodeIndex(toFloor, toD);

	// Si esas posiciones no tienen un portal, entonces hago la conexion, sino hay un error con el input
	// Los conecto a traves de un intermediario, asi cumple los 2 metros de costo para viajes por portales
	connect(from, portalIndex);
	connect(portalIndex, to);

	// Incremento el indice para apuntar al siguiente vertices intermediario
	portalIndex++;
}

void ShortestPath::connect(int nodef, int nodet) {
	// Si no estan conectados, los conecto, sino aviso que el pedido es inesperado
	adjacency[nodef].push_back(nodet);
	adjacency[nodet].push_back(nodef);
}

// Mapea la posicion especifica a un vertice del grafo
inline int ShortestPath::getNodeIndex(int floor, int pos) {
	return (floor * this->length) + pos;
}

int ShortestPath::solve() {
    Timer timer("Excercise 2 Timer");
	//Cola
	std::queue<int> Q;
	// Distancias desde el vertice inicial
	std::vector<int> distance(this->adjacency.size(), -1);
	std::vector<int> parent(this->adjacency.size(), -1);
	// Inicializo el vertice inicial y lo introduzco lentamente en la cola
	distance[0] = 0;
	Q.push(0);

	while (!Q.empty()) {
		// Desencolo
		auto now = Q.front();
		Q.pop();
		// Itero por los vecinos del vertice actual (a lo sumo 3)
		for (auto neighbor : this->adjacency[now]) {
			// Si no lo habia alcanzado hasta ahora, actualizo su distancia y lo introduzco en la cola
			if (distance[neighbor] == -1) {
				distance[neighbor] = distance[now] + 1;
				parent[neighbor] = now;
				Q.push(neighbor);
			}

			if (neighbor == this->goal) {
				return distance[this->goal];
			}
		}
	}

	// Devuelvo la distancia hasta el objetivo, si es -1 es que no se puede alcanzar desde el vertice inicial
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