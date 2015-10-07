#include <fstream>
#include <stdexcept>
#include <queue>
#include <iostream>
#include "Statistics.h"
#include "Exercise3.h"

void WeightedGraph::connect(int from, int to, int weight) {
    adjacency.push_back(Edge(from, to, weight));
    sum += weight;
    ++edges;
}

std::size_t inline WeightedGraph::getEdgeSize() const {
    return edges;
}

int inline WeightedGraph::getEdgeSum() const {
    return sum;
}

WeightedGraph WeightedGraph::kruskal() {
    Timer timer("Excercise 3 Timer");
    WeightedGraph output(vertices);
    DisjointSet set(vertices);
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> edgeQ(adjacency.begin(), adjacency.end());

    while (output.getEdgeSize() < vertices - 1) {
        Edge current = edgeQ.top();
        edgeQ.pop();

        int setFrom = set.find(current.from);
        int setTo = set.find(current.to);

        if (setFrom != setTo) {
            set.merge(setFrom, setTo);
            output.connect(current.from, current.to, current.weight);
        }
    }

    return output;
}

/***********************************************************************************************************************
 *                                              Entrada y Salida
 **********************************************************************************************************************/

void Exercise3::read(std::string input) {
    std::ifstream handle;
    handle.open(input, std::ifstream::in);

    if (!handle.is_open()) {
        throw std::runtime_error("Fallo al abrir el archivo de tests para el ejercicio 1");
    }

    std::string line;

    // Mientras que podamos leer un piso
    while (std::getline(handle, line)) {
        if (!line.empty()) {
			std::list<std::string> parser = split(line, ';');

            int maxFloor = 0;

            // Tenemos una linea no vacia. Splitteamos por ; y procesamos individualmente
            // Obtenemos la cantidad de pisos
            for (auto &portal : parser) {
                int from, to, weight;
                std::stringstream endpoints(portal);
                endpoints >> from >> to >> weight;
                maxFloor = std::max(std::max(maxFloor, from), to);
            }

			WeightedGraph graph(maxFloor + 1);

            // Armamos las conexiones del grafo
			for (auto &portal : parser) {
                int from, to, weight;
                std::stringstream endpoints(portal);
                endpoints >> from >> to >> weight;

                // Agregamos los pesos del grafo, pero negados, este truco nos va a permitir hacer que Kruskal nos de
                // el árbol generador máximo
                graph.connect(from, to, -weight);
            }

            // Agregar instancia
            this->instances.push_back(graph);
        }
    }

    if (handle.fail() && !handle.eof()) {
        handle.close();
        throw std::runtime_error("Fallo al leer el archivo de tests para el ejercicio 3");
    }

    handle.close();
}

void Exercise3::solve(int runs, std::string output) {
    std::ofstream handle(output.c_str(), std::ofstream::out | std::ofstream::trunc);
	auto j = 0;

    for (auto &instance : instances) {
        for (auto i = 0; i < runs - 1; ++i) {
			std::cout << "Now running: " << j << " / " << i << "\r";
            instance.kruskal();
        }

        // Como insertamos los pesos negados, tenemos que negar la suma para poder tener el verdadero valor
        int inSum = -instance.getEdgeSum();

        // Por otro lado, al calcular Kruskal con los pesos negados, invertimos el orden efectivo de la toma de
        // vertices, es decir, insertamos primero los vertices más negativos (que serían los más grandes en el grafo
        // negado). Por lo tanto, simplemente tenemos que tomar el inverso aditivo de la suma para tener la suma del
        // árbol generador máximo. Negar los pesos del mismo nos daría el verdadero árbol.
        int outSum = -instance.kruskal().getEdgeSum();

        handle << inSum - outSum << std::endl;
		++j;
    }

    handle.close();
}
