// #include <stdio.h>
// #include <stdlib.h>
// #define NUM_QUEUES 3   // total number of queues

// // ----------------------------------------------------
// // Structure for a node (each element in a linked queue)
// // ----------------------------------------------------
// struct Node {
//     int data;              // value of the element
//     struct Node* next;     // pointer to next node
// };

// // ----------------------------------------------------
// // Structure representing ONE queue
// // Each queue has its own front and rear pointers
// // ----------------------------------------------------
// struct Queue {
//     struct Node* front;   // points to first node
//     struct Node* rear;    // points to last node
// };

// // ----------------------------------------------------
// // Declare an array of queues
// // Example: q[0], q[1], q[2]
// // ----------------------------------------------------
// struct Queue q[NUM_QUEUES];

// // ----------------------------------------------------
// // Initialize all queues (make them empty)
// // ----------------------------------------------------
// void initializeQueues() {
//     for (int i = 0; i < NUM_QUEUES; i++) {
//         q[i].front = NULL;
//         q[i].rear = NULL;
//     }
// }

// // ----------------------------------------------------
// // ENQUEUE — add element to the rear of a specific queue
// // ----------------------------------------------------
// void enqueue(int i, int value) {
//     if (i < 0 || i >= NUM_QUEUES) {
//         printf("Invalid queue number %d!\n", i);
//         return;
//     }

//     // Create a new node dynamically
//     struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
//     newNode->data = value;
//     newNode->next = NULL;

//     // If queue is empty, front and rear both point to new node
//     if (q[i].rear == NULL) {
//         q[i].front = q[i].rear = newNode;
//     } else {
//         // Link the new node at the end and move rear pointer
//         q[i].rear->next = newNode;
//         q[i].rear = newNode;
//     }

//     printf("Inserted %d into Queue %d\n", value, i);
// }

// // ----------------------------------------------------
// // DEQUEUE — remove element from the front of a queue
// // ----------------------------------------------------
// void dequeue(int i) {
//     if (i < 0 || i >= NUM_QUEUES) {
//         printf("Invalid queue number %d!\n", i);
//         return;
//     }

//     if (q[i].front == NULL) {
//         printf("Queue %d Underflow! Nothing to delete.\n", i);
//         return;
//     }

//     struct Node* temp = q[i].front;
//     printf("Deleted %d from Queue %d\n", temp->data, i);

//     q[i].front = q[i].front->next;

//     // If queue becomes empty, reset rear to NULL
//     if (q[i].front == NULL)
//         q[i].rear = NULL;

//     free(temp);
// }

// // ----------------------------------------------------
// // DISPLAY — show all elements of a specific queue
// // ----------------------------------------------------
// void display(int i) {
//     if (i < 0 || i >= NUM_QUEUES) {
//         printf("Invalid queue number %d!\n", i);
//         return;
//     }

//     if (q[i].front == NULL) {
//         printf("Queue %d is empty.\n", i);
//         return;
//     }

//     printf("Queue %d elements: ", i);
//     struct Node* temp = q[i].front;
//     while (temp != NULL) {
//         printf("%d ", temp->data);
//         temp = temp->next;
//     }
//     printf("\n");
// }

// // ----------------------------------------------------
// // MAIN — Demonstrate Multiple Linked List Queues
// // ----------------------------------------------------
// int main() {
//     initializeQueues();

//     enqueue(0, 10);
//     enqueue(0, 20);
//     enqueue(1, 100);
//     enqueue(1, 200);
//     enqueue(1, 300);
//     enqueue(2, 999);

//     printf("\nDisplaying all queues:\n");
//     for (int i = 0; i < NUM_QUEUES; i++)
//         display(i);

//     printf("\nDequeue some elements:\n");
//     dequeue(0);
//     dequeue(1);

//     printf("\nAfter Deletion:\n");
//     for (int i = 0; i < NUM_QUEUES; i++)
//         display(i);

//     return 0;
// }





// // Array Represetation

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 5   // maximum elements in each queue
#define NUM_QUEUES 3 // total number of queues

// ---------------------------------------------
// Structure to represent ONE queue
// ---------------------------------------------
struct Queue {
    int items[MAX_SIZE];  // array to hold elements
    int front;            // index of front element
    int rear;             // index of last element
};

// ---------------------------------------------
// Declare an array of Queue structures
// ---------------------------------------------
//
// We are creating NUM_QUEUES separate queues.
// Example: queue[0], queue[1], queue[2] ...
//
struct Queue q[NUM_QUEUES];

// ---------------------------------------------
// Initialize all queues
// ---------------------------------------------
void initializeQueues() {
    for (int i = 0; i < NUM_QUEUES; i++) {
        q[i].front = -1;
        q[i].rear = -1;
    }
}

// ---------------------------------------------
// Function to check if a specific queue is full
// ---------------------------------------------
int isFull(int i) {
    return q[i].rear == MAX_SIZE - 1;
}

// ---------------------------------------------
// Function to check if a specific queue is empty
// ---------------------------------------------
int isEmpty(int i) {
    return q[i].front == -1 || q[i].front > q[i].rear;
}

// ---------------------------------------------
// Enqueue operation for specific queue
// ---------------------------------------------
void enqueue(int i, int value) {
    if (i < 0 || i >= NUM_QUEUES) {
        printf("Invalid queue number %d!\n", i);
        return;
    }

    if (isFull(i)) {
        printf("Queue %d Overflow!\n", i);
        return;
    }

    if (q[i].front == -1) // first element
        q[i].front = 0;

    q[i].rear++;
    q[i].items[q[i].rear] = value;
    printf("Inserted %d into Queue %d\n", value, i);
}

// ---------------------------------------------
// Dequeue operation for specific queue
// ---------------------------------------------
void dequeue(int i) {
    if (i < 0 || i >= NUM_QUEUES) {
        printf("Invalid queue number %d!\n", i);
        return;
    }

    if (isEmpty(i)) {
        printf("Queue %d Underflow!\n", i);
        return;
    }

    printf("Deleted %d from Queue %d\n", q[i].items[q[i].front], i);
    q[i].front++;

    if (q[i].front > q[i].rear)
        q[i].front = q[i].rear = -1; // queue empty again
}

// ---------------------------------------------
// Display specific queue
// ---------------------------------------------
void display(int i) {
    if (i < 0 || i >= NUM_QUEUES) {
        printf("Invalid queue number %d!\n", i);
        return;
    }

    if (isEmpty(i)) {
        printf("Queue %d is empty.\n", i);
        return;
    }

    printf("Queue %d elements: ", i);
    for (int j = q[i].front; j <= q[i].rear; j++)
        printf("%d ", q[i].items[j]);
    printf("\n");
}

// ---------------------------------------------
// MAIN: Example usage of multiple queues
// ---------------------------------------------
int main() {
    initializeQueues();

    enqueue(0, 10);
    enqueue(0, 20);
    enqueue(1, 100);
    enqueue(1, 200);
    enqueue(2, 1000);

    printf("\nDisplaying all queues:\n");
    for (int i = 0; i < NUM_QUEUES; i++)
        display(i);

    printf("\nDequeue from Queue 0 and Queue 1:\n");
    dequeue(0);
    dequeue(1);

    printf("\nAfter Deletion:\n");
    for (int i = 0; i < NUM_QUEUES; i++)
        display(i);

    return 0;
}
