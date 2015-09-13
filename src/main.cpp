#include <iostream>
#include "Statistics.h"
#include "Exercise.h"
#include "Exercise1.h"
#include "Exercise2.h"
#include "Exercise3.h"

/*
 * ./tp <ejercicio> <entrada> <salida> <corridas>
 */
int main(int argc, char *argv[]) {
    if (argc < 5) {
        std::cerr << "Formato de entrada: " << argv[0] << " <ejercicio> <entrada> <salida> <corridas>" << std::endl;
        return 1;
    }

    int exercise = std::atoi(argv[1]);
    std::string input = argv[2];
    std::string output = argv[3];
    int runs = std::atoi(argv[4]);

    if (runs <= 0) {
        std::cerr << "Parametro de corridas inválido, debe ser mayor a 0." << std::endl;
        return 1;
    }

    Exercise *instance;

    switch(exercise) {
        case 1:
            instance = new Exercise1();
            break;
        case 2:
            instance = new Exercise2();
            break;
        case 3:
            instance = new Exercise3();
            break;
        default:
            std::cerr << "Numero de ejercicio invalido, solo puede ser 1, 2 o 3." << std::endl;
            return 1;
    }

    instance->read(input);

    for (int i = 0; i < runs; ++i) {
        instance->solve();
    }

    instance->write(output);

    delete instance;

    std::string path = std::string(output);
    std::string basename = path.substr(0, path.find_last_of('.'));
    Statistics::getInstance().dump(basename + ".sts");

    return 0;
}