#ifndef _ITERATOR_H
#define _ITERATOR_H

#include "list.h"

typedef struct
{
    ListNode *node;
} Iterator;

Iterator *iter_create(List *list);

ListNode *iter_next(Iterator *iter);

bool iter_has_next(Iterator *iter);

void iter_set(Iterator *iter, Item value);

Item iter_get(Iterator *iter);

void iter_delete(Iterator *iter);

void print_list(Iterator *iter);

ListNode *iter_get_next_node(Iterator *iter);

int list_length(Iterator *iter);

bool check_sort(Iterator *iter);

void swapper(Iterator *iter, int k);
#endif
