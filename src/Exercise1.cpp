#include <fstream>
#include <iostream>
#include <stdexcept>
#include "Statistics.h"
#include "Exercise1.h"

Maximize::Maximize(int iFloors)
        : floors(iFloors+1) {
    Timer timer("Excercise 1 Generate Matrix Timer");

    for (auto i = 0; i < floors; ++i) {
        adjacency.push_back(std::vector<bool>(floors-i, false));
    }
}

int Maximize::solve() {
    Timer timer("Excercise 1 Timer");
    std::vector<int> best(floors);
    std::vector<bool> reachable(floors, false);
    reachable[0] = true;

    for (auto floor = 0; floor < floors - 1; ++floor) {
        if (!reachable[floor]) {
            continue;
        }

        for (auto floor2 = floor + 1; floor2 < floors; ++floor2) {
            /* Si teniamos forma de conectar el piso floor con el piso floor2,
             * actualizamos el floor2 con lo que sea maximo.
             */
            if (adjacency[floor][floor2-floor]) {
                best[floor2] = std::max(best[floor2], best[floor] + 1);
                reachable[floor2] = true;
            }
        }
    }

    return best[floors - 1];
}

void Maximize::addPortal(int from, int to) {
    if (from < 0 || from > floors || to <= from || to > floors) {
        throw std::out_of_range("Portal coordinates out of range");
    }

    adjacency[from][to-from] = true;
}

/***********************************************************************************************************************
 *                                              Entrada y Salida
 **********************************************************************************************************************/

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
    std::ofstream handle(output.c_str(), std::ofstream::out | std::ofstream::trunc);

    for (auto &instance : instances) {
        for (auto i = 0; i < runs - 1; ++i) {
            instance.solve();
        }

        handle << instance.solve() << std::endl;
    }

    handle.close();
}