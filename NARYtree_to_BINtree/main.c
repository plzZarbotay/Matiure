#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct BNode {
    char data;
    struct BNode *left;
    struct BNode *right;
} BNode;

typedef struct NNode {
    char data;
    struct NNode *firstChild;
    struct NNode *nextSibling;
} NNode;

BNode* createBNode(char data) {
    BNode* node = (BNode*)malloc(sizeof(BNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

#define MAX_EXPR_SIZE 100

int precedence(char op) {
    switch (op) {
        case '+': case '-':
            return 1;
        case '*': case '/':
            return 2;
        default:
            return 0;
    }
}

void infixToPostfix(const char* infix, char* postfix) {
    char stack[MAX_EXPR_SIZE];
    int top = -1;
    int j = 0;
    for (int i = 0; infix[i]; i++) {
        if (isalnum(infix[i])) {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            stack[++top] = infix[i];
        } else if (infix[i] == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = stack[top--];
            }
            top--;
        } else {
            while (top != -1 && precedence(stack[top]) >= precedence(infix[i])) {
                postfix[j++] = stack[top--];
            }
            stack[++top] = infix[i];
        }
    }
    while (top != -1) {
        postfix[j++] = stack[top--];
    }
    postfix[j] = '\0';
}

BNode* constructBTreeFromPostfix(const char* postfix) {
    BNode* stack[MAX_EXPR_SIZE];
    int top = -1;
    for (int i = 0; postfix[i]; i++) {
        if (isalnum(postfix[i])) {
            stack[++top] = createBNode(postfix[i]);
        } else {
            BNode* node = createBNode(postfix[i]);
            node->right = stack[top--];
            node->left = stack[top--];
            stack[++top] = node;
        }
    }
    return stack[top];
}

NNode* createNNode(char data) {
    NNode* newNode = (NNode*)malloc(sizeof(NNode));
    newNode->data = data;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}

NNode* addSibling(NNode* node, NNode* sibling) {
    if (!node) return sibling;

    NNode* temp = node;
    while (temp->nextSibling) {
        temp = temp->nextSibling;
    }
    temp->nextSibling = sibling;
    return node;
}

NNode* binaryToNary(BNode* root) {
    if (!root) return NULL;

    NNode* nRoot = createNNode(root->data);

    if (root->left) {
        NNode* leftChild = binaryToNary(root->left);
        if ((leftChild->data == '+' || leftChild->data == '-' || leftChild->data == '/' || leftChild->data == '*') && root->data == leftChild->data) {
            NNode* temp = leftChild->firstChild;
            leftChild->firstChild = nRoot->firstChild;
            nRoot->firstChild = temp;
            free(leftChild);
        } else {
            nRoot->firstChild = addSibling(nRoot->firstChild, leftChild);
        }
    }

    if (root->right) {
        NNode* rightChild = binaryToNary(root->right);
        if ((rightChild->data == '+' || rightChild->data == '-' || rightChild->data == '/' || rightChild->data == '*') && root->data == rightChild->data) {
            NNode* temp = rightChild->firstChild;
            rightChild->firstChild = nRoot->firstChild;
            nRoot->firstChild = temp;
            free(rightChild);
        } else {
            nRoot->firstChild = addSibling(nRoot->firstChild, rightChild);
        }
    }

    return nRoot;
}


void printBTree(BNode* root, int space) {
    if (root == NULL) return;
    space += 10;
    printBTree(root->right, space);
    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("%c\n", root->data);
    printBTree(root->left, space);
}

void printNTree(NNode* root, int depth) {
    if (root == NULL) return;
    for (int i = 0; i < depth; i++) {
        printf(" ");
    }
    printf("%c\n", root->data);
    printNTree(root->firstChild, depth + 1);
    printNTree(root->nextSibling, depth);
}

void menu() {
    char expression[MAX_EXPR_SIZE];
    char postfix[MAX_EXPR_SIZE];
    BNode* bTreeRoot = NULL;
    NNode* nTreeRoot = NULL;

    while (1) {
        printf("\nМеню:\n");
        printf("1. Ввести выражение\n");
        printf("2. Показать двоичное дерево\n");
        printf("3. Перевести в n-арное дерево\n");
        printf("4. Показать n-арное дерево\n");
        printf("5. Выход\n");
        printf("Выберите опцию: ");
        int choice;
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Введите выражение: ");
                fgets(expression, MAX_EXPR_SIZE, stdin);
                expression[strcspn(expression, "\n")] = '\0';
                infixToPostfix(expression, postfix);
                bTreeRoot = constructBTreeFromPostfix(postfix);
                printf("Выражение успешно преобразовано в двоичное дерево.\n");
                break;
            case 2:
                if (bTreeRoot) {
                    printBTree(bTreeRoot, 0);
                } else {
                    printf("Сначала введите выражение.\n");
                }
                break;
            case 3:
                if (bTreeRoot) {
                    nTreeRoot = binaryToNary(bTreeRoot);
                    printf("Двоичное дерево успешно преобразовано в n-арное дерево.\n");
                } else {
                    printf("Сначала введите выражение.\n");
                }
                break;
            case 4:
                if (nTreeRoot) {
                    printNTree(nTreeRoot, 0);
                } else {
                    printf("Сначала преобразуйте двоичное дерево в n-арное.\n");
                }
                break;
            case 5:
                exit(0);
            default:
                printf("Неправильный выбор. Пожалуйста, попробуйте снова.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
