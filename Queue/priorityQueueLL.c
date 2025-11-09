#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    int priority;
    struct Node* next;
};

struct Node* front = NULL;

// ---------------------------------------------
// Create new node
// ---------------------------------------------
struct Node* newNode(int d, int p) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = d;
    temp->priority = p;
    temp->next = NULL;
    return temp;
}

// ---------------------------------------------
// Enqueue by priority
// ---------------------------------------------
void enqueue(int data, int priority) {
    struct Node* temp = newNode(data, priority);

    // if queue empty or new node has higher priority (smaller number)
    if (front == NULL || priority < front->priority) {
        temp->next = front;
        front = temp;
    } else {
        struct Node* start = front;

        // traverse until we find correct position
        while (start->next != NULL && start->next->priority <= priority)
            start = start->next;

        temp->next = start->next;
        start->next = temp;
    }

    printf("Inserted %d with priority %d\n", data, priority);
}

// ---------------------------------------------
// Dequeue (front element = highest priority)
// ---------------------------------------------
void dequeue() {
    if (front == NULL) {
        printf("Queue Underflow!\n");
        return;
    }

    struct Node* temp = front;
    printf("Deleted %d with priority %d\n", temp->data, temp->priority);
    front = front->next;
    free(temp);
}

// ---------------------------------------------
// Display queue
// ---------------------------------------------
void display() {
    if (front == NULL) {
        printf("Queue is empty\n");
        return;
    }

    printf("Value\tPriority\n");
    struct Node* temp = front;
    while (temp != NULL) {
        printf("%d\t%d\n", temp->data, temp->priority);
        temp = temp->next;
    }
}

// ---------------------------------------------
int main() {
    enqueue(10, 3);
    enqueue(20, 1);
    enqueue(30, 2);
    display();

    dequeue();
    display();

    enqueue(40, 0);
    display();

    return 0;
}
