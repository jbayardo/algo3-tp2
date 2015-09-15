def gen_matrix(n, portal_list):
    matrix = []
    for x in xrange(n):
        matrix.append([False]*(n+1)) #O(N**2)

    for x, y in portal_list: #O(P)
        matrix[x][y] = True

    return matrix

def maximize_portals_matrix(n, portal_list):
    m = n+1
    matrix = gen_matrix(n, portal_list) # O(N**2)
    max_portals = [0]*m

    for floor in xrange(n): #O(N)
        for portal in xrange(floor + 1, m): #O(N-floor-1)
            portals_from = matrix[floor][portal] * (max_portals[floor] + 1) #O(1)
            max_portals[portal] = max(max_portals[portal], portals_from) #O(1)

    return max_portals[n] #O(1)

    """
    Esto es equivalente a ∑ i, i = N-1 to 1 ≈ N**2
    """


def gen_table(portal_list):
    table = {}
    for x, y in portal_list:
        table.setdefault(x, set()).add(y)
    return table


def maximize_portals_dict(n, portal_list):
    table = gen_table(portal_list)
    max_portals = [0]*(n+1)

    for floor in table:
        for portal in table[floor]:
            portals_from = max_portals[floor] + 1
            max_portals[portal] = max(max_portals[portal], portals_from)

    return max_portals[n]