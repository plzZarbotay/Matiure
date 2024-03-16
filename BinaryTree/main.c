
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Исходник лабы лол

struct node {
  double item;
  struct node* left;
  struct node* right;
};

struct node* create(double value) {
  struct node* newNode = malloc(sizeof(struct node));
  newNode->item = value;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

struct node *insertValue(struct node* root, double value) {
    if (root == NULL) {
        return create(value);
    }
    if (value < root->item) {
        root->left = insertValue(root->left, value);
    } else if (value > root->item) {
        root->right = insertValue(root->right, value);
    }
    return root;
}

struct node* deleteNode(struct node* root, double value) {
    if (root == NULL) {
        return root;
    }
    // Если значение для удаления меньше значения корня, рекурсивно удаляем в левом поддереве
    if (value < root->item) {
        root->left = deleteNode(root->left, value);
    }
    // Если значение для удаления больше значения корня, рекурсивно удаляем в правом поддереве
    else if (value > root->item) {
        root->right = deleteNode(root->right, value);
    }
    // Если найден узел для удаления
    else {
        // Узел без детей или с одним ребенком
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        // Узел с двумя детьми
        // Находим наименьший узел в правом поддереве (или наибольший в левом поддереве) {ХРЕНЬ!!!}
        struct node* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }

        // Копируем данные наименьшего узла в текущий узел 
        root->item = temp->item;

        // Рекурсивно удаляем наименьший узел в правом поддереве
        root->right = deleteNode(root->right, temp->item);
    }
    return root;
}

void printTree(struct node *root, int space) { 
    if (root == NULL) { 
        return; 
    } 
    space += 3; 
    printTree(root->right, space); 
    printf("\n"); 
    for (int i = 5; i < space; i++) { 
        printf(" "); 
    } 
    printf("%lf\n", root->item); 
    printTree(root->left, space); 
} 

double findMinDepthLeafValue(struct node* root) {
    if (root == NULL) {
        printf("Дерево пустое.\n");
        return 0;
    }

    double minValue = root->item;
    int minDepth = -1;

    findLeafDepth(root, 0, &minValue, &minDepth);
    return minValue;
}

void findLeafDepth(struct node* node, int depth, double* minValue, int* minDepth) {
    if (node == NULL)
        return;
    if (node->left == NULL && node->right == NULL) {
        if (*minDepth == -1 || depth < *minDepth) {
            *minValue = node->item;
            *minDepth = depth;
        }
    }
    findLeafDepth(node->left, depth + 1, minValue, minDepth);
    findLeafDepth(node->right, depth + 1, minValue, minDepth);
}


struct node* freeTree (struct node* root) {
    if (root == NULL) {
      return root;
    }
    freeTree(root->left);
    freeTree(root->right);

    free(root);
}


int main() {
    double number;
    struct node* root = NULL;

    int choice;
    do {
        printf("\nМеню:\n");
        printf("1. Создать дерево\n");
        printf("2. Вставить значение\n");
        printf("3. Удалить узел\n");
        printf("4. Вывести дерево\n");
        printf("5. Определить значение листа с минимальной глубиной\n");
        printf("6. Освободить память от дерева\n");
        printf("7. Выйти из программы\n");

        printf("Введите ваш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введите значение для корневого узла: ");
                scanf("%lf", &number);
                root = freeTree(root);
                root = create(number);
                break;
            case 2:
                printf("Введите значение для вставки: ");
                scanf("%lf", &number);
                root = insertValue(root, number);
                break;
            case 3:
                printf("Введите значение для удаления: ");
                scanf("%lf", &number);
                root = deleteNode(root, number);
                break;
            case 4:
                printf("Дерево:\n");
                printTree(root, 5);
                break;
            case 5:
                printf("Значение листа с минимальной глубиной: %lf\n", findMinDepthLeafValue(root));
                break;
            case 6:
                root = freeTree(root);
                printf("Память от дерева освобождена.\n");
                break;
            case 7:
                printf("Завершение программы.\n");
                root = freeTree(root);
                break;
            default:
                printf("Неверный выбор. Пожалуйста, попробуйте еще раз.\n");
        }
    } while (choice != 7);

    return 0;
}