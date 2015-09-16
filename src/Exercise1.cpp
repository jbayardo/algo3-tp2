#include <fstream>
#include <iostream>
#include <stdexcept>
#include "Exercise1.h"

void Exercise1::read(std::string input) {
    int test = 0;
    std::ifstream handle;
    handle.open(input, std::ifstream::in);

    if (!handle.is_open()) {
        throw std::runtime_error("Fallo al abrir el archivo de tests para el ejercicio 1");
    }

    // Mientras que podamos leer un piso
    while (handle >> this->floors) {
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
                // TODO: Agregar portal!
            }
        } else {
            // Hubo un error, abortar!
            handle.close();
            throw std::runtime_error("Fallo al leer el archivo de tests para el ejercicio 1");
        }

        ++test;
    }

    handle.close();
}

/* Resuelve runs veces por caso de test!
 */
void Exercise1::solve(int runs) const {

}

void Exercise1::write(std::string output) {

}

Exercise1::Exercise1() {

}