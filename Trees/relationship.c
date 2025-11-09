#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node *left, *right;
};

// -------------------- Node creation --------------------
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// -------------------- Queue for building interactively --------------------
struct QueueNode {
    struct Node* treeNode;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode *front, *rear;
};

struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(struct Queue* q, struct Node* node) {
    struct QueueNode* temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    temp->treeNode = node;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

struct Node* dequeue(struct Queue* q) {
    if (q->front == NULL)
        return NULL;
    struct QueueNode* temp = q->front;
    struct Node* node = temp->treeNode;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return node;
}

int isEmpty(struct Queue* q) {
    return q->front == NULL;
}

// -------------------- Find Parent --------------------
struct Node* findParent(struct Node* root, int key, struct Node* parent) {
    if (root == NULL)
        return NULL;

    if (root->data == key)
        return parent;

    struct Node* left = findParent(root->left, key, root);
    if (left != NULL) return left;

    return findParent(root->right, key, root);
}

// -------------------- Print Immediate Children --------------------
void printChildren(struct Node* root, int key) {
    if (root == NULL) return;

    if (root->data == key) {
        if (root->left)
            printf("Left Child: %d\n", root->left->data);
        else
            printf("Left Child: NULL\n");

        if (root->right)
            printf("Right Child: %d\n", root->right->data);
        else
            printf("Right Child: NULL\n");
        return;
    }

    printChildren(root->left, key);
    printChildren(root->right, key);
}

// -------------------- Print Ancestors --------------------
bool printAncestors(struct Node* root, int key) {
    if (root == NULL)
        return false;

    if (root->data == key)
        return true;

    if (printAncestors(root->left, key) || printAncestors(root->right, key)) {
        printf("%d ", root->data);
        return true;
    }

    return false;
}

// -------------------- Print Descendants --------------------
void printDescendants(struct Node* root) {
    if (root == NULL)
        return;
    printf("%d ", root->data);
    printDescendants(root->left);
    printDescendants(root->right);
}

void printAllDescendants(struct Node* root, int key) {
    if (root == NULL)
        return;

    if (root->data == key) {
        printf("Descendants of %d: ", key);
        if (!root->left && !root->right)
            printf("None");
        else {
            if (root->left) printDescendants(root->left);
            if (root->right) printDescendants(root->right);
        }
        printf("\n");
        return;
    }

    printAllDescendants(root->left, key);
    printAllDescendants(root->right, key);
}

// -------------------- Build Tree Interactively --------------------
struct Node* buildTreeInteractive() {
    int val;
    printf("Enter root value (-1 for no node): ");
    scanf("%d", &val);
    if (val == -1)
        return NULL;

    struct Node* root = createNode(val);
    struct Queue* q = createQueue();
    enqueue(q, root);

    while (!isEmpty(q)) {
        struct Node* current = dequeue(q);
        int leftVal, rightVal;

        printf("Enter left child of %d (-1 for no node): ", current->data);
        scanf("%d", &leftVal);
        if (leftVal != -1) {
            current->left = createNode(leftVal);
            enqueue(q, current->left);
        }

        printf("Enter right child of %d (-1 for no node): ", current->data);
        scanf("%d", &rightVal);
        if (rightVal != -1) {
            current->right = createNode(rightVal);
            enqueue(q, current->right);
        }
    }

    return root;
}

// -------------------- Hardcoded Sample Tree --------------------
struct Node* buildHardcodedTree() {
    //        1
    //       / \
    //      2   3
    //     / \   \
    //    4   5   6
    //             \
    //              7
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->right = createNode(6);
    root->right->right->right = createNode(7);
    return root;
}

// -------------------- MAIN --------------------
int main() {
    struct Node* root = NULL;
    int choice;

    printf("Choose tree input method:\n");
    printf("1. Use Hardcoded Tree (default)\n");
    printf("2. Enter Tree Interactively\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 2)
        root = buildTreeInteractive();
    else
        root = buildHardcodedTree();

    int key;
    printf("\nEnter node value to analyze: ");
    scanf("%d", &key);

    printf("\n--- Node Relationships ---\n");

    struct Node* parent = findParent(root, key, NULL);
    if (parent)
        printf("Parent: %d\n", parent->data);
    else
        printf("Parent: None (root node)\n");

    printChildren(root, key);

    printf("Ancestors: ");
    if (!printAncestors(root, key))
        printf("None");
    printf("\n");

    printAllDescendants(root, key);

    return 0;
}
