#!/usr/bin/python
import os
from collections import defaultdict
from random import randint, shuffle
from itertools import combinations

EX_DIR = "experiments/"
BEST = "best"
WORST = "worst"
RANDOM = "random"
EX_FILE_TEMPLATE = "test_%d_complejidad_%s.in"

####################################
############# Exercise 1 ############
####################################


def best_case_1(top_floor):
    cases = []
    for z in xrange(1, top_floor + 1):
        cases.append("%d\n0 %d" % (z, z))
    return "\n".join(cases)


def random_case_1(top_floor):
    cases = []
    for z in xrange(3, top_floor + 1):
        # Me aseguro que haya un camino
        connect = "%d\n0 %d; " % (z, z)
        data = set()
        for x in xrange(1, z):
            while len(data) < z:
                a = randint(x, z)
                b = randint(x+1, z)
                while a >= b and "%d %d" % (a, b) not in data:
                    a = randint(x, z)
                    b = randint(x+1, z)
                data.add("%d %d" % (a, b))
        cases.append(connect + "; ".join(data))
    return "\n".join(cases)


def worst_case_1(top_floor):
    cases = []
    for z in xrange(1, top_floor+1):
        data = ["%d %d" % (n, x)
                for n in xrange(z + 1)
                for x in xrange(n + 1, z + 1)]
        cases.append("%d\n" % (z) + "; ".join(data))
    return "\n".join(cases)


####################################
############# Exercise 2 ###########
####################################

def best_case_2(top):
    return "\n".join(["%d %d\n0 0 %d %d" % (l, l, l, l)
                      for l in xrange(2, max(top + 1, 3))])


def random_case_2(top):
    cases = defaultdict(set)
    for l in xrange(2, max(top + 1, 3)):
        # me aseguro que sea conexo y haya solucion
        for floor in xrange(l):
            here = randint(0, l)
            there = randint(0, l)
            next = floor + 1
            edge = "%d %d %d %d" % (floor, here, next, there)
            cases[(l, l)].add(edge)
        # agrego aristas random
        for x in xrange(l):
            for _ in xrange(randint(x + 1, l)):
                here = randint(0, l)
                there = randint(0, l)
                next = randint(x+1, l)
                edge = "%d %d %d %d" % (x, here, next, there)
                cases[(l, l)].add(edge)

    return "\n".join(["%d %d\n" % k + "; ".join(cases[k])
                      for k in sorted(cases.keys())])

def worst_case_2(top):
    cases = defaultdict(list)
    for l in xrange(2, max(top + 1, 3)):
        for floor in xrange(l):
            for here in xrange(l):
                for there in xrange(l - 1 * (l == (floor + 1))):
                    edge = "%d %d %d %d" % (floor, here, floor + 1, there)
                    cases[(l, l)].append(edge)

    return "\n".join(["%d %d\n" % k + "; ".join(cases[k])
                      for k in sorted(cases.keys())])


####################################
############# Exercise 3 ###########
####################################


def best_case_3(top):
    cases = []
    for n in xrange(2, max(3, top + 1)):
        edges = "; ".join(["%d %d %d" % (i, i + 1, randint(1, 100))
                          for i in xrange(n + 1)])
        cases.append(edges)
    return "\n".join(cases)


def random_case_3(top, max_weight=100):
    cases = []
    for x in xrange(3, top + 1):
        m = 2 + ((x - 1)*(x - 2))/2
        all_edges = list(combinations(xrange(x + 1), 2))
        shuffle(all_edges)
        edges = "; ".join(["%d %d %d" % (a, b, randint(3, max_weight))
                           for (a, b) in all_edges[:m]])
        cases.append(edges)
    return "\n".join(cases)



def worst_case_3(top, max_weight=100):
    cases = []
    top = max(4, top + 1)
    for n in xrange(3, top + 1):
        edges = "; ".join(map(lambda (x, y):
                              "%d %d %d" % (x, y, (x == 0) * 1 + x * randint(3, max_weight)),
                              list(combinations(xrange(n + 1), 2))))
        cases.append(edges)
    return "\n".join(cases)


####################################
############# General ##############
####################################
best_case = {}
best_case[1] = best_case_1
best_case[2] = best_case_2
best_case[3] = best_case_3

worst_case = {}
worst_case[1] = worst_case_1
worst_case[2] = worst_case_2
worst_case[3] = worst_case_3

random_case = {}
random_case[1] = random_case_1
random_case[2] = random_case_2
random_case[3] = random_case_3


def generate_ex(ex, max_cases):
    best_file = EX_DIR + EX_FILE_TEMPLATE % (ex, BEST)
    random_file = EX_DIR + EX_FILE_TEMPLATE % (ex, RANDOM)
    worst_file = EX_DIR + EX_FILE_TEMPLATE % (ex, WORST)

    best_output = []
    random_output = []
    worst_output = []

    best_output.append(best_case[ex](max_cases))
    random_output.append(random_case[ex](max_cases))
    worst_output.append(worst_case[ex](max_cases))

    write_ex_file(best_file, "\n".join(best_output))
    write_ex_file(random_file, "\n".join(best_output))
    write_ex_file(worst_file, "\n".join(worst_output))


def write_ex_file(path, data):
    with open(path, "w") as handle:
        handle.write(data)


if __name__ == '__main__':
    # if len(sys.argv) == 1:
    #     print "Numero Problema a generar"
    if not os.path.exists(EX_DIR):
        os.makedirs(EX_DIR)
    #generate_ex(1, 100)
    generate_ex(2, 100)
    #generate_ex(3, 100)
