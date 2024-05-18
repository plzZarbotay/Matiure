#ifndef KP9_STRING_H
#define KP9_STRING_H

typedef struct node {
    char chr;
    struct node *next;
} StringNode;

typedef struct {
    StringNode *head;
    StringNode *tail;
    int size;
} String;

typedef struct {
    StringNode *node;
} Iterator;

void add(char, String *);

String *create_string(void);

String *convert_key(String *);

String *random_string(int);

void print(String *);

void clean(String *str);

int compare(String *left, String *right);

#endif