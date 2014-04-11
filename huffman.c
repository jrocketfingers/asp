#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
    struct node_t *child[2];
    struct node_t *next;
    int freq;
    char character;
} node_t;


node_t*
insert_pq(node_t *head, node_t *node) {
    node_t *q = NULL;
    node_t *p = head;
    while(p != NULL && p->freq <= node->freq) {
        q = p;
        p = p->next;
    }

    if(q == NULL) {             // Ako je prvi u listi
        node->next = head;
        return node;
    } else {                    // Ako je usred liste
        node->next = q->next;
        q->next = node;

        return head;
    }
}

node_t*
pq_min_delete(node_t **head) {
    node_t *min = *head;

    *head = (*head)->next;
    return min;
}


node_t*
mk_node(char character, int freq) {
    node_t *node;
    node = malloc(sizeof(node_t));

    node->character = character;
    node->freq = freq;

    return node;
}


int
main(void)
{
    node_t *head = NULL, *left, *right, *root;
    char input;
    unsigned int frequencies[26] = {0}, i, char_count = 0, weight;

    input = '\n';

    // Input sequence
    while(input != '\n') {
        input = getchar();

        frequencies[input - 'A']++;
        char_count++;
    }

    // Frequency data
    for(i = 0; i < 26; i++)
        head = insert_pq(head, mk_node(i + 'A', frequencies[i]));

    // Huffman
    for(i = 0; i < char_count - 1; i++) {
        root = mk_node('\0', 0);
        left = pq_min_delete(&head);
        right = pq_min_delete(&head);
        root->freq = left->freq + right->freq;

        root->child[0] = left;
        root->child[1] = right;

        insert_pq(head, root);
    }

    return 0;
}
