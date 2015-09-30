#include <fstream>
#include <stdexcept>
#include <queue>
#include "Statistics.h"
#include "Exercise3.h"

void WeightedGraph::connect(int from, int to, int weight) {
    vertices[from].push_back(Edge(from, to, weight));
    vertices[to].push_back(Edge(to, from, weight));

    sum += weight;
}

bool WeightedGraph::exists(int node) const {
    return vertices[node].size() != 0;
}

int WeightedGraph::getSum() const {
    return sum;
}

int WeightedGraph::prim() {
    Timer timer("Excercise 3 Timer");
    WeightedGraph output(this->vertices.size());
    std::priority_queue<Edge> queue;

    // Pongo todos los vertices que conectan la fuente con otro
    for (auto &edge : vertices[0]) {
        queue.push(edge);
    }

    // Hasta que no nos hayamos quedado sin aristas
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

    return getSum() - output.getSum();
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

                graph.connect(from, to, weight);
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

    for (auto &instance : instances) {
        for (auto i = 0; i < runs - 1; ++i) {
            instance.prim();
        }

        handle << instance.prim() << std::endl;
    }

    handle.close();
}