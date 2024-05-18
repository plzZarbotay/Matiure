#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>
#include "table.h"

int main() {
    int val, data;
    int key;
    bool flag = true;
    Table *table = new_table();
    while (flag) {
        printf("Menu:\n"
               "1. Fill table manually\n"
               "2. Fill table randomly\n"
               "3. Clear table\n"
               "4. Sort table\n"
               "5. Search by key\n"
               "6. Reverse table\n"
               "7. Mix table\n"
               "8. Print table\n"
               "9. Exit\n"
               "Input: ");
        scanf("%d", &val);
        switch (val) {
            case 1:
                system("clear");
                printf("Enter count of rows (<=12): ");
                scanf("%d", &data);
                while (data > 12) {
                    printf("Entered number > 12. Enter count of rows(<=12): ");
                    scanf("%d", &data);
                }
                for (int i = 0; i < data; ++i) {
                    add_row(table);
                }
                system("clear");
                break;
            case 2:
                system("clear");
                printf("Enter count of rows (<=12): ");
                scanf("%d", &data);
                while (data > 12) {
                    printf("Entered number > 12. Enter count of rows(<=12): ");
                    scanf("%d", &data);
                }
                for (int i = 0; i < data; ++i) {
                    add_random_row(table);
                }
                break;
            case 3:
                system("clear");
                if (!table->size)
                    printf("Table already cleared.\n");
                else {
                    clean_table(table);
                    table = new_table();
                    printf("Done\n");
                }
                getchar();
                getchar();
                system("clear");
                break;
            case 4:
                system("clear");
                sort_table(table);
                printf("Done\n");
                getchar();
                getchar();
                system("clear");
                break;
            case 5:
                system("clear");
                printf("Key: ");
                scanf("%d", &key);
                String *res = binary_search(key, table);
                if (res == NULL) {
                    printf("Not found!\n");
                } else {
                    print(res);
                    printf("\n");
                }
                break;
            case 6:
                system("clear");
                reverse_table(table);
                printf("Done\n");
                getchar();
                getchar();
                system("clear");
                break;
            case 7:
                system("clear");
                mix_table(table);
                printf("Done\n");
                getchar();
                getchar();
                system("clear");
                break;
            case 8:
                system("clear");
                print_table(table);
                getchar();
                while (getchar() != '\n') {
                    //
                }
                system("clear");
                break;
            case 9:
                flag = false;
                break;
            default:
                system("clear");
                printf("Unknown command\n");
                getchar();
                system("clear");
        }
    }
    clean_table(table);
    return 0;
}
