#include <stdio.h>
#include <stdlib.h>

#define STACK_LIST

#include "stack.h"

stack_t *stack_create(USHORT max_len)
{
    if(max_len <= MAX_STACK)
    {
        stack_t *stack = malloc(sizeof(stack_t));
        stack->max_len = max_len;
        stack->cur_len = 0;

        node_t *head = malloc(sizeof(node_t));
        stack->head = head;

        return stack;
    }
    else
        log_err("Maximum stack length cannot exceed %d", MAX_STACK);
}

// push, pop, peek, memused, stack_size

// 100 - 1 = 99 [100th]
void push(stack_t *stack, UINT value)
{
    if(stack->cur_len < (stack->max_len)) {
        node_t *new_head = malloc(sizeof(node_t));
        new_head->next = stack->head;

        stack->head->value = value;
        stack->cur_len++;

        stack->head = new_head;
    }
    else
        log_err("Stack overflow! Nothing is pushed onto the stack!");
}

UINT pop(stack_t *stack)
{
    if(stack->cur_len > 0) {
        UINT value = stack->head->next->value;
        node_t *deletion_node;

        deletion_node = stack->head;
        stack->head = stack->head->next;
        free(deletion_node);

        stack->cur_len--;

        return value;
    }
    else
    {
        log_err("Stack underflow! Nothing poped off the stack!");
        return 0;                           // return the default value (0)
    }
}

UINT peek(stack_t *stack)
{
    if(stack->cur_len > 0)
        return stack->head->next->value;
    else
    {
        log_err("Stack empty!");
        return 0;
    }
}

USHORT memused(stack_t *stack)
{
    return stack->cur_len;
}

USHORT stack_size(stack_t *stack)
{
    return stack->max_len;
}