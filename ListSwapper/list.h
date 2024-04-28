#ifndef _LIST_H
#define _LIST_H

#include "stdbool.h"
#include "stdlib.h"

typedef size_t Item;

typedef struct listnode {
    Item data;
    struct listnode *next;
} ListNode;

typedef struct {
    ListNode *head;
    ListNode *last;
} List;

List *list_create();

void list_insert(ListNode *after_node, Item value);

void list_delete_next(ListNode *node);

bool list_is_empty(List *list);

void list_destroy(List *list);

#endif