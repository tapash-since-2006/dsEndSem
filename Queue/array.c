#include <stdio.h>
#include <stdlib.h>
#define MAX 5   // maximum size of queue

int queue[MAX];
int front = -1, rear = -1;

// Function to add element to the queue
void enqueue(int data) {
    if (rear == MAX - 1) {
        printf("Queue Overflow! Cannot insert %d\n", data);
        return;
    }
    if (front == -1)  // first element
        front = 0;

    rear++;
    queue[rear] = data;
    printf("%d inserted into queue.\n", data);
}

// Function to remove element from the queue
void dequeue() {
    if (front == -1 || front > rear) {
        printf("Queue Underflow! Nothing to delete.\n");
        return;
    }
    printf("%d deleted from queue.\n", queue[front]);
    front++;

    // Reset when queue becomes empty
    if (front > rear)
        front = rear = -1;
}

// Function to return front element
void peek() {
    if (front == -1)
        printf("Queue is empty.\n");
    else
        printf("Front element: %d\n", queue[front]);
}

// Function to display the queue
void display() {
    if (front == -1)
        printf("Queue is empty.\n");
    else {
        printf("Queue elements: ");
        for (int i = front; i <= rear; i++)
            printf("%d ", queue[i]);
        printf("\n");
    }
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
