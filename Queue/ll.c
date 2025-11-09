#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
};

// Queue with front and rear pointers
struct Node *front = NULL, *rear = NULL;

// Function to add element to queue
void enqueue(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (rear == NULL) {  // first element
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    printf("%d inserted into queue.\n", data);
}

// Function to remove element from queue
void dequeue() {
    if (front == NULL) {
        printf("Queue Underflow! Nothing to delete.\n");
        return;
    }

    struct Node* temp = front;
    printf("%d deleted from queue.\n", front->data);
    front = front->next;

    if (front == NULL)  // queue became empty
        rear = NULL;

    free(temp);
}

// Function to get front element
void peek() {
    if (front == NULL)
        printf("Queue is empty.\n");
    else
        printf("Front element: %d\n", front->data);
}

// Function to display queue
void display() {
    if (front == NULL) {
        printf("Queue is empty.\n");
        return;
    }

    struct Node* temp = front;
    printf("Queue elements: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    display();
    dequeue();
    peek();
    display();
    return 0;
}
