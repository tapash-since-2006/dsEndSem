// #include <stdio.h>
// #include <stdlib.h>

// // Node structure
// struct Node {
//     int key, height;
//     struct Node *left, *right;
// };

// // Utility functions
// int max(int a, int b) { return (a > b) ? a : b; }

// int height(struct Node* node) {
//     return node ? node->height : 0;
// }

// struct Node* newNode(int key) {
//     struct Node* node = (struct Node*)malloc(sizeof(struct Node));
//     node->key = key;
//     node->left = node->right = NULL;
//     node->height = 1;
//     return node;
// }

// // Rotations
// struct Node* rightRotate(struct Node* y) {
//     struct Node* x = y->left;
//     struct Node* T2 = x->right;

//     x->right = y;
//     y->left = T2;

//     y->height = 1 + max(height(y->left), height(y->right));
//     x->height = 1 + max(height(x->left), height(x->right));
//     return x;
// }

// struct Node* leftRotate(struct Node* x) {
//     struct Node* y = x->right;
//     struct Node* T2 = y->left;

//     y->left = x;
//     x->right = T2;

//     x->height = 1 + max(height(x->left), height(x->right));
//     y->height = 1 + max(height(y->left), height(y->right));
//     return y;
// }

// int getBalance(struct Node* node) {
//     return node ? height(node->left) - height(node->right) : 0;
// }

// // ✅ Balance function
// struct Node* balanceNode(struct Node* node) {
//     int balance = getBalance(node);

//     // LL
//     if (balance > 1 && getBalance(node->left) >= 0)
//         return rightRotate(node);

//     // LR
//     if (balance > 1 && getBalance(node->left) < 0) {
//         node->left = leftRotate(node->left);
//         return rightRotate(node);
//     }

//     // RR
//     if (balance < -1 && getBalance(node->right) <= 0)
//         return leftRotate(node);

//     // RL
//     if (balance < -1 && getBalance(node->right) > 0) {
//         node->right = rightRotate(node->right);
//         return leftRotate(node);
//     }

//     return node; // Balanced already
// }

// // Find smallest node (used in deletion)
// struct Node* minValueNode(struct Node* node) {
//     struct Node* current = node;
//     while (current->left)
//         current = current->left;
//     return current;
// }

// // Insertion
// struct Node* insert(struct Node* node, int key) {
//     if (!node)
//         return newNode(key);

//     if (key < node->key)
//         node->left = insert(node->left, key);
//     else if (key > node->key)
//         node->right = insert(node->right, key);
//     else
//         return node; // Duplicate not allowed

//     node->height = 1 + max(height(node->left), height(node->right));

//     // ✅ Just call balance once
//     return balanceNode(node);
// }

// // Deletion
// struct Node* deleteNode(struct Node* root, int key) {
//     if (!root)
//         return root;

//     if (key < root->key)
//         root->left = deleteNode(root->left, key);
//     else if (key > root->key)
//         root->right = deleteNode(root->right, key);
//     else {
//         // Node found
//         if (!root->left || !root->right) {
//             struct Node* temp = root->left ? root->left : root->right;

//             if (!temp) { // No child
//                 free(root);
//                 root = NULL;
//             } else { // One child
//                 *root = *temp;
//                 free(temp);
//             }
//         } else {
//             struct Node* temp = minValueNode(root->right);
//             root->key = temp->key;
//             root->right = deleteNode(root->right, temp->key);
//         }
//     }

//     if (!root)
//         return root;

//     root->height = 1 + max(height(root->left), height(root->right));

//     // ✅ Just call balance once
//     return balanceNode(root);
// }

// // Traversals
// void inorder(struct Node* root) {
//     if (root) {
//         inorder(root->left);
//         printf("%d ", root->key);
//         inorder(root->right);
//     }
// }

// void preorder(struct Node* root) {
//     if (root) {
//         printf("%d ", root->key);
//         preorder(root->left);
//         preorder(root->right);
//     }
// }

// void postorder(struct Node* root) {
//     if (root) {
//         postorder(root->left);
//         postorder(root->right);
//         printf("%d ", root->key);
//     }
// }

// // Driver
// int main() {
//     struct Node* root = NULL;

//     root = insert(root, 9);
//     root = insert(root, 5);
//     root = insert(root, 10);
//     root = insert(root, 0);
//     root = insert(root, 6);
//     root = insert(root, 11);
//     root = insert(root, -1);
//     root = insert(root, 1);
//     root = insert(root, 2);

//     printf("Inorder traversal before deletion:\n");
//     inorder(root);

//     root = deleteNode(root, 10);

//     printf("\n\nInorder traversal after deleting 10:\n");
//     inorder(root);

//     printf("\n\nPreorder traversal:\n");
//     preorder(root);

//     printf("\n\nPostorder traversal:\n");
//     postorder(root);

//     return 0;
// }



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

    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, -1);
    root = insert(root, 1);
    root = insert(root, 2);

    printf("Inorder traversal of AVL tree:\n");
    inorder(root);

    root = delete(root, 10);
    printf("\n\nAfter deleting 10:\n");
    inorder(root);

    return 0;
}




