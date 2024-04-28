#include <stdio.h>
#include "./list.h"
#include "./iterator.h"

#define MENU "Menu:\n1. Add value\n2. Delete value\n3. Get list length\n4. Change\n5. Print list\n6. Exit\nInput: "

int main()
{
    int val, k; // Declare k outside the switch statement
    List *l = list_create();
    long data;
    bool flag = true;
    Iterator *it;

    while (flag)
    {
        printf(MENU);
        scanf("%d", &val);

        switch (val)
        {
        case 1:
            printf("Enter value to add: ");
            scanf("%ld", &data);
            list_insert(l->head, labs(data)); // Use labs() for absolute value of long
            break;
        case 2:
            printf("Enter value to delete: ");
            scanf("%ld", &data);
            it = iter_create(l);
            if (iter_get_next_node(it)->data == data)
            {
                list_delete_next(it->node);
                break;
            }
            while (iter_next(it) != NULL)
            {
                if (iter_has_next(it))
                {
                    if (iter_get_next_node(it)->data == data)
                    {
                        list_delete_next(it->node);
                        break;
                    }
                }
            }
            free(it);
            break;
        case 3:
            printf("List length: ");
            it = iter_create(l);
            printf("%d\n", list_length(it));
            free(it);
            break;
        case 4:
            printf("Enter k to change: ");
            scanf("%d", &k);
            it = iter_create(l);
            swapper(it, k+1);
            free(it);
            break;
        case 5:
            printf("Printing list: ");
            it = iter_create(l);
            print_list(it);
            printf("\n");
            free(it);
            break;
        case 6:
            flag = false;
            break;
        default:
            printf("Unknown command\n");
        }
    }

    list_destroy(l);
    free(l);
    return 0;
}
