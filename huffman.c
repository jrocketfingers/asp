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

    if(*head != NULL)
        *head = (*head)->next;

    return min;
}


node_t*
push(node_t *head, node_t *node) {
    node->next = head;

    return node;
}

node_t*
pop(node_t **head) {
    node_t *node;

    if(head != NULL) {
        node = *head;

        *head = (*head)->next;

        return node;
    }

    return NULL;
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
    node_t *head = NULL, *list_head = NULL, *left, *right, *root;
    char input, code[26];       // code length is max-depth

    unsigned int frequencies[26] = {0}, i, char_count = 0, weight;

    // Input sequence
    while(input != '\n') {
        input = getchar();

        frequencies[input - 'A']++;
    }

    // Frequency data
    for(i = 0; i < 26; i++) {
        if(frequencies[i] != 0) {
            head = insert_pq(head, mk_node(i + 'A', frequencies[i]));
            char_count++;
        }
    }

    // Huffman
    for(i = 0; i < char_count - 1; i++) {
        root = mk_node('\0', 0);
        left = pq_min_delete(&head);
        right = pq_min_delete(&head);

        left->next = right;
        right->next = list_head;
        list_head = left;

        root->freq = left->freq + right->freq;

        root->child[0] = left;
        root->child[1] = right;

        insert_pq(head, root);
    }

    while(list_head != NULL) {
        if(list_head->character >= 'A' && list_head->character <= 'Z')
            printf("freq: %d; character: %c\n", list_head->freq, list_head->character);
        list_head = list_head->next;
    }

    return 0;
}
