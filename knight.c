#include <stdio.h>
#include <stdlib.h>

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


int
main(void) {
    int dx[] = {1, -1, 2, -2, 1, -1, 2, -2};
    int dy[] = {2, 2, -1, -1, -2, -2, 1, 1};
    int **table;

    int m, n, x, y, nx, ny, i;

    scanf("%d%d", &m, &n);

    if(m == 1) {
        printf("1\n");
        exit(0);
    }
    else if(m < 4 || n < 4) {
        printf("Unsolvable, make m and n > 4. Exiting.");
        exit(1);
    }

    scanf("%d%d", &x, &y);
    if(!is_valid(x, y, m, n)) {
        printf("Invalid x or y. Outside the board! Exiting.");
        exit(1);
    }

    table = malloc(m * sizeof(int *));
    for(i = 0; i < m; i++) table[i] = calloc(n, sizeof(int));

    int step = 0;

    node_t *root, *next, *new_option, *old;
    root = mk_node(x, y, NULL);

    next = root;

    while(1) {
        step++;

        table[next->x][next->y] = step;

        print_board(table, m, n);
        printf("\n");

        while(next->next_index < 8) {
            nx = next->x + dx[next->next_index];
            ny = next->y + dy[next->next_index];
            if(is_valid(nx, ny, m, n) && table[nx][ny] == 0) {
                new_option = mk_node(nx, ny, next);
                next->options[next->next_index] = new_option;
                next->next_index++;
                next = new_option;
                break;
            }
            else {
                next->options[next->next_index] = NULL;
                next->next_index++;
            }
        }

        if(next->next_index >= 8) {
            table[next->x][next->y] = 0;
            old = next;
            next = next->parent;

            free(old);
            step -= 2;
        }

        if(step >= m * n) {
            print_board(table, m, n);
            break;
        }
    }
}
