#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "table.h"
#include "str.h"

int num_length(int num) {
    if (!num) return 1;
    int res = 0;
    while (num) {
        num /= 10;
        res++;
    }
    return res;
}

void spaces(int count) {
    for (int i = 0; i < count; i++)
        printf(" ");
}

Table *new_table() {
    Table *table = (Table *) malloc(sizeof(Table));
    for (int i = 0; i < TABLE_SIZE; i++)
        table->rows[i] = NULL;
    table->size = 0;
    return table;
}

int check_key(int key, Table *table) {
    if (table->size)
        for (int i = 0; i < table->size; i++)
            if (table->rows[i]->key->z == key) {
                return 1;
            }
    return 0;
}

void add_random_row(Table *table) {
    int rand_key_num = rand() % 100000;
    while (check_key(rand_key_num, table)) {
        rand_key_num = rand() % 100000;
    }
    srand(time(NULL) % rand() % (rand() % 10000));
    Row *row = (Row *) malloc(sizeof(Row));
    row->key = (Key *) malloc(sizeof(Key));
    row->key->z = rand_key_num;
    row->data = random_string(rand() % 15 + 2);
    table->rows[table->size] = row;
    table->size++;
}

String *convert_to_string(void) {
    String *data = create_string();
    char chr = getchar();
    while ((chr = getchar()) != '\n')
        add(chr, data);
    return data;
}

int add_row(Table *table) {
    if (table->size == 10) {
        printf("Table overflow!\n\n ");
        return 0;
    }
    Row *row = (Row *) malloc(sizeof(Row));
    row->key = (Key *) malloc(sizeof(Key));
    printf("Enter key: ");
    int key;
    scanf("%d", &key);

    if (check_key(key, table)) {
        printf("The entered key already exists.\n\n ");
        free(row->key);
        free(row);
        return 0;
    }

    printf("Enter data: ");
    row->key->z = key;

    String *data = convert_to_string();

    row->data = data;

    table->rows[table->size] = row;
    table->size++;
    return 1;
}

void print_table(Table *table) {
    if (!table->size) {
        printf("EMPTY\n");
        return;
    }
    int a = 0, b = 0, c = 0;
    for (int i = 0; i < table->size; i++) {
        if (num_length(table->rows[i]->key->z) > a)
            a = num_length(table->rows[i]->key->z);
        if (table->rows[i]->data->size > c)
            c = table->rows[i]->data->size;
    }

    printf(" ");
    for (int i = 0; i < table->size; i++) {
        printf(" ");
        printf("| ");
        spaces(a - num_length(table->rows[i]->key->z));
        printf("%d ", table->rows[i]->key->z);
        spaces(b - num_length(table->rows[i]->key->z));
        printf(" | ");
        print(table->rows[i]->data);
        spaces(c - table->rows[i]->data->size);
        printf(" |\n ");
    }
}

void swap(int first, int second, Table *table) {
    Row *temp = table->rows[first];
    table->rows[first] = table->rows[second];
    table->rows[second] = temp;
}

void swap_rows(Row **a, Row **b) {
    Row *temp = *a;
    *a = *b;
    *b = temp;
}

void reverse_table(Table *table) {
    if (table->size > 1)
        for (int i = 0; i < table->size / 2; i++)
            swap(i, table->size - i - 1, table);
}

void sort_table(Table *table) {
    int i, j;
    for (i = 0; i < table->size - 1; i++) {
        for (j = 0; j < table->size - i - 1; j++) {
            if (table->rows[j]->key->z > table->rows[j + 1]->key->z) {
                Key *tempKey = table->rows[j]->key;
                table->rows[j]->key = table->rows[j + 1]->key;
                table->rows[j + 1]->key = tempKey;

                String *tempData = table->rows[j]->data;
                table->rows[j]->data = table->rows[j + 1]->data;
                table->rows[j + 1]->data = tempData;
            }
        }
    }
}




void clean_table(Table *table) {
    for (int i = 0; i < table->size; i++) {
        free(table->rows[i]->key);
        clean(table->rows[i]->data);
        free(table->rows[i]);
    }
    free(table);
}

void mix_table(Table *table) {
    if (table->size > 1) {
        srand(time(NULL));
        for (int i = rand() % (table->size - 1); i < table->size; i += rand() % 3)
            swap(i, table->size - i - 1, table);
    }
}


int comb_compare(int key_first, int key_second) {
    if ((key_first > key_second))
        return 1;
    if ((key_first < key_second))
        return -1;
    return 0;
}

String *binary_search(int key, Table *table) {
    if (!table->size)
        return NULL;

    //sort_table(table);

    int low = 0, high = table->size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (table->rows[mid]->key->z == key)
            return table->rows[mid]->data;

        if (table->rows[mid]->key->z > key)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return NULL;
}

