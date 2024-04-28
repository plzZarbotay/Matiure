#include "./list.h"

List *list_create()
{
    List *list = (List *)malloc(sizeof(List));
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    list->head = node;
    list->head->next = NULL;
    return list;
}

void list_insert(ListNode *node, Item value)
{
    ListNode *inserted = (ListNode *)malloc(sizeof(ListNode));
    inserted->data = value;
    inserted->next = node->next;
    node->next = inserted;
}

// Null | aaa | aaa <- bbb <- ccc
void list_delete_next(ListNode *node)
{
    ListNode *n = (ListNode *)malloc(sizeof(ListNode));
    ListNode *delete_node = node->next;
    if (delete_node->next != NULL)
    {
        n->data = delete_node->next->data;
        n->next = delete_node->next->next;
        node->next = n;
    }
    else
    {
        node->next = NULL;
    }
    free(delete_node);
}

bool list_is_empty(List *list)
{
    return (list->head->next == NULL);
}

void list_destroy(List *list)
{
    ListNode *n = list->head->next;
    while (list->head != NULL)
    {
        n = list->head->next;
        free(list->head);
        list->head = n;
    }
    list->head = NULL;
}