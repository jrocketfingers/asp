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

    node->parent = 0;
    node->next_index = 0;

    return node;
}


int
is_valid(int x, int y, int m, int n) {
    return x >= 0 && y >= 0 && x < m && y < n;
}


int
main(void) {
    int dx[] = {1, -1, 2, -2, 1, -1, 2, -2};
    int dy[] = {2, 2, -1, -1, -2, -2, 1, 1};
    int **table;

    int m, n, x, y, i;

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

    node_t *root, *next;
    root = mk_node(x, y, NULL);

    next = root;

    while(1) {
        table[next->x][next->y];

        if(next->next_index < 8) {
            next = next->options[next->next_index];
        } else {
            next = next->parent;
        }
    }
}
