// //deque using the array represetnation

// #include <stdio.h>
// #include <stdlib.h>
// #define SIZE 100

// int arr[SIZE];
// int front=0;
// int rear=0;


// int isFull(){
//     if (rear>=SIZE){
//         return 1;
//     }

//     return 0;
// }

// int isEmpty(){
//     return front==rear;
// }


// void insertRear(int data){
//     if(isFull()){
//         printf("cannot enter to a full queueu");
//         return;
//     }
//     arr[rear++]=data;
// }


// void insertFront(int data){
//     if(rear>=SIZE){
//         printf("Full cannot be added");
//         return;
//     }

//     if(front>0){ // space available at the frot
//         front--;
//         arr[front]=data;
//         return;
//     }

//     // else shifting will be needed

//     for(int i=rear;i>front;i--){
//         arr[i]=arr[i-1];
//     }

//     arr[front]=data;
//     rear++;// important to increment the value of the rear as the size increased
// }


// int removeFront(){
//     if(isEmpty()){
//         return -1;
//     }

//     int val=arr[front++];
//     if(front==rear){
//         front=rear=0; // i.e the queue has become empty;
//     }

//     return val;
// }


// int removeRear(){
//     if(isEmpty()){
//         return -1;
//     }

//     int val=arr[--rear];
//     if(front==rear){
//         front=rear=0;
//     }
//     return val;
// }



// void displayQueue(){
//     if(isEmpty()){
//         printf("queue is empty");
//         return;
//     }

//     for(int i=front; i<rear; i++){
//         printf("%d", arr[i]);
//     }

// }



//dequeu using linkedlist


#include <stdio.h>
#include <stdlib.h>

struct Node{
    int val;
    struct Node* next;
};

struct Node* createNode(int data){
    struct Node* newNode=(struct Node*) malloc(sizeof(struct Node));
    newNode->val=data;
    newNode->next=NULL;
    return newNode;
}

struct Node* front=NULL;
struct Node* rear=NULL;

int isEmpty(){
    if(rear==NULL){
        return 1;
    }

    return 0;
}


void insertRear(int data){
    if(isEmpty()){
        front=rear=createNode(data);
        return;
    }


    rear->next=createNode(data);
    rear=rear->next;
}


void insertFront(int data){
    if(isEmpty()){
        front=rear=createNode(data);
        return;
    }

    struct Node* temp=createNode(data);
    temp->next=front;
    front=temp;
}

int deleteFront(){
    if(isEmpty()){
        return -1;
    }

    struct Node* temp=front;
    if(front==rear){
        front=rear=NULL;
        int val=temp->val;
        free(temp);
        return val;
    }

    front=front->next;
    int val=temp->val;
    free(temp);
    return val;
}


int deleteRear(){
    if(isEmpty()){
        return -1;
    }

    struct Node* temp=front;
    if(front==rear){
        front=rear=NULL;
        int val=temp->val;
        free(temp);
        return val;
    }

    struct Node* curr=front;
    struct Node* prev=NULL;

    while(curr!=NULL && curr->next!=NULL){
        prev=curr;
        curr=curr->next;
    }

    int val=curr->val;
    rear=prev;
    rear->next=NULL; // important case to detach otherwise will fail 
    free(curr);
    return val;
}


void display(){
    if(front==NULL){
        return;
    }
    struct Node* temp=front;

    while(temp!=NULL){
        printf("%d", temp->val);
        temp=temp->next;
    }

    
}