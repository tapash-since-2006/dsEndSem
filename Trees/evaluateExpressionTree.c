#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  // for isdigit()

struct Node {
    char data[10]; // to allow multi-digit numbers
    struct Node *left, *right;
};

// Function to create a new node
struct Node* createNode(char* data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    strcpy(newNode->data, data);
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Recursive function to create a binary expression tree
struct Node* createTree() {
    char data[10];
    char hasLeft, hasRight;

    printf("Enter node data (operator or number): ");
    scanf("%s", data);

    struct Node* root = createNode(data);

    // If this is not a number (i.e., an operator), it must have children
    if (!(isdigit(data[0]) || (data[0] == '-' && isdigit(data[1])))) {
        printf("Does '%s' have a left child? (y/n): ", data);
        scanf(" %c", &hasLeft);
        if (hasLeft == 'y' || hasLeft == 'Y')
            root->left = createTree();

        printf("Does '%s' have a right child? (y/n): ", data);
        scanf(" %c", &hasRight);
        if (hasRight == 'y' || hasRight == 'Y')
            root->right = createTree();
    }

    return root;
}

// Evaluate expression tree recursively
double evaluate(struct Node* root) {
    if (root == NULL)
        return 0;

    // If leaf node → return number
    if (root->left == NULL && root->right == NULL)
        return atof(root->data); // convert string to double

    // Otherwise evaluate left and right
    double leftVal = evaluate(root->left);
    double rightVal = evaluate(root->right);

    switch (root->data[0]) {
        case '+': return leftVal + rightVal;
        case '-': return leftVal - rightVal;
        case '*': return leftVal * rightVal;
        case '/': 
            if (rightVal == 0) {
                printf("Error: Division by zero!\n");
                exit(1);
            }
            return leftVal / rightVal;
        default:
            printf("Invalid operator: %s\n", root->data);
            exit(1);
    }
}

// Inorder traversal (for infix form)
void inorder(struct Node* root) {
    if (root == NULL)
        return;

    if (root->left && root->right)
        printf("(");
    
    inorder(root->left);
    printf("%s", root->data);
    inorder(root->right);

    if (root->left && root->right)
        printf(")");
}

int main() {
    printf("Create the binary expression tree:\n");
    struct Node* root = createTree();

    printf("\nInfix Expression: ");
    inorder(root);

    double result = evaluate(root);
    printf("\nResult: %.2f\n", result);

    return 0;
}
