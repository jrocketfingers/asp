#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "matrix.h"

/* Returns an n x n upper triangular matrix structure */
matrix_t *make_upper_triangular(int size, int default_value)
{
    matrix_t *matrix = malloc(sizeof(matrix_t));
    matrix->n = size;
    matrix->default_value = default_value;
    matrix->get = upper_triangular_get_at;
    matrix->set = upper_triangular_set_at;

    int it, length;
    length = upper_triangular_count_non_default_values(matrix);
    for(it = 0; it < length; it++)
        matrix->vector[it] = default_value;

    return matrix;
}


void print_matrix(matrix_t *matrix)
{
    int row, column;
    for(row = 1; row <= matrix->n; row++)
    {
        for(column = 1; column <= matrix->n; column++)
            printf("%d ", matrix->get(matrix, row, column));
        printf("\n");
    }
}

void upper_triangular_set_at(matrix_t *matrix, int row, int column, int value) {
    if(column > matrix->n || row > matrix->n)
    {
        log_err("Index outside of the matrix! r:%d;c:%d n:%d", row, column, matrix->n);
    }
    else if(column >= row)
    {
        int addr = matrix->n*(row - 1) - (row - 2)*(row - 1)/2 + column - row;
        matrix->vector[addr] = value;
    }
    else
        log_err("Row coordinate greater than the column! %d > %d", row, column);
}

int upper_triangular_get_at(matrix_t *matrix, int row, int column) {
    if(column > matrix->n || row > matrix->n)
    {
        log_err("Index outside of the matrix! r:%d;c:%d n:%d", row, column, matrix->n);
        return 0;
    }
    else if(column >= row)
    {
        int addr = matrix->n*(row - 1) - (row - 2)*(row - 1)/2 + column - row;
        return matrix->vector[addr];
    }
    else
    {
        return matrix->default_value;
    }
}

int upper_triangular_count_non_default_values(matrix_t *matrix)
{
    int n = matrix->n;
    return n*n - (n - 1)*n/2;
}
