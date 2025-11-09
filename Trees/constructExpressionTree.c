#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>   // for isdigit(), isalpha()

// ---------------------------
// Node Structure
// ---------------------------
struct Node {
    char data[10];         // to store numbers or operators
    struct Node *left, *right;
};

// ---------------------------
// Stack for Tree Nodes
// ---------------------------
struct Stack {
    struct Node* arr[100];
    int top;
};

void initStack(struct Stack* s) {
    s->top = -1;
}

int isEmpty(struct Stack* s) {
    return s->top == -1;
}

void push(struct Stack* s, struct Node* node) {
    s->arr[++(s->top)] = node;
}

struct Node* pop(struct Stack* s) {
    if (isEmpty(s)) return NULL;
    return s->arr[(s->top)--];
}

// ---------------------------
// Node Creation
// ---------------------------
struct Node* createNode(char* data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->data, data);
    newNode->left = newNode->right = NULL;
    return newNode;
}

// ---------------------------
// Utility Functions
// ---------------------------
int isOperator(char* c) {
    return (strlen(c) == 1 && strchr("+-*/^", c[0]) != NULL);
}

// ---------------------------
// 1️⃣ Build from Postfix
// ---------------------------
struct Node* buildFromPostfix(char* postfix[]) {
    struct Stack s;
    initStack(&s);

    for (int i = 0; postfix[i] != NULL; i++) {
        char* token = postfix[i];
        struct Node* node = createNode(token);

        if (!isOperator(token)) {
            push(&s, node);
        } else {
            node->right = pop(&s);
            node->left = pop(&s);
            push(&s, node);
        }
    }
    return pop(&s);
}

// ---------------------------
// 2️⃣ Build from Prefix
// ---------------------------
struct Node* buildFromPrefix(char* prefix[], int n) {
    struct Stack s;
    initStack(&s);

    for (int i = n - 1; i >= 0; i--) {
        char* token = prefix[i];
        struct Node* node = createNode(token);

        if (!isOperator(token)) {
            push(&s, node);
        } else {
            node->left = pop(&s);
            node->right = pop(&s);
            push(&s, node);
        }
    }
    return pop(&s);
}

// ---------------------------
// 3️⃣ Build from Infix
// ---------------------------
// To build from infix, we must first convert infix ➜ postfix.
int precedence(char op) {
    switch (op) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}

int isLeftAssoc(char op) {
    return op != '^'; // ^ is right-associative
}

void infixToPostfix(char* infix[], char* postfix[]) {
    char* stack[100];
    int top = -1, k = 0;

    for (int i = 0; infix[i] != NULL; i++) {
        char* token = infix[i];

        if (!isOperator(token) && strcmp(token, "(") && strcmp(token, ")")) {
            postfix[k++] = token;
        }
        else if (strcmp(token, "(") == 0) {
            stack[++top] = token;
        }
        else if (strcmp(token, ")") == 0) {
            while (top >= 0 && strcmp(stack[top], "(") != 0) {
                postfix[k++] = stack[top--];
            }
            top--;
        }
        else {
            while (top >= 0 && precedence(stack[top][0]) >= precedence(token[0]) && isLeftAssoc(token[0])) {
                postfix[k++] = stack[top--];
            }
            stack[++top] = token;
        }
    }
    while (top >= 0)
        postfix[k++] = stack[top--];

    postfix[k] = NULL;
}

struct Node* buildFromInfix(char* infix[]) {
    char* postfix[100];
    infixToPostfix(infix, postfix);
    return buildFromPostfix(postfix);
}

// ---------------------------
// Traversals
// ---------------------------
void inorder(struct Node* root) {
    if (!root) return;
    if (isOperator(root->data))
        printf("(");
    inorder(root->left);
    printf("%s", root->data);
    inorder(root->right);
    if (isOperator(root->data))
        printf(")");
}

void preorder(struct Node* root) {
    if (!root) return;
    printf("%s ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%s ", root->data);
}

// ---------------------------
// Main Function
// ---------------------------
int main() {
    // Example postfix expression: "a b + c d - *"
    char* postfixExp[] = {"a", "b", "+", "c", "d", "-", "*", NULL};
    char* prefixExp[]  = {"*", "+", "a", "b", "-", "c", "d", NULL};
    char* infixExp[]   = {"(", "a", "+", "b", ")", "*", "(", "c", "-", "d", ")", NULL};

    printf("\n--- Build from Postfix ---\n");
    struct Node* postRoot = buildFromPostfix(postfixExp);
    printf("Infix: "); inorder(postRoot); printf("\n");

    printf("\n--- Build from Prefix ---\n");
    struct Node* preRoot = buildFromPrefix(prefixExp, 7);
    printf("Infix: "); inorder(preRoot); printf("\n");

    printf("\n--- Build from Infix ---\n");
    struct Node* inRoot = buildFromInfix(infixExp);
    printf("Infix: "); inorder(inRoot); printf("\n");

    return 0;
}
