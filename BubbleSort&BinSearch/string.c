#include <stdlib.h>
#include <stdio.h>

#include "str.h"

Iterator *iterator(StringNode *node) {
    Iterator *iter = (Iterator *) malloc(sizeof(Iterator));
    iter->node = node;
    return iter;
}

void next(Iterator *iter) {
    iter->node = iter->node->next;
}

void add(char chr, String *str) {
    StringNode *node = (StringNode *) malloc(sizeof(StringNode));
    node->chr = chr;
    node->next = NULL;
    if (!str->size)
        str->head = str->tail = node;
    else {
        str->tail->next = node;
        str->tail = node;
    }
    str->size++;
}

String *create_string(void) {
    String *res = (String *) malloc(sizeof(String));
    res->head = res->tail = NULL;
    res->size = 0;
    return res;
}

String *convert_key(String *str) {
    String *key = create_string();
    Iterator *iter = iterator(str->head);
    int p = str->size > 4 ? 4 : str->size;
    for (int i = 0; i < p; i++) {
        add(iter->node->chr, key);
        next(iter);
    }
    return key;
}

String *random_string(int size) {
    String *res = create_string();
    while (res->size != size)
        add((char) (rand() % 70 + (int) '0'), res);
    return res;
}

void print(String *str) {
    Iterator *iter = iterator(str->head);
    while (iter->node != NULL) {
        printf("%c", iter->node->chr);
        next(iter);
    }
    free(iter);
}

void clean(String *str) {
    Iterator *iter = iterator(str->head);
    while (iter->node != NULL) {
        StringNode *temp = iter->node;
        next(iter);
        free(temp);
    }
    free(str);
    free(iter);
}

int compare(String *left, String *right) {
    if (left->size == right->size) {
        Iterator *left_iter = iterator(left->head);
        Iterator *right_iter = iterator(right->head);
        while (right_iter->node != NULL) {
            if (left_iter->node == NULL) {
                free(left_iter);
                free(right_iter);
                return -1;
            }
            if (left_iter->node->chr > right_iter->node->chr) {
                free(left_iter);
                free(right_iter);
                return 1;
            }
            if (left_iter->node->chr < right_iter->node->chr) {
                free(left_iter);
                free(right_iter);
                return -1;
            }
            next(left_iter);
            next(right_iter);
        }
        free(left_iter);
        free(right_iter);
        return 0;
    }
    return 1;
}