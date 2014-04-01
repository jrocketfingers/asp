import random

def mmake(n):
    return [[0 for _ in range(0, n)] for _ in range(0, n)]


def mfill(matrix):
    n = len(matrix[0])
    for i in range(0, n):
        for j in range(i, n):
            matrix[i][j] = random.randrange(0, 100)


def mprint(matrix):
    for row in matrix:
        for column in row:
            print "%3d" % column,
        print


def linearize(matrix):
    n = len(matrix[0])
    return [matrix[i][j] for i in range(0, n) for j in range(i, n)]


def laccess(linmat, i, j, n):
    v = n*(i - 1) - (i-1)*(i-2)/2 + j - i
    return linmat[v]


def checkaccess(linmat, matrix):
    n = len(matrix[0])
    for i in range(0, n):
        for j in range(i, n):
            if matrix[i][j] != laccess(linmat, i + 1, j + 1, n):
                return False
    else:
        return True