#include <stdio.h>
#include <stdlib.h>
#include "../dbg.h"
#include "stack.h"

void render_menu(void)
{
    printf("=======================================================\n");
    printf("=== 1. Push onto stack\n");
    printf("=== 2. Pop off the stack\n");
    printf("=== 3. Peek off the stack\n");
    printf("=== 4. Check stack usage\n");
    printf("=== 5. Print the preffered stack size\n");

    printf("=== 9. Redraw the menu\n");
    printf("=== 0. Quit the program\n");
    printf("=======================================================\n");
}

int main(void)
{
    unsigned short preffered_stack_size;
    unsigned short input = 10000;
    unsigned int value;

    printf("========== STATIC ARRAY STACK IMPLEMENTATION ==========\n");
    printf("=== Input your prefered stack size (< %d): ", MAX_STACK);
    scanf("%d", &preffered_stack_size);

    stack_t *stack = stack_create(preffered_stack_size);

    render_menu();

    while(input != 0)
    {
        printf("=== Choose an option: ");

        scanf("%d", &input);

        switch(input) {
            case 1:
                printf("=== Value to be pushed: ");
                scanf("%d", &value);
                push(stack, value);
                break;
            case 2:
                printf("=== Value: %d\n", pop(stack));
                break;
            case 3:
                printf("=== Value %d\n", peek(stack));
                break;
            case 4:
                printf("=== Stack usage: %d\n", memused(stack));
                break;
            case 5:
                printf("=== Stack size: %d\n", stack_size(stack));
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

    free(stack);

    return 0;
}