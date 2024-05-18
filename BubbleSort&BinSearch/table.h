#ifndef KP9_TABLE_H
#define KP9_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "str.h"

#define TABLE_SIZE 12


typedef struct {
    int z;
} Key;

typedef struct {
    Key *key;
    String *data;
} Row;

typedef struct {
    Row *rows[TABLE_SIZE];
    int size;
} Table;


int compare_key(Key *z1, Key *z2);

String *convert_to_string(void);

Table *new_table(void);

void add_random_row(Table *);

int add_row(Table *);

void print_table(Table *);

void reverse_table(Table *);

void sort_table(Table *);

void clean_table(Table *);

void mix_table(Table *);

String *binary_search(int real_part, Table *);


#endif
