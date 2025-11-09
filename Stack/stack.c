#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Node {
    int data;
};

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

void pushStack(struct Stack *s, struct Node* node){
    if(s->top==MAX-1){
        printf("Stack overflow!!\n");
        return;
    }
    s->arr[++(s->top)]=node;
}

struct Node* popStack(struct Stack *s){
    if(isEmptyStack(s)){
        printf("Stack underflow!!\n");
        return NULL;
    }
    return s->arr[s->top--];
}

void displayStack(struct Stack* s){
    if(isEmptyStack(s)){
        printf("Stack is empty\n");
        return;
    }

    printf("Stack: ");
    for(int i=s->top;i>=0;i--){
        printf("%d ", s->arr[i]->data);
    }
    printf("\n");
}

int main(){
    struct Stack s;
    initStack(&s);

    struct Node a={10};
    struct Node b={20};
    struct Node c={30};

    pushStack(&s,&a);
    pushStack(&s,&b);
    pushStack(&s,&c);

    displayStack(&s);

    popStack(&s);
    displayStack(&s);

    popStack(&s);
    popStack(&s);
    displayStack(&s);
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

// // Display stack
// void displayStack(struct Stack* s){
//     if(isEmptyStack(s)){
//         printf("Stack is empty\n");
//         return;
//     }
//     struct StackNode* temp = s->top;
//     printf("Stack: ");
//     while(temp!=NULL){
//         printf("%d ", temp->data->data);
//         temp=temp->next;
//     }
//     printf("\n");
// }
