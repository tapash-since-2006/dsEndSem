#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Iterative BST insertion
struct Node* insertBST(struct Node* root, int data) {
    struct Node* newNode = createNode(data);

    if (!root) return newNode;

    struct Node* curr = root;
    struct Node* parent = NULL;

    while (curr) {
        parent = curr;
        if (data < curr->data)
            curr = curr->left;
        else if (data > curr->data)
            curr = curr->right;
        else {
            // Duplicate, do not insert
            free(newNode);
            return root;
        }
    }

    if (data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    return root;
}

// Inorder traversal
void inorder(struct Node* root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

// Example usage
int main() {
    struct Node* root = NULL;
    int n, val;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter value to insert: ");
        scanf("%d", &val);
        root = insertBST(root, val);
    }

    printf("Inorder traversal of BST:\n");
    inorder(root);
    printf("\n");

    return 0;
}
