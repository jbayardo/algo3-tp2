import os
import sys

EX_DIR = "experiments/"
BEST = "best"
WORST = "worst"
EX_FILE_TEMPLATE = "test_%d_complejidad_%s.in"

####################################
############# Exercise 1 ############
####################################


def best_case_1(top_floor):
    return str(top_floor) + "\n" + "0 " + str(top_floor)


def worst_case_1(top_floor):
    data = [str(n) + " " + str(x)
            for n in xrange(top_floor + 1)
            for x in xrange(n + 1, top_floor + 1)]
    return str(top_floor) + "\n" + "; ".join(data)


def generate_ex1(max_cases):
    best_file = EX_DIR + EX_FILE_TEMPLATE % (1, BEST)
    worst_file = EX_DIR + EX_FILE_TEMPLATE % (1, WORST)

    best_output = []
    worst_output = []

    for x in xrange(1, max_cases):
        best_output.append(best_case_1(x))
        worst_output.append(worst_case_1(x))

    write_ex_file(best_file, "\n".join(best_output))
    write_ex_file(worst_file, "\n".join(worst_output))


####################################
############# Exercise 2 ###########
####################################

def best_case_2(top):
    pass


def worst_case_2(top):
    pass

####################################
############# Exercise 3 ###########
####################################


def best_case_3(top):
    pass


def worst_case_3(top):
    pass

####################################
############# General ##############
####################################


def write_ex_file(path, data):
    with open(path, "w") as handle:
        handle.write(data)


if __name__ == '__main__':
    # if len(sys.argv) == 1:
    #     print "Numero Problema a generar"
    if not os.path.exists(EX_DIR):
        os.makedirs(EX_DIR)
    generate_ex1(100)
