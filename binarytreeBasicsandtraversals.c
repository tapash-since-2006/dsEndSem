#include <stdio.h>
#include <stdlib.h>

#define MAX 100  // For stack and queue size

// -------------------------
// Node structure
// -------------------------
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// -------------------------
// Stack for iterative traversals
// -------------------------
struct Stack {
    struct Node* arr[MAX];
    int top;
};

void initStack(struct Stack* s) { s->top = -1; }
int isEmptyStack(struct Stack* s) { return s->top == -1; }
void push(struct Stack* s, struct Node* node) { s->arr[++(s->top)] = node; }
struct Node* pop(struct Stack* s) { return s->arr[(s->top)--]; }
struct Node* peek(struct Stack* s) { return s->arr[s->top]; }

// -------------------------
// Queue for level-order traversal
// -------------------------
struct Queue {
    struct Node* arr[MAX];
    int front, rear;
};

void initQueue(struct Queue* q) { q->front = q->rear = -1; }
int isEmptyQueue(struct Queue* q) { return q->front == -1; }

void enqueue(struct Queue* q, struct Node* node) {
    if (q->rear == MAX - 1) return; // Overflow check
    if (q->front == -1) q->front = 0;
    q->arr[++(q->rear)] = node;
}

struct Node* dequeue(struct Queue* q) {
    if (isEmptyQueue(q)) return NULL;
    struct Node* node = q->arr[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
    return node;
}

// -------------------------
// Node creation
// -------------------------
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// -------------------------
// Recursive tree creation
// -------------------------
struct Node* createTree(int data) {
    if (data == -1)
        return NULL;

    struct Node* root = createNode(data);

    int leftData, rightData;
    printf("Enter left child of %d (-1 for no node): ", data);
    scanf("%d", &leftData);
    root->left = createTree(leftData);

    printf("Enter right child of %d (-1 for no node): ", data);
    scanf("%d", &rightData);
    root->right = createTree(rightData);

    return root;
}

// -------------------------
// Recursive Traversals
// -------------------------
void inorderRecursive(struct Node* root) {
    if (root == NULL) return;
    inorderRecursive(root->left);
    printf("%d ", root->data);
    inorderRecursive(root->right);
}

void preorderRecursive(struct Node* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorderRecursive(root->left);
    preorderRecursive(root->right);
}

void postorderRecursive(struct Node* root) {
    if (root == NULL) return;
    postorderRecursive(root->left);
    postorderRecursive(root->right);
    printf("%d ", root->data);
}

// -------------------------
// Iterative Traversals
// -------------------------

// Inorder iterative
void inorderIterative(struct Node* root) {
    struct Stack s;
    initStack(&s);
    struct Node* curr = root;

    while (curr != NULL || !isEmptyStack(&s)) {
        while (curr != NULL) {
            push(&s, curr);
            curr = curr->left;
        }
        curr = pop(&s);
        printf("%d ", curr->data);
        curr = curr->right;
    }
}

// Preorder iterative
void preorderIterative(struct Node* root) {
    if (root == NULL) return;
    struct Stack s;
    initStack(&s);
    push(&s, root);

    while (!isEmptyStack(&s)) {
        struct Node* curr = pop(&s);
        printf("%d ", curr->data);
        if (curr->right) push(&s, curr->right);
        if (curr->left) push(&s, curr->left);
    }
}

// Postorder iterative (using two stacks)
void postorderIterative(struct Node* root) {
    if (root == NULL) return;
    struct Stack s1, s2;
    initStack(&s1);
    initStack(&s2);
    push(&s1, root);

    while (!isEmptyStack(&s1)) {
        struct Node* curr = pop(&s1);
        push(&s2, curr);
        if (curr->left) push(&s1, curr->left);
        if (curr->right) push(&s1, curr->right);
    }

    while (!isEmptyStack(&s2))
        printf("%d ", pop(&s2)->data);
}

// -------------------------
// Level Order Traversal (BFS)
// -------------------------
void levelOrder(struct Node* root) {
    if (root == NULL) return;

    struct Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while (!isEmptyQueue(&q)) {
        struct Node* curr = dequeue(&q);
        printf("%d ", curr->data);

        if (curr->left) enqueue(&q, curr->left);
        if (curr->right) enqueue(&q, curr->right);
    }
}

// -------------------------
// Main function
// -------------------------
int main() {
    int rootData;
    printf("Enter root data (-1 for no node): ");
    scanf("%d", &rootData);

    struct Node* root = createTree(rootData);

    printf("\n--- Recursive Traversals ---\n");
    printf("Inorder: ");
    inorderRecursive(root);
    printf("\nPreorder: ");
    preorderRecursive(root);
    printf("\nPostorder: ");
    postorderRecursive(root);

    printf("\n\n--- Iterative Traversals ---\n");
    printf("Inorder: ");
    inorderIterative(root);
    printf("\nPreorder: ");
    preorderIterative(root);
    printf("\nPostorder: ");
    postorderIterative(root);

    printf("\n\n--- Level Order Traversal (BFS) ---\n");
    levelOrder(root);
    printf("\n");

    return 0;
}
