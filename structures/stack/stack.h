#ifndef __H_ST_LIST_H__
#define __H_ST_LIST_H__

#include "../dbg.h"

#define MAX_STACK 100

typedef unsigned short int USHORT;
typedef unsigned int UINT;

typedef struct stack_t stack_t;
typedef struct node_t node_t;

#ifndef STACK_LIST
struct stack_t {
    USHORT max_len;
    USHORT cursor;
    UINT data[MAX_STACK];
};
#endif // !STACK_LIST

#ifdef STACK_LIST
struct node_t {
    unsigned int value;
    struct node_t *next;
};

struct stack_t {
    USHORT max_len;
    USHORT cur_len;
    node_t *head;
    //node_t *cursor;
};
#endif // STACK_LIST

stack_t *stack_create(USHORT max_len);
void push(stack_t *stack, UINT value);
UINT pop(stack_t *stack);
UINT peek(stack_t *stack);
USHORT memused(stack_t *stack);
USHORT stack_size(stack_t *stack);
#endif
