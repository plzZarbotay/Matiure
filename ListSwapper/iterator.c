#include "./iterator.h"
#include "stdio.h"

Iterator *iter_create(List *list) {
    Iterator *iter = (Iterator *) malloc(sizeof(Iterator));
    iter->node = list->head;
    return iter;
}

ListNode *iter_next(Iterator *iter) {
    iter->node = iter->node->next;
    return iter->node;
}

bool iter_has_next(Iterator *iter) {
    return iter->node->next != NULL;
}

void iter_set(Iterator *iter, Item value) {
    iter->node->data = value;
}

ListNode *iter_get_next_node(Iterator *iter) {
    return iter->node->next;
}

Item iter_get(Iterator *iter) {
    return iter->node->data;
}

void iter_delete(Iterator *iter) {
    ListNode *tmp = iter->node->next;
    iter->node->next = tmp->next;
    free(tmp);
}

void print_list(Iterator *iter) {
    printf("HEAD ");
    while (iter_next(iter) != NULL) {
        printf("%ld", iter_get(iter));
        if (iter_has_next(iter)) {
            printf(" -> ");
        }
    }
}


int list_length(Iterator *iter) {
    int length = 0;
    while (iter_next(iter) != NULL) {
        length++;
    }
    return length;
}


void swapper(Iterator *iter, int k) {
    ListNode *prev = NULL;
    ListNode *temp = NULL;
    ListNode *saved = NULL;
    ListNode *current = iter->node;
    ListNode *next = NULL;
    int count = 0;

    // Перемещаемся до k-1 элемента
    while (current != NULL && count < k - 1) {
        prev = current;
        current = current->next;
        count++;
    }

    // Проверяем, есть ли k-1 и k+1 элементы
    if (prev == NULL || current == NULL || current->next == NULL) {
        printf("Elements Error!\n");
        return;
    }

    temp = prev->data;
    prev->data = current->next->data;
    current->next->data = temp;


}

