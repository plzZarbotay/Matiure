#include <stdio.h>
#include "./stack.h"

int main() {
    Stack *stack = create_stack();
    int input;
    while (true) {
        printf("1. Add Node\n2. Delete Node\n3. Print Nodes\n4. Sort\n5. Exit\n~: ");
        scanf("%d", &input);
        if (input == 1) {
            printf("Enter value to insert in stack or 0 to quit: ");
            scanf("%d", &input);
            while (input != 0) {
                stack_push(stack, input);
                printf("~. !=to_quit: ");
                scanf("%d", &input);
            }
        }
        if (input == 2) {
            printf("1 - delete headnode/ 0-quit: ");
            scanf("%d", &input);
            while (input != "!") {
                if (stack_is_empty(stack)) {
                    printf("Stack is empty\n");
                    break;
                }
                printf("Poped %d\n", stack_pop(stack));
                printf("Enter 1 to delete head node or 0 to quit: ");
                scanf("%d", &input);
            }
        }
        if (input == 3) {
            printStack(stack);
        }
        if (input == 4) {
            stack = merge_sort(stack);
            printf("It'S sorted\n");
        }
        if (input == 5) {
            stack_destroy(stack);
            break;
        }
    }
    // free(stack);
    stack = NULL;
    return 0;
}
