#include <stdio.h>
#include <stdlib.h>

// -------------------------------
// Node structure (no priority field)
// -------------------------------
struct Node {
    int data;
    struct Node* next;
};

// Global pointers for both versions
struct Node* front_unsorted = NULL;
struct Node* front_sorted = NULL;

// -------------------------------
// Create a new node
// -------------------------------
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// ======================================================
// ✅ 1️⃣  UNSORTED LINKED LIST IMPLEMENTATION
// ======================================================

// Enqueue → insert at end (unsorted)
void enqueueUnsorted(int data) {
    struct Node* newNode = createNode(data);

    if (front_unsorted == NULL) {
        front_unsorted = newNode;
        return;
    }

    struct Node* temp = front_unsorted;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

// Dequeue → remove element with MAX value
void dequeueUnsorted() {
    if (front_unsorted == NULL) {
        printf("Unsorted Queue Underflow!\n");
        return;
    }

    struct Node *temp = front_unsorted, *maxNode = front_unsorted;
    struct Node *prev = NULL, *prevMax = NULL;

    // Find node with max value
    while (temp != NULL) {
        if (temp->data > maxNode->data) {
            maxNode = temp;
            prevMax = prev;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("[Unsorted] Deleted element with highest priority: %d\n", maxNode->data);

    // Remove maxNode
    if (prevMax == NULL)
        front_unsorted = front_unsorted->next;
    else
        prevMax->next = maxNode->next;

    free(maxNode);
}

// Display unsorted queue
void displayUnsorted() {
    if (front_unsorted == NULL) {
        printf("[Unsorted] Queue is empty\n");
        return;
    }

    printf("[Unsorted] Queue elements: ");
    struct Node* temp = front_unsorted;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// ======================================================
// ✅ 2️⃣  SORTED LINKED LIST IMPLEMENTATION
// ======================================================

// Enqueue → insert in sorted descending order (largest first)
void enqueueSorted(int data) {
    struct Node* newNode = createNode(data);

    // If queue empty or new node has highest value
    if (front_sorted == NULL || data > front_sorted->data) {
        newNode->next = front_sorted;
        front_sorted = newNode;
        return;
    }

    struct Node* temp = front_sorted;
    while (temp->next != NULL && temp->next->data >= data)
        temp = temp->next;

    newNode->next = temp->next;
    temp->next = newNode;
}

// Dequeue → remove first element (highest priority)
void dequeueSorted() {
    if (front_sorted == NULL) {
        printf("Sorted Queue Underflow!\n");
        return;
    }

    struct Node* temp = front_sorted;
    printf("[Sorted] Deleted element with highest priority: %d\n", temp->data);
    front_sorted = front_sorted->next;
    free(temp);
}

// Display sorted queue
void displaySorted() {
    if (front_sorted == NULL) {
        printf("[Sorted] Queue is empty\n");
        return;
    }

    printf("[Sorted] Queue elements: ");
    struct Node* temp = front_sorted;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// ======================================================
// MAIN FUNCTION
// ======================================================
int main() {
    printf("=== Max Priority Queue using Linked List ===\n\n");

    // --------------------------
    // Unsorted version demo
    // --------------------------
    printf(">>> UNSORTED QUEUE DEMO <<<\n");
    enqueueUnsorted(10);
    enqueueUnsorted(5);
    enqueueUnsorted(30);
    enqueueUnsorted(20);
    displayUnsorted();

    dequeueUnsorted();
    displayUnsorted();

    enqueueUnsorted(50);
    displayUnsorted();

    dequeueUnsorted();
    displayUnsorted();

    printf("\n-------------------------------------------\n");

    // --------------------------
    // Sorted version demo
    // --------------------------
    printf(">>> SORTED QUEUE DEMO <<<\n");
    enqueueSorted(10);
    enqueueSorted(5);
    enqueueSorted(30);
    enqueueSorted(20);
    displaySorted();

    dequeueSorted();
    displaySorted();

    enqueueSorted(50);
    displaySorted();

    dequeueSorted();
    displaySorted();

    return 0;
}
