#include <stdio.h>
#include "./stack.h"

int main() {
    Stack *stack = create_stack();
    int value;
    while (true) {
        printf("1. Add Node\n2. Delete Node\n3. Print Nodes\n4. Sort\n5. Exit\n~: ");
        scanf("%d", &value);
        if (value == 1) {
            printf("\n~. 0=to_quit:\n");
            scanf("%d", &value);
            while (value != 0) {
                stack_push(stack, value);
                printf("\n~. 0=to_quit:\n");
                scanf("%d", &value);
            }
        }
        if (value == 2) {
            printf("\n1 - delete headnode/ 0 - quit: \n");
            scanf("%d", &value);
            while (value != 0) {
                if (stack_is_empty(stack)) {
                    printf("\nStack is empty\n");
                    break;
                }
                printf("\nPoped %d\n", stack_pop(stack));
                printf("\nE1 - delete head / 0 - quit:\n");
                scanf("%d", &value);
            }
        }
        if (value == 3) {
            printStack(stack);
        }
        if (value == 4) {
            stack = merge_sort(stack);
            printf("\nIt'S sorted\n");
        }
        if (value == 5) {
            stack_destroy(stack); 
            break;
        }
    }
    return 0;
}
