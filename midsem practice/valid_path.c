#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node *newNode(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

int is_prime(int num) {
    if (num <= 1) {
        return 0;
    }
    if (num <= 3) {
        return 1;
    }
    if (num % 2 == 0 || num % 3 == 0) {
        return 0;
    }
    return 1; // Assume composite if not divisible by 2 or 3
}

int valid_path(Node *root, int start, int end) {
    if (root == NULL) {
        return 0;
    }
    if (root->data == start) {
        if (root->data == end) {
            return is_prime(root->data);
        }
        int left_path = valid_path(root->left, start, end);
        if (left_path && is_prime(root->data)) {
            return 0; // Already found a prime in the left path
        }
        int right_path = valid_path(root->right, start, end);
        return (left_path || right_path) && !is_prime(root->data);
    }
    return valid_path(root->left, start, end) || valid_path(root->right, start, end);
}

int main() {
    Node *root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);

    int start = 1, end = 7;

    if (valid_path(root, start, end)) {
        printf("Valid path exists.\n");
    } else {
        printf("Valid path does not exist.\n");
    }

    return 0;
}