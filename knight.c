#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t {
    int x;
    int y;

    int next_index;
    struct node_t *options[8];
    struct node_t *parent;
} node_t;

node_t*
mk_node(int x, int y, node_t *parent) {
    node_t *node = malloc(sizeof(node_t));
    node->x = x;
    node->y = y;

    node->parent = parent;
    node->next_index = 0;

    return node;
}


int
is_valid(int x, int y, int m, int n) {
    return x >= 0 && y >= 0 && x < m && y < n;
}

void
print_board(int **table, int m, int n) {
    int i, j;
    for(i = 0; i < m; i++) {
        for(j = 0; j < n; j++) {
            printf("%3d ", table[i][j]);
        }
        printf("\n");
    }
}


void
deallocate_tree(node_t *root) {
    node_t *next, *old = NULL;

    next = root;

    while(next->options[next->next_index - 1] != NULL)
        next = next->options[next->next_index - 1];

    while(old != root) {
        old = next->parent;
        free(next);
        next = old;
    }

    free(old);
}


int
main(void) {
    int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
    int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};
    int **table;

    int m, n, x, y, nx, ny, i;

    node_t *root, *next, *new_option, *old;



    scanf("%d%d", &m, &n);

    if(m == 1) {
        printf("1\n");
        exit(0);
    }

    scanf("%d%d", &x, &y);
    if(!is_valid(x, y, m, n)) {
        printf("Invalid x or y. Outside the board! Exiting.");
        exit(1);
    }

    table = malloc(m * sizeof(int *));
    for(i = 0; i < m; i++)
        table[i] = calloc(n, sizeof(int));

    int step = 0;
    root = mk_node(x, y, NULL);

    next = root;

    while(1) {
        step++;

        table[next->x][next->y] = step;

        while(next->next_index < 8) {
            nx = next->x + dx[next->next_index];
            ny = next->y + dy[next->next_index];
            if(is_valid(nx, ny, m, n) && table[nx][ny] == 0) {      // if the choice is valid and we've not yet been there
                new_option = mk_node(nx, ny, next);                 // construct the new potential node;
                next->options[next->next_index] = new_option;       // make note of it as the next in that direction
                next->next_index++;                                 // move up the next_index
                next = new_option;                                  // head over to the new choice
                break;
            }
            else {                                                  // if it ain't valid,
                next->options[next->next_index] = NULL;             // make sure you mark it
                next->next_index++;                                 // and keep going
            }
        }

        if(step >= m * n) {                     // if we've stepped through
            print_board(table, m, n);           // print out the solution
            printf("\nSolved.\n");
            break;                              // and leave
        }

        if(next->next_index >= 8) {             // if it did run out of options
            table[next->x][next->y] = 0;        // delete the current step

            if(next == root) {
                print_board(table, m, n);
                printf("Unsolvable!");
                break;
            }

            old = next;                         // preserve it for actual deletion
            next = next->parent;                // go back to the parent

            free(old);                          // free the stub child
            step -= 2;                          // go back "two" steps (considering
                                                // that the first thing the loop
                                                // does is increment the step
                                                // counter.
        }
    }

    // deallocation
    for(i = 0; i < m; i++)
        free(table[i]);

    free(table);

    deallocate_tree(root);
}
