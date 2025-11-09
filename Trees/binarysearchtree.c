#include <stdio.h>
#include <stdlib.h>

// Structure for a node
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// -------------------------
// Function Prototypes
// -------------------------
struct Node* createNode(int data);
struct Node* insert(struct Node* root, int data);
struct Node* searchRecursive(struct Node* root, int key);
struct Node* searchIterative(struct Node* root, int key);
struct Node* deleteNode(struct Node* root, int key);
struct Node* findMin(struct Node* root);
struct Node* findMax(struct Node* root);
void inorder(struct Node* root);
void preorder(struct Node* root);
void postorder(struct Node* root);

// -------------------------
// Create a new node
// -------------------------
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// -------------------------
// Insert a node
// -------------------------
struct Node* insert(struct Node* root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

// -------------------------
// Search (Recursive)
// -------------------------
struct Node* searchRecursive(struct Node* root, int key) {
    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return searchRecursive(root->left, key);
    else
        return searchRecursive(root->right, key);
}

// -------------------------
// Search (Iterative)
// -------------------------
struct Node* searchIterative(struct Node* root, int key) {
    while (root != NULL) {
        if (key == root->data)
            return root;
        else if (key < root->data)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}

// -------------------------
// Find minimum value node
// -------------------------
struct Node* findMin(struct Node* root) {
    while (root && root->left != NULL)
        root = root->left;
    return root;
}

// -------------------------
// Find maximum value node
// -------------------------
struct Node* findMax(struct Node* root) {
    while (root && root->right != NULL)
        root = root->right;
    return root;
}

// -------------------------
// Delete a node
// -------------------------
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        // Case 1: Leaf node
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        // Case 2: One child
        else if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Case 3: Two children
        // Option 1: Replace with smallest in right subtree
        struct Node* temp = findMin(root->right);
        // Option 2 (alternative): findMax(root->left)
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// -------------------------
// Traversal Functions
// -------------------------
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// -------------------------
// Main Function
// -------------------------
int main() {
    struct Node* root = NULL;

    // Create BST
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    // Searching
    int key = 40;
    printf("\nSearching (Recursive) for %d: ", key);
    struct Node* found = searchRecursive(root, key);
    if (found) printf("Found\n"); else printf("Not Found\n");

    printf("Searching (Iterative) for %d: ", key);
    found = searchIterative(root, key);
    if (found) printf("Found\n"); else printf("Not Found\n");

    // Deletion examples
    printf("\nDeleting a leaf node (20)\n");
    root = deleteNode(root, 20);
    inorder(root); printf("\n");

    printf("\nDeleting a node with one child (30)\n");
    root = deleteNode(root, 30);
    inorder(root); printf("\n");

    printf("\nDeleting a node with two children (50)\n");
    root = deleteNode(root, 50);
    inorder(root); printf("\n");

    return 0;
}
