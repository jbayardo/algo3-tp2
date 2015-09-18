#include "Exercise3.h"
#include <fstream>
#include <stdexcept>

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
            WeightedGraph graph;

            // Tenemos una linea no vacia. Splitteamos por ; y procesamos individualmente
            for (auto &portal : split(line, ';')) {
                int from, to, weight;
                std::stringstream endpoints(portal);
                endpoints >> from >> to >> weight;

                graph.connect(from, to, weight);
            }

            // Agregar instancia
            this->instances.push_back(graph);
        }
    }

    if (handle.fail()) {
        handle.close();
        throw std::runtime_error("Fallo al leer el archivo de tests para el ejercicio 3");
    }

    handle.close();
}

void Exercise3::solve(int runs, std::string output) {
    std::ofstream handle(output.c_str(), std::ofstream::out | std::ofstream::app);

    for (auto &instance : instances) {
        for (auto i = 0; i < runs - 1; ++i) {
            instance.prim();
        }

        handle << instance.prim() << std::endl;
    }

    handle.close();
}