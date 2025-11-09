#include <stdio.h>
#include <stdlib.h>

struct Node {
    char data;
    struct Node *left, *right;
};

// Function to create a new node
struct Node* createNode(char data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Recursive function to create a binary expression tree
struct Node* createTree() {
    char data;
    char hasLeft, hasRight;

    printf("Enter node data: ");
    scanf(" %c", &data);

    struct Node* root = createNode(data);

    printf("Does '%c' have a left child? (y/n): ", data);
    scanf(" %c", &hasLeft);
    if (hasLeft == 'y' || hasLeft == 'Y')
        root->left = createTree();

    printf("Does '%c' have a right child? (y/n): ", data);
    scanf(" %c", &hasRight);
    if (hasRight == 'y' || hasRight == 'Y')
        root->right = createTree();

    return root;
}

// Inorder (Infix) Traversal
void inorder(struct Node* root) {
    if (root == NULL)
        return;

    if (root->left != NULL && root->right != NULL)
        printf("(");

    inorder(root->left);
    printf("%c", root->data);
    inorder(root->right);

    if (root->left != NULL && root->right != NULL)
        printf(")");
}

// Preorder (Prefix) Traversal
void preorder(struct Node* root) {
    if (root == NULL)
        return;

    printf("%c", root->data);
    preorder(root->left);
    preorder(root->right);
}

// Postorder (Postfix) Traversal
void postorder(struct Node* root) {
    if (root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);
    printf("%c", root->data);
}

int main() {
    printf("Create the binary expression tree:\n");
    struct Node* root = createTree();

    printf("\nInfix Expression: ");
    inorder(root);

    printf("\nPrefix Expression: ");
    preorder(root);

    printf("\nPostfix Expression: ");
    postorder(root);

    printf("\n");

    return 0;
}

