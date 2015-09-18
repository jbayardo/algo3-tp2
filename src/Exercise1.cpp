#include <fstream>
#include <iostream>
#include <stdexcept>
#include "Statistics.h"
#include "Exercise1.h"

Maximize::Maximize(int iFloors) : floors(iFloors) {
	adjacency = std::vector<std::vector<bool>>(floors, std::vector<bool>(floors + 1, false));

    // for (auto i = 0; i < floors; ++i) {
    //     adjacency[floors] = new bool[i + 1]; //MAL!
    // }
}

int Maximize::solve() {
    Timer timer("Excercise 1 Timer");
    std::vector<int> best(floors);

    for (auto floor = 0; floor < floors; ++floor) {
        for (auto portal = floor + 1; portal < floors+1; ++portal) {
            /* Si teniamos forma de conectar el piso floor con el piso portal,
             * actualizamos el portal con lo que sea maximo.
             */
            if (adjacency[floor][portal]) {
                best[portal] = std::max(best[portal], best[floor] + 1);
            }
        }
    }

    return best[floors - 1];
}

void Maximize::addPortal(int from, int to) {
    if (from < 0 || from > floors || to <= from || to > floors) {
        throw std::out_of_range("Portal coordinates out of range");
    }
    adjacency[from][to] = true;
}

Maximize::~Maximize() {
    // for (auto i = 0; i < floors; ++i) {
    //     delete adjacency[i];
    // }

    // delete adjacency;
}

/*
 * Entrada y salida!
 */
void Exercise1::read(std::string input) {
    std::ifstream handle;
    handle.open(input, std::ifstream::in);

    if (!handle.is_open()) {
        throw std::runtime_error("Fallo al abrir el archivo de tests para el ejercicio 1");
    }

    int floors;

    // Mientras que podamos leer un piso
    while (handle >> floors) {
        Maximize instance(floors);

        std::string line;

        // Leemos una linea no vacia
        while (line.length() == 0 && !handle.fail()) {
            std::getline(handle, line);
        }

        // Si no hubo errores, tenemos una linea no vacia
        if (!handle.fail()) {
            // Splitteamos por ; y procesamos individualmente
            for (auto &portal : split(line, ';')) {
                int from, to;
                std::stringstream endpoints(portal);
                endpoints >> from >> to;
                instance.addPortal(from, to);
            }

            // Agregar instancia
            instances.push_back(instance);
        } else {
            // Hubo un error, abortar!
            handle.close();
            throw std::runtime_error("Fallo al leer el archivo de tests para el ejercicio 1");
        }
    }

    handle.close();
}

/* Resuelve runs veces por caso de test!
 */
void Exercise1::solve(int runs, std::string output) {
    std::ofstream handle(output.c_str(), std::ofstream::out | std::ofstream::app);

    for (auto &instance : instances) {
        for (auto i = 0; i < runs - 1; ++i) {
            instance.solve();
        }

        handle << instance.solve() << std::endl;
    }

    handle.close();
}