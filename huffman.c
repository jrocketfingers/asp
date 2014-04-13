#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t {
    struct node_t *child[2];
    struct node_t *next;
    int freq;
    int level;
    char character;
    char code;
} node_t;


unsigned int stack_size = 0;
node_t *stack_head = NULL;


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
push(node_t *node) {
    node->next = stack_head;

    stack_head = node;

    stack_size++;

    return node;
}

node_t*
pop() {
    node_t *node;

    if(stack_head != NULL) {
        node = stack_head;

        stack_head = stack_head->next;

        stack_size--;

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
    node->level = 0;

    return node;
}


int
main(int argc, char **argv)
{
    node_t *head = NULL, *left, *right, *root, *next;
    char *input = NULL, input_char, code[26];       // code length is max-depth
    short int code_cursor = 0;

    unsigned int frequencies[26] = {0}, i, char_count = 0, input_length = 0;
    char code_table[26][26] = {{0}};

    FILE *output, *input_file;

    output = fopen("output", "w");

    input_file = fopen(argv[1], "r");

    input = malloc(20 * sizeof(char));

    input_char = fgetc(input_file);
    // Input sequence
    while(input_char != '\n') {
        if(input_length % 20 == 0)
            input = realloc(input, (input_length + 20) * sizeof(char));

        frequencies[input_char - 'A']++;

        input[input_length] = input_char;
        input_length++;

        input_char = fgetc(input_file);
    }

    input[input_length] = '\0';

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

        left->code = '0';
        right->code = '1';

        root->freq = left->freq + right->freq;

        root->child[0] = left;
        root->child[1] = right;

        head = insert_pq(head, root);
    }

    // INORDER calculation
    push(root);
    while(stack_size > 0) {
        next = pop();
        code_cursor = next->level;

        while(next != NULL) {
            if(next->code == '1' || next->code == '0') {
                code[code_cursor] = next->code;
                code_cursor++;
                code[code_cursor] = '\0';
            }

            if(next->character >= 'A' && next->character <= 'Z') {
                strcpy(code_table[next->character - 'A'], code);
                fprintf(output, "%c %s\n", next->character, code_table[next->character - 'A']);
            }


            if(next->child[1] != NULL)
            {
                next->child[1]->level = code_cursor;
                push(next->child[1]);
            }

            next = next->child[0];
        }
    }

    fprintf(output, "\n");
    for(i = 0; i < input_length; i++)
        fprintf(output, "%s", code_table[input[i] - 'A']);
    fprintf(output, "\n");

    return 0;
}
