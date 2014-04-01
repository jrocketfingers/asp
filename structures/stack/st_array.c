#include <stdio.h>
#include <stdlib.h>

#define STACK_ARRAY

#include "stack.h"

stack_t *stack_create(USHORT max_len)
{
    if(max_len <= MAX_STACK)
    {
        stack_t *stack = malloc(sizeof(stack_t));
        stack->max_len = max_len;

        return stack;
    }
    else
        log_err("Maximum stack length cannot exceed %d", MAX_STACK);
}

// push, pop, peek, memused, stack_size

// 100 - 1 = 99 [100th]
void push(stack_t *stack, UINT value)
{
    if(stack->cursor < (stack->max_len)) {
        stack->data[stack->cursor] = value;
        stack->cursor++;
    }
    else
        log_err("Stack overflow! Nothing is pushed onto the stack!");
}

UINT pop(stack_t *stack)
{
    if(stack->cursor > 0) {
        stack->cursor--;
        return stack->data[stack->cursor];  // rely on the fact that we're
                                            // subtracting the pointer anyways.
    }
    else
    {
        log_err("Stack underflow! Nothing poped off the stack!");
        return 0;                           // return the default value (0)
    }
}

UINT peek(stack_t *stack)
{
    if(stack->cursor > 0)
        return stack->data[stack->cursor - 1];
    else
    {
        log_err("Stack empty!");
        return 0;
    }
}

USHORT memused(stack_t *stack)
{
    return stack->cursor;
}

USHORT stack_size(stack_t *stack)
{
    return stack->max_len;
}