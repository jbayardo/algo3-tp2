#include <fstream>
#include <iostream>
#include <stdexcept>
#include "Exercise2.h"

/** Entrada y salida
 */
std::list<std::string> split(std::string string, char delim) {
    std::list<std::string> output;
    std::string current;
    std::stringstream stream(string);

    while (std::getline(stream, current, delim)) {
        output.push_back(current);
    }

    return output;
}

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
        int portals;

        handle >> portals;

        std::string line;

        // Leemos una linea no vacia
        while (line.length() == 0 && !handle.fail()) {
            std::getline(handle, line);
        }

        // Si no hubo errores, tenemos una linea no vacia
        if (!handle.fail()) {
            // Splitteamos por ; y procesamos individualmente
            for (auto &portal : split(line, ';')) {
                int from, dFrom, to, dTo;
                std::stringstream endpoints(portal);
                endpoints >> from >> dFrom >> to >> dTo;
                // TODO: Agregar portal!
            }
        } else {
            // Hubo un error, abortar!
            handle.close();
            throw std::runtime_error("Fallo al leer el archivo de tests para el ejercicio 2");
        }

        ++test;
    }

    handle.close();
}

/* Resuelve runs veces por caso de test!
 */
void Exercise2::solve(int runs, std::string output) {

}