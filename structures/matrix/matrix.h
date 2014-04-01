#ifndef __H_MATRIX__
#define __H_MATRIX__

#include "../dbg.h"

#define MAX_MATRIX_N 100
#define MAX_VECTOR 5050

typedef struct matrix_t matrix_t;

typedef int (*get_fn)(matrix_t *matrix, int row, int column);
typedef void (*set_fn)(matrix_t *matrix, int row, int column, int value);

struct matrix_t {
    int n;
    int default_value;
    int vector[MAX_VECTOR];
    get_fn get;
    set_fn set;
};

matrix_t *make_upper_triangular(int size, int default_values);
void print_matrix(matrix_t *matrix);
void upper_triangular_set_at(matrix_t *matrix, int row, int column, int value);
int upper_triangular_get_at(matrix_t *matrix, int row, int column);
int upper_triangular_count_non_default_values(matrix_t *matrix);

#endif //__H_MATRIX__
