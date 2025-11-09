// #include <stdio.h>
// #define SIZE 10

// int deque[SIZE];
// int front = -1, rear = -1;

// // ---------------------------------------------
// // Check if deque is full
// // ---------------------------------------------
// int isFull() {
//     return (rear == SIZE - 1);
// }

// // ---------------------------------------------
// // Check if deque is empty
// // ---------------------------------------------
// int isEmpty() {
//     return (front == -1 || front > rear);
// }

// // ---------------------------------------------
// // Insert at REAR end
// // ---------------------------------------------
// void insertRear(int value) {
//     if (isFull()) {
//         printf("Deque Overflow! Cannot insert %d at rear.\n", value);
//         return;
//     }

//     if (front == -1) // first element
//         front = 0;

//     rear++;
//     deque[rear] = value;
//     printf("Inserted %d at REAR\n", value);
// }

// // ---------------------------------------------
// // Insert at FRONT end
// // ---------------------------------------------
// void insertFront(int value) {
//     if (front <= 0) {
//         if (front == -1 && rear == -1) {
//             front = rear = 0;
//             deque[front] = value;
//             printf("Inserted %d at FRONT (first element)\n", value);
//         } else {
//             printf("No space at FRONT to insert %d.\n", value);
//         }
//         return;
//     }

//     front--;
//     deque[front] = value;
//     printf("Inserted %d at FRONT\n", value);
// }

// // ---------------------------------------------
// // Delete from FRONT end
// // ---------------------------------------------
// void deleteFront() {
//     if (isEmpty()) {
//         printf("Deque Underflow! Nothing to delete at front.\n");
//         return;
//     }

//     printf("Deleted %d from FRONT\n", deque[front]);
//     front++;

//     if (front > rear)
//         front = rear = -1; // reset when empty
// }

// // ---------------------------------------------
// // Delete from REAR end
// // ---------------------------------------------
// void deleteRear() {
//     if (isEmpty()) {
//         printf("Deque Underflow! Nothing to delete at rear.\n");
//         return;
//     }

//     printf("Deleted %d from REAR\n", deque[rear]);
//     rear--;

//     if (front > rear)
//         front = rear = -1;
// }

// // ---------------------------------------------
// // Display elements in deque
// // ---------------------------------------------
// void display() {
//     if (isEmpty()) {
//         printf("Deque is empty.\n");
//         return;
//     }

//     printf("Deque elements: ");
//     for (int i = front; i <= rear; i++) {
//         printf("%d ", deque[i]);
//     }
//     printf("\n");
// }

// // ---------------------------------------------
// // MAIN FUNCTION
// // ---------------------------------------------
// int main() {
//     insertRear(10);
//     insertRear(20);
//     insertRear(30);
//     insertFront(5);  // won't work here (no free space on left yet)
//     display();

//     deleteFront();
//     insertFront(5);  // now it works
//     display();

//     deleteRear();
//     display();

//     insertRear(40);
//     insertRear(50);
//     display();

//     return 0;
// }



// doubly ended queue with linkedList

#include <stdio.h> 
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next;
};

struct Node* front=NULL;
struct Node* rear=NULL;

struct Node* createNode(int data){
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    newNode->next=NULL;
    newNode->data=data;
    return newNode;
}

void insertFront(int data){
    struct Node* newNode=createNode(data);
    if(front==NULL){
        front=rear=newNode;
        return;
    }

    newNode->next=front;
    front=newNode;
}


void insertRear(int data){

    struct Node* newNode=createNode(data);

    if(rear==NULL){
        front=rear=newNode;
        return;
    }
    rear->next=newNode;
    rear=newNode;
}


void deleteRear(){
    if(rear==NULL){
        printf("Cannot be deleted from an empty Queue");
        return;
    }

    struct Node* curr=front;

    if(front==rear){
        front=rear=NULL;
        return;
    }

    while(curr->next!=NULL && curr->next->next!=NULL){
        curr=curr->next;
    }

    struct Node* temp=rear;
    rear=curr;
    rear->next=NULL; // important line beacuse it will become the last hence it next must point to null never forget this otherwise overflow problem will occur
    free(temp);
}


void deleteFront(){
    if(front==NULL){
        printf("No eleemnt to be deleted!!");
        return;
    }

    struct Node* temp=front;
    front=front->next;
    free(temp);

    if(front==NULL){
        front=rear=NULL;
    }
}


void display(){
    printf("The queue is : ");

    if(front==NULL){
        printf("The queue is empty");
    }

    struct Node* temp=front;

    while(temp!=NULL){
        printf("%d", temp->data);
        temp=temp->next;
    }
}


int main(){
    insertFront(1);
    insertFront(2);
    insertFront(3);

    display();

    insertFront(4);
    insertFront(5);

    display();

    deleteRear();
    deleteRear();

    display();

    deleteFront();
    deleteFront();

    display();

    return 0;

}