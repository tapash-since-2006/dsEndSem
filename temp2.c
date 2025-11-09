
#include <stdio.h>
#include <stdlib.h>

// -----------------------------------------
// Node structure
// -----------------------------------------
struct Node {
    int key;
    int height;
    struct Node* left;
    struct Node* right;
};

// -----------------------------------------
// Utility functions
// -----------------------------------------
int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(struct Node* root) {
    return root ? root->height : 0;
}

int getBalance(struct Node* root) {
    return root ? getHeight(root->left) - getHeight(root->right) : 0;
}

// -----------------------------------------
// Create a new node
// -----------------------------------------
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1; // node-based convention (leaf = height 1)
    return newNode;
}

// -----------------------------------------
// Right rotation (LL case)
// -----------------------------------------
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    // Return new root
    return x;
}

// -----------------------------------------
// Left rotation (RR case)
// -----------------------------------------
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    // Return new root
    return y;
}

// -----------------------------------------
// Balance a node after insertion or deletion
// -----------------------------------------
struct Node* balanceNode(struct Node* root) {
    int balance = getBalance(root);

    // LL Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // LR Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // RL Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    // Already balanced
    return root;
}

// -----------------------------------------
// Insert a node in the AVL tree
// -----------------------------------------
struct Node* insert(struct Node* root, int key) {
    // Normal BST insertion
    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else {
        printf("Duplicate key %d not allowed\n", key);
        return root;
    }

    // Update height
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Balance the node
    return balanceNode(root);
}

// -----------------------------------------
// Find the smallest node (inorder successor helper)
// -----------------------------------------
struct Node* small(struct Node* root) {
    struct Node* curr = root;
    while (curr && curr->left != NULL)
        curr = curr->left;
    return curr;
}

// -----------------------------------------
// Delete a node from the AVL tree
// -----------------------------------------
struct Node* delete(struct Node* root, int key) {
    if (root == NULL)
        return root;

    // Traverse to find node
    if (key < root->key)
        root->left = delete(root->left, key);
    else if (key > root->key)
        root->right = delete(root->right, key);
    else {
        // Node found
        if (root->left == NULL || root->right == NULL) {
            struct Node* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        }

        // Node with two children
        struct Node* temp = small(root->right);
        root->key = temp->key;
        root->right = delete(root->right, temp->key);
    }

    // Update height
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Balance and return
    return balanceNode(root);
}

// -----------------------------------------
// Inorder traversal
// -----------------------------------------
void inorder(struct Node* root) {
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

// -----------------------------------------
// Example usage
// -----------------------------------------
int main() {
    struct Node* root = NULL;
    int n, key;

    printf("Enter number of nodes to insert: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter key for node %d: ", i + 1);
        scanf("%d", &key);
        root = insert(root, key);
    }

    printf("\nInorder traversal of AVL tree:\n");
    inorder(root);

    // Optionally delete nodes
    char choice;
    printf("\nDo you want to delete a node? (y/n): ");
    scanf(" %c", &choice);

    while (choice == 'y' || choice == 'Y') {
        printf("Enter key to delete: ");
        scanf("%d", &key);
        root = delete(root, key);
        printf("Inorder traversal after deletion:\n");
        inorder(root);
        printf("\nDo you want to delete another node? (y/n): ");
        scanf(" %c", &choice);
    }

    return 0;
}

