#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct BNode {
    char* data;
    struct BNode *left;
    struct BNode *right;
} BNode;

typedef struct NNode {
    char* data;
    struct NNode *firstChild;
    struct NNode *nextSibling;
} NNode;

BNode* createBNode(const char* data) {
    BNode* node = (BNode*)malloc(sizeof(BNode));
    node->data = strdup(data);
    node->left = node->right = NULL;
    return node;
}

NNode* createNNode(const char* data) {
    NNode* newNode = (NNode*)malloc(sizeof(NNode));
    newNode->data = strdup(data);
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}

void freeBTree(BNode* root) {
    if (root) {
        freeBTree(root->left);
        freeBTree(root->right);
        free(root->data);
        free(root);
    }
}

void freeNTree(NNode* root) {
    if (root) {
        freeNTree(root->firstChild);
        freeNTree(root->nextSibling);
        free(root->data);
        free(root);
    }
}

#define MAX_EXPR_SIZE 100

int precedence(char op) {
    switch (op) {
        case '+': case '-':
            return 1;
        case '*': case '/':
            return 2;
        case '~': // Унарный минус
            return 3;
        default:
            return 0;
    }
}

void infixToPostfix(const char* infix, char* postfix) {
    char stack[MAX_EXPR_SIZE][MAX_EXPR_SIZE];
    int top = -1;
    int j = 0;
    for (int i = 0; infix[i];) {
        if (isdigit(infix[i])) {
            char num[MAX_EXPR_SIZE] = {0};
            int k = 0;
            while (isdigit(infix[i])) {
                num[k++] = infix[i++];
            }
            num[k] = '\0';
            j += sprintf(postfix + j, "%s ", num);
        } else if (infix[i] == '(') {
            strcpy(stack[++top], "(");
            i++;
        } else if (infix[i] == ')') {
            while (top != -1 && strcmp(stack[top], "(") != 0) {
                j += sprintf(postfix + j, "%s ", stack[top--]);
            }
            if (top != -1 && strcmp(stack[top], "(") == 0) {
                top--; // Pop the '('
            }
            i++;
        } else if (isspace(infix[i])) {
            i++;
        } else {
            if (infix[i] == '-' && (i == 0 || infix[i - 1] == '(' || !isdigit(infix[i - 1]))) {
                char num[MAX_EXPR_SIZE] = {0};
                int k = 0;
                num[k++] = infix[i++];
                while (isdigit(infix[i])) {
                    num[k++] = infix[i++];
                }
                num[k] = '\0';
                j += sprintf(postfix + j, "%s ", num);
            } else {
                while (top != -1 && precedence(stack[top][0]) >= precedence(infix[i])) {
                    j += sprintf(postfix + j, "%s ", stack[top--]);
                }
                char op[2] = {infix[i], '\0'};
                strcpy(stack[++top], op);
                i++;
            }
        }
    }
    while (top != -1) {
        j += sprintf(postfix + j, "%s ", stack[top--]);
    }
    postfix[j] = '\0';
}

BNode* constructBTreeFromPostfix(const char* postfix) {
    BNode* stack[MAX_EXPR_SIZE];
    int top = -1;
    char token[MAX_EXPR_SIZE];
    int i = 0;

    while (sscanf(postfix + i, "%s", token) != EOF) {
        i += strlen(token) + 1; // Move to the next token
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            stack[++top] = createBNode(token);
        } else {
            BNode* node = createBNode(token);
            node->right = stack[top--];
            node->left = stack[top--];
            stack[++top] = node;
        }
    }
    return stack[top];
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
        nRoot->firstChild = addSibling(nRoot->firstChild, leftChild);
    }

    if (root->right) {
        NNode* rightChild = binaryToNary(root->right);
        nRoot->firstChild = addSibling(nRoot->firstChild, rightChild);
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
    printf("%s\n", root->data);
    printBTree(root->left, space);
}

void printNTree(NNode* root, int depth) {
    if (root == NULL) return;
    for (int i = 0; i < depth; i++) {
        printf(" ");
    }
    printf("%s\n", root->data);
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
