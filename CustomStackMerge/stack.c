#include "./stack.h"
#include "stdio.h"
#include "stdlib.h"

Stack* create_stack() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if (s == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }
    s->head = NULL;
    return s;
}

StackNode* insert_stack_node(StackNode* parent, int value) {
    StackNode* new_node = (StackNode*)malloc(sizeof(StackNode));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }
    new_node->element = value;
    new_node->next = parent;
    if (parent == NULL) {
        new_node->maxLower = value;
    } else {
        int parent_max = parent->maxLower;
        new_node->maxLower = (parent_max <= value) ? value : parent_max;
    }

    return new_node;
}

void stack_push(Stack* s, int value) {
    s->head = insert_stack_node(s->head, value);
}

int stack_pop(Stack* s) {
    if (s->head == NULL) {
        fprintf(stderr, "Stack is empty.\n");
        exit(EXIT_FAILURE);
    }
    int data = s->head->element;
    StackNode* tmp = s->head->next;
    free(s->head);
    s->head = tmp;
    return data;
}

bool stack_is_empty(Stack* s) {
    return (s->head == NULL);
}

int get_max_in_stack(Stack* s) {
    Stack* second_stack = create_stack();
    while (!stack_is_empty(s) && s->head->element != s->head->maxLower) {
        stack_push(second_stack, stack_pop(s));
    }
    int max = stack_pop(s);
    while (!stack_is_empty(second_stack)) {
        stack_push(s, stack_pop(second_stack));
    }
    stack_destroy(second_stack);
    return max;
}

Stack* merge_sort(Stack* s) {
    if (s->head == NULL || s->head->next == NULL) {
        return s;
    }
    Stack* left = create_stack();
    Stack* right = create_stack();
    StackNode* current = s->head;
    int index = 0;
    while (current != NULL) {
        if (index % 2 == 0) {
            stack_push(left, current->element);
        } else {
            stack_push(right, current->element);
        }
        current = current->next;
        index++;
    }
    left = merge_sort(left);
    right = merge_sort(right);
    Stack* merged = merge(left, right);
    stack_destroy(left); 
    stack_destroy(right);
    stack_destroy(s);
    return merged;
}


Stack* merge(Stack* left, Stack* right) {
    Stack* result = create_stack();
    while (!stack_is_empty(left) && !stack_is_empty(right)) {
        if (left->head->element <= right->head->element) {
            stack_push(result, stack_pop(left));
        } else {
            stack_push(result, stack_pop(right));
        }
    }
    while (!stack_is_empty(left)) {
        stack_push(result, stack_pop(left));
    }
    while (!stack_is_empty(right)) {
        stack_push(result, stack_pop(right));
    }
    Stack* reversed_result = create_stack();
    while (!stack_is_empty(result)) {
        stack_push(reversed_result, stack_pop(result));
    }
    stack_destroy(result);
    return reversed_result;
}

void stack_destroy(Stack* s) {
    if (s == NULL) return;
    while (!stack_is_empty(s)) {
        StackNode* temp = s->head;
        s->head = s->head->next;
        free(temp);
    }
    free(s);
}

void printStack(Stack* s) {
    if (stack_is_empty(s)) return;
    StackNode* now = s->head;
    printf("Stack head\n");
    printf("%d\n", now->element);
    while (now->next) {
        now = now->next;
        printf("%d\n", now->element);
    }
}