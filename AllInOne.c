#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Node{
    int key;
    int height;
    struct Node* left;
    struct Node* right;
};


struct Node* createNode(int key){
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    newNode->left=NULL;
    newNode->right=NULL;
    newNode->key=key;
    newNode->height=1;

    return newNode;
}


// stack for the operation needed
struct Stack{
    struct Node* arr[MAX];
    int top;
};

void initStack(struct Stack* s){
    s->top=-1;
}

int isEmptyStack(struct Stack* s){
    return s->top==-1;
}

struct Node* popStack(struct Stack *s){
    return s->arr[s->top--];
}

void pushStack(struct Stack *s, struct Node* node){
    s->arr[++(s->top)]=node;
}





// // Stack node for linked list
// struct StackNode {
//     struct Node* data;
//     struct StackNode* next;
// };

// // Stack structure
// struct Stack {
//     struct StackNode* top;
// };

// // Initialize stack
// void initStack(struct Stack* s){
//     s->top = NULL;
// }

// // Check if stack is empty
// int isEmptyStack(struct Stack* s){
//     return (s->top == NULL);
// }

// // Push a node onto stack
// void pushStack(struct Stack* s, struct Node* node){
//     struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
//     newNode->data = node;
//     newNode->next = s->top;
//     s->top = newNode;
// }

// // Pop a node from stack
// struct Node* popStack(struct Stack* s){
//     if(isEmptyStack(s)){
//         printf("Stack Empty\n");
//         return NULL;
//     }
//     struct StackNode* temp = s->top;
//     struct Node* val = temp->data;
//     s->top = s->top->next;
//     free(temp);
//     return val;
// }



// Queue for the bfs needed

struct Queue{
    struct Node* arr[MAX];
    int front;
    int rear;
};

void initQueue(struct Queue* q){
    q->front=0;
    q->rear=0;
}


void enqueue(struct Queue* q, struct Node* val){
    if(q->rear>=MAX){
        printf("queue overflow!!");
        return;
    }

    q->arr[q->rear++]=val;
}

struct Node* dequeue(struct Queue* q){
    if(q->front==q->rear){
        printf("Empty");
        return NULL;
    }

    return q->arr[q->front++];
}

int isEmptyQueue(struct Queue* q){
    if(q->front==q->rear){
        return 1;
    }

    return 0;
}




// // Queue node for linked list
// struct QueueNode {
//     struct Node* data;
//     struct QueueNode* next;
// };

// // Queue structure
// struct Queue {
//     struct QueueNode* front;
//     struct QueueNode* rear;
// };

// // Initialize the queue
// void initQueue(struct Queue* q){
//     q->front = NULL;
//     q->rear = NULL;
// }

// // Enqueue a node
// void enqueue(struct Queue* q, struct Node* val){
//     struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
//     newNode->data = val;
//     newNode->next = NULL;

//     if(q->rear == NULL){  // empty queue
//         q->front = q->rear = newNode;
//         return;
//     }

//     q->rear->next = newNode;
//     q->rear = newNode;
// }

// // Dequeue a node
// struct Node* dequeue(struct Queue* q){
//     if(q->front == NULL){
//         printf("Queue Empty\n");
//         return NULL;
//     }

//     struct QueueNode* temp = q->front;
//     struct Node* val = temp->data;
//     q->front = q->front->next;

//     if(q->front == NULL)  // queue became empty
//         q->rear = NULL;

//     free(temp);
//     return val;
// }

// // Check if queue is empty
// int isEmpty(struct Queue* q){
//     return (q->front == NULL);
// }

















// Helper Functions
int max(int a, int b){
    return (a>b?a:b);
}

int getHeight(struct Node* node){
    return node? node->height:0;
};


int findHeight(struct Node* node){
    if(node==NULL){
        return 0;
    }

    int leftHeight=findHeight(node->left);
    int rightHeight=findHeight(node->right);

    return 1+max(leftHeight, rightHeight);
}

int findDepth(struct Node* root, int key ,int currentDepth){
    if (root==NULL){
        return -1;
    }

    if(root->key==key){
        return currentDepth;
    }

    int left=findDepth(root->left, key, currentDepth+1);
    if(left!=-1){
        return left;
    }

    int right=findDepth(root->right, key, currentDepth+1);
    return right;
}


int getbalance(struct Node* root){
    return root? getHeight(root->left)-getHeight(root->right):0;
}



struct Node* rightRotate(struct Node* y){
    struct Node* x=y->left;
    struct Node* T2=x->right;

    x->right=y;
    y->left=T2;

    x->height=1+max(getHeight(x->left), getHeight(x->right));
    y->height=1+max(getHeight(y->left), getHeight(x->right));

    return x;
}


struct Node* leftRotate(struct Node* x){
    struct Node* y=x->right;
    struct Node* T2=y->left;

    y->left=x;
    x->right=T2;

    x->height=1+max(getHeight(x->right), getHeight(x->left));
    y->height=1+max(getHeight(y->left), getHeight(y->right));

    return y;
}


struct Node* balanceNode(struct Node* root){
    int balance=getbalance(root);

    //LL Case
    if(balance>1 && getbalance(root->left)>=0){
        return rightRotate(root);
    }

    // RR Case
    if(balance<-1 && getbalance(root->right)<=0){
        return leftRotate(root);
    }

    // LR case
    if(balance>1 && getBalacne(root->left)<0){
        root->left=leftRotate(root->left);
        return rightRotate(root);
    }

    //RL Case
    if(balance<-1 && getbalance(root->right)>0){
        root->right=rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


// inserting into a AVL tree
struct Node* insert(struct Node* root, int key){
    if(root==NULL){
        return createNode(key);
    }

    if(key<root->key){
        root->left=insert(root->left, key);
    }else if(key>root->key){
        root->right=insert(root->right, key);
    }else{
        printf("Duplicate not allowed!!");
        return root;
    }

    root->height=1+max(getHeight(root->left), getHeight(root->right));

    return balanceNode(root);
}


struct Node* small(struct Node* root){
    struct Node* curr=root;


    while(curr && curr->left!=NULL){
        curr=curr->left;
    }

    return curr;
}

struct Node* largest(struct Node* root){
    struct Node* curr=root;
    while(curr!=NULL && curr->right!=NULL){
        curr=curr->right;
    }
    return curr;
}


struct Node* deleteNode(struct Node* root, int key){
    if(root==NULL){
        return root;
    }

    if(key<root->key){
        root->left=deleteNode(root->left, key);
    }else if(key>root->key){
        root->right=deleteNode(root->right, key);
    }else{
        // Node is found

        if(root->left==NULL || root->right ){
            struct Node* temp=root->left?root->left:root->right;
            free(root);
            return temp;
        }

        // with successor
        struct Node* temp=small(root->right);
        root->key=temp->key;
        root->right=deleteNode(root->right, temp->key);
    }

    root->height=1+max(getHeight(root->left), getHeight(root->right));

    return balanceNode(root);
}



// recursive traverals
void inorderRec(struct Node *root){
    if(root==NULL){
        return;
    }

    inorderRec(root->left);
    printf("%d ", root->key);
    inorderRec(root->right);
}

void preorderRec(struct Node* root){
    if(root==NULL){
        return;
    }

    printf("\n%d ",root->key);
    preorderRec(root->left);
    preorderRec(root->right);
}

void postorderRec(struct Node* root){
    if(root==NULL){
        return;
    }

    postorderRec(root->left);
    postorderRec(root->right);
    printf("\n%d ", root->key);
}




// Iterative Traversals

void inorderIterative(struct Node* root){
    struct Stack s;
    initStack(&s);

    struct Node* curr=root;
    
    while(curr!=NULL || !isEmptyStack(&s)){
        while(curr!=NULL){
            pushStack(&s, curr);
            curr=curr->left;
        }
        curr=pop(&s);
        printf("\n%d ", curr->key);
        curr=curr->right;
    }
}



void preorderIterative(struct Node* root){
    if (root==NULL){
        return;
    }
    struct Stack s;
    initStack(&s);
        
    pushStack(&s, root);

    while(!isEmptyStack(&s)){
        struct Node* curr=popStack(&s);
        printf("\n%d ", curr->key);

        if(curr->right){
            pushStack(&s, curr->right);
        }
        if(curr->left){
            pushStack(&s, curr->left);
        }
    }
}




void postorderIterative(struct Node* root){
    if(root==NULL){
        return;
    }

    struct Stack s1,s2;
    initStack(&s1);
    initStack(&s2);

    pushStack(&s1, root);

    while(!isEmptyStack(&s1)){
        struct Node* curr=popStack(&s1);
        pushStack(&s2, curr);

        if(curr->left) pushStack(&s1, curr->left);
        if(curr->right) pushStack(&s1, curr->right);
    }

    while(!isEmptyStack(&s2)){
        printf("\n%d ", popStack(&s2)->key);
    }
}



//BFS/LevelOrder

void bfs(struct Node* root){
    if(root==NULL){
        return;
    }

    struct Queue q;
    initQueue(&q);

    enqueue(&q, root);

    while(!isEmptyQueue(&q)){
        struct Node* curr=dequeue(&q);
        printf("%d ", curr->key);
        if(curr->left) enqueue(&q, curr->left);
        if(curr->right) enqueue(&q, curr->right);
    }
}



int main() {
    struct Node* root = NULL;
    int n, key;

    // User input for tree nodes
    printf("Enter number of nodes to insert: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("Enter key for node %d: ", i + 1);
        scanf("%d", &key);
        root = insert(root, key);
    }

    printf("\nInorder traversal of AVL tree:\n");
    inorderRec(root);

    // Delete the root node
    if(root) {
        printf("\n\nDeleting the root node with key %d...\n", root->key);
        root = deleteNode(root, root->key);  // Delete root
    }

    printf("\nInorder traversal after deleting root:\n");
    inorderRec(root);

    return 0;
}

