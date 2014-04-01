#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../dbg.h"
#include "matrix.h"

void render_menu(void)
{
    printf("=======================================================\n");
    printf("=== 1. Print the matrix\n");
    printf("=== 2. Set an element\n");
    printf("=== 3. Get an element\n");
    printf("=== 4. Number of non defaults\n");

    printf("=== 9. Redraw the menu\n");
    printf("=== 0. Quit the program\n");
    printf("=======================================================\n");
}

int main(void)
{
    unsigned short matrix_n;
    unsigned short input = 10000;
    int default_value, row, column, value;

    printf("========== UPPER TRIANGULAR MATRIX IMPLEMENTATION ==========\n");
    printf("=== Input your matrix size (< %d): ", MAX_MATRIX_N);
    scanf("%d", &matrix_n);
    printf("=== Input your default value: ");
    scanf("%d", &default_value);

    matrix_t *matrix = make_upper_triangular(matrix_n, default_value);

    render_menu();

    while(input != 0)
    {
        printf("=== Choose an option: ");

        scanf("%d", &input);

        switch(input) {
            case 1:
                print_matrix(matrix);
                break;
            case 2:
                printf("=== Input the <row> <column> <value>: ");
                scanf("%d %d %d", &row, &column, &value);
                matrix->set(matrix, row, column, value);
                break;
            case 3:
                printf("=== Input the <row> <column>: ");
                scanf("%d %d", &row, &column);
                printf("=== Value is: %d\n", matrix->get(matrix, row, column));
                break;
            case 4:
                printf("=== Number of non-default elements is: %d\n", upper_triangular_count_non_default_values(matrix));
                break;
            case 9:
                render_menu();
                break;
            case 0:
                break;
            default:
                printf("Wrong choice!\n");
                break;
        }
    }

    free(matrix);

    return 0;
}