#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
    int lthread, rthread;   // 1 → thread, 0 → child
} Node;

// -----------------------------
// Create new node
// -----------------------------
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->lthread = newNode->rthread = 1;  // Initially threads
    return newNode;
}

// -----------------------------
// Insert as RIGHT child of s
// -----------------------------
void insertRight(Node* s, Node* r) {
    r->right = s->right;
    r->rthread = s->rthread;
    r->left = s;
    r->lthread = 1;

    s->right = r;
    s->rthread = 0;

    // If s had a right subtree before insertion
    if (r->rthread == 0) {
        Node* temp = r->right;
        while (temp->lthread == 0)
            temp = temp->left;
        temp->left = r;  // Update inorder successor's thread
    }
}

// -----------------------------
// Insert as LEFT child of s
// -----------------------------
void insertLeft(Node* s, Node* r) {
    r->left = s->left;
    r->lthread = s->lthread;
    r->right = s;
    r->rthread = 1;

    s->left = r;
    s->lthread = 0;

    // If s had a left subtree before insertion
    if (r->lthread == 0) {
        Node* temp = r->left;
        while (temp->rthread == 0)
            temp = temp->right;
        temp->right = r;  // Update inorder predecessor's thread
    }
}

// -----------------------------
// Find a node by data (non-BST, so inorder scan)
// -----------------------------
Node* find(Node* root, int key) {
    if (root == NULL) return NULL;
    Node* temp = root;

    // Move to leftmost node
    while (temp->lthread == 0)
        temp = temp->left;

    // Inorder traversal search
    while (temp != NULL) {
        if (temp->data == key)
            return temp;

        // Move to inorder successor
        if (temp->rthread == 1)
            temp = temp->right;
        else {
            temp = temp->right;
            while (temp != NULL && temp->lthread == 0)
                temp = temp->left;
        }
    }
    return NULL;
}

// -----------------------------
// Inorder traversal (threaded)
// -----------------------------
void inorder(Node* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    Node* temp = root;
    // Move to leftmost node
    while (temp->lthread == 0)
        temp = temp->left;

    while (temp != NULL) {
        printf("%d ", temp->data);

        // If right thread exists → go directly to inorder successor
        if (temp->rthread == 1)
            temp = temp->right;
        else {
            // Move to leftmost node in right subtree
            temp = temp->right;
            while (temp != NULL && temp->lthread == 0)
                temp = temp->left;
        }
    }
}

// -----------------------------
// Insertion wrapper (interactive)
// -----------------------------
void insert(Node** root) {
    int parentData, newData;
    char side;

    printf("\nEnter parent data: ");
    scanf("%d", &parentData);

    Node* parent = find(*root, parentData);
    if (parent == NULL) {
        printf("Parent not found.\n");
        return;
    }

    printf("Enter new node data: ");
    scanf("%d", &newData);
    printf("Insert as Left or Right child (L/R): ");
    scanf(" %c", &side);

    Node* newNode = createNode(newData);

    if (side == 'L' || side == 'l') {
        if (parent->lthread == 0)
            printf("Left subtree exists, adjusting threads accordingly.\n");
        insertLeft(parent, newNode);
    } 
    else if (side == 'R' || side == 'r') {
        if (parent->rthread == 0)
            printf("Right subtree exists, adjusting threads accordingly.\n");
        insertRight(parent, newNode);
    } 
    else {
        printf("Invalid side.\n");
        free(newNode);
    }
}

// -----------------------------
// Create the threaded tree
// -----------------------------
Node* createTree() {
    int data, n;
    printf("Enter root data: ");
    scanf("%d", &data);
    Node* root = createNode(data);

    printf("Enter number of other nodes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        insert(&root);

    return root;
}

// -----------------------------
// MAIN FUNCTION
// -----------------------------
int main() {
    Node* root = NULL;
    root = createTree();

    printf("\nInorder traversal (using threads): ");
    inorder(root);
    printf("\n");

    return 0;
}