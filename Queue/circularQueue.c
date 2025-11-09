#include <stdio.h>
#include <stdlib.h>

#define size 100

int arr[size];
int front = -1;
int rear = -1;

int isFull() {
    return ((rear + 1) % size == front);
}

int isEmpty() {
    return (front == -1);
}

void enqueue(int data) {
    if (isFull()) {
        printf("The circular queue is full\n");
        return;
    }

    if (front == -1) {
        front = 0;
    }

    rear = (rear + 1) % size;
    arr[rear] = data;
    printf("Enqueued: %d\n", data);
}

int dequeue() {
    if (isEmpty()) {
        printf("Cannot remove from an empty circular queue\n");
        return -1;
    }

    int popped = arr[front];

    if (front == rear) {
        front = rear = -1;
    } else {
        front = (front + 1) % size;
    }

    return popped;
}

void display() {
    if (isEmpty()) {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue elements: ");
    int i = front;
    while (1) {
        printf("%d ", arr[i]);
        if (i == rear)
            break;
        i = (i + 1) % size;
    }
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    display();

    printf("Dequeued: %d\n", dequeue());
    display();

    printf("Dequeued: %d\n", dequeue());
    display();

    enqueue(40);
    enqueue(50);
    display();

    printf("Dequeued: %d\n", dequeue());
    display();

    return 0;
}
