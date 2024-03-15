#include <stdlib.h>
#include <stdio.h>

typedef struct _b_node {
    int data;
    struct _b_node* parent;
    struct _b_node* left;
    struct _b_node* right;
} Binary_Node;

typedef struct _tree {
    Binary_Node *root;
} Tree;

Binary_Node * newBinaryNode(int data) {
    Binary_Node *node = (Binary_Node *)malloc(sizeof(Binary_Node));
    node->data = data;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void insertIntoTree(Binary_Node *root, int data) {
    if (data < root->data) {
        if (root->left == NULL) {
            root->left = newBinaryNode(data);
            root->left->parent = root;
        } else {
            insertIntoTree(root->left, data);
        }
    } else {
        if (root->right == NULL) {
            root->right = newBinaryNode(data);
            root->right->parent = root;
        } else {
            insertIntoTree(root->right, data);
        }
    }
}

void createBinaryTree(Tree *tree, int *data, int size) {
    if (size <= 0)
        return;

    tree->root = newBinaryNode(data[0]);
    for (int i = 1; i < size; i++) {
        insertIntoTree(tree->root, data[i]);
    }
}

void printPreOrder(Binary_Node *node) {
    if (node == NULL)
        return;
    printf("%d ", node->data);
    printPreOrder(node->left);
    printPreOrder(node->right);
}

int main(void) {
    int data[] = {5, 3, 2, 10, 8, 12, 15};
    int size = sizeof(data) / sizeof(data[0]);

    Tree tree;
    createBinaryTree(&tree, data, size);

    printf("Pre-order traversal of the binary tree: ");
    printPreOrder(tree.root);
    printf("\n");

    // Free memory (not implemented in this example)

    return 0;
}
