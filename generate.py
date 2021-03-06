#!/usr/bin/python
import os
from collections import defaultdict
from random import randint, shuffle, random, randrange
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
        connect = "%d\n" % z
        data = set(["0 %d" % z])
        for x in xrange(0, z):
            for _ in xrange((randint(1, z))):
                if random() < 0.25:
                    data.add("%d %d" % (x, randint(x+1, z)))
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
    cases = defaultdict(list)
    for l in xrange(2, max(top + 1, 3)):
        for floor in xrange(l):
            for here in xrange(l+1):
                for there in xrange(l + 1 - 1 * (l == (floor + 1))):
                    edge = ""
                    if floor == 0 and here == 0 and there == l:
                        edge = "%d %d %d %d" % (floor, here, l, l)
                    else:
                        edge = "%d %d %d %d" % (floor, here, floor + 1, there)
                    cases[(l, l)].append(edge)

    return "\n".join(["%d %d\n" % k + "; ".join(cases[k])
                      for k in sorted(cases.keys())])


def random_case_2(top):
    cases = defaultdict(set)
    for l in xrange(2, max(top + 1, 3)):
        for floor in xrange(l):
            here = randint(0, l)
            there = randint(0, l)
            next = floor + 1
            edge = "%d %d %d %d" % (floor, here, next, there)
            cases[(l, l)].add(edge)
        for _ in xrange(l**3):
            here = randint(0, l)
            there = randint(0, l)
            origin = randint(0, l)
            dest = randint(0, l)

            edge = "%d %d %d %d" % (origin, here, dest, there)

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


def _tree_edges(n):
    # generador de arbol binario balanceado
    nodes = iter(range(n))
    parents = [next(nodes)]
    while parents:
        source = parents.pop(0)
        for i in range(2):
            try:
                target = next(nodes)
                parents.append(target)
                yield source, target
            except StopIteration:
                break


def best_case_3(top):
    cases = []
    top = max(4, top + 1)
    for n in xrange(3, top + 1):
        m = (n * (n - 1)) / 2
        all_edges = list(combinations(xrange(n), 2))  # genero Kn
        shuffle(all_edges)  # randomizo aristas
        s_edges = set([(min(e), max(e)) for e in _tree_edges(n)])
        edges = {e: 2 for e in _tree_edges(n)}

        while len(edges) < m:
            e = all_edges.pop()
            k = (min(e), max(e))
            if k not in s_edges:
                edges[e] = 1
                s_edges.add(k)
        assert len(edges) == m
        cases.append("; ".join(["%d %d "%e + "%d"% edges[e]for e in edges]))
    return "\n".join(cases)


def random_case_3(top, max_weight=100):
    cases = []
    top = max(4, top + 1)
    for n in xrange(3, top + 1):
        m = (n * (n - 1)) / 2
        all_edges = list(combinations(xrange(n + 1), 2)) #genero Kn+1
        shuffle(all_edges) #randomizo aristas
        edges = ["%d %d %d" % (x, y, randint(1, max_weight))
                 for (x, y) in all_edges[:m + 1]]
        assert len(edges) - 1 == m
                           # Elijo m+1 aristas para asegurar que sea conexo
        cases.append("; ".join(edges))
    return "\n".join(cases)



def worst_case_3(top):
    cases = []
    top = max(4, top + 1)
    for n in xrange(3, top + 1):
        m = (n * (n - 1)) / 2
        edges = ["%d %d %d" % (x, y, (x == 0) * 1 + 3 * (x != 0))
                 for (x, y) in combinations(xrange(n), 2)]
        assert len(edges) == m
        cases.append("; ".join(edges))
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
    write_ex_file(random_file, "\n".join(random_output))
    write_ex_file(worst_file, "\n".join(worst_output))


def write_ex_file(path, data):
    with open(path, "w") as handle:
        handle.write(data)


if __name__ == '__main__':
    # if len(sys.argv) == 1:
    #     print "Numero Problema a generar"
    if not os.path.exists(EX_DIR):
        os.makedirs(EX_DIR)
    # generate_ex(1, 100)
    # generate_ex(2, 100)
    generate_ex(3, 100)
