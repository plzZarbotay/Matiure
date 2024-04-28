#ifndef _STACK_H
#define _STACK_H

#include "stdlib.h"
#include "limits.h"
#include "stdbool.h"

typedef struct _node
{
    int element;
    int maxLower;
    struct _node *next;
} StackNode;

typedef struct
{
    StackNode *head;
} Stack;

Stack *create_stack();

StackNode *insert_stack_node(StackNode *parent, int value);

void stack_push(Stack *s, int value);

int stack_pop(Stack *s);

bool stack_is_empty(Stack *s);

void stack_destroy(Stack *s);

int get_max_in_stack(Stack *s);

Stack* merge(Stack* left, Stack* right);

Stack* merge_sort(Stack* s);

void printStack(Stack* s);

#endif
