#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Node {
    int data;
};

struct Deque {
    struct Node* arr[MAX];
    int front;
    int rear;
};

void initDeque(struct Deque* dq) {
    dq->front = 0;
    dq->rear = 0;
}

int isEmpty(struct Deque* dq) {
    return dq->front == dq->rear;
}

int isFull(struct Deque* dq) {
    return dq->rear >= MAX;
}

void insertRear(struct Deque* dq, struct Node* val) {
    if (isFull(dq)) {
        printf("Deque overflow at REAR!!\n");
        return;
    }
    dq->arr[dq->rear++] = val;
}

void insertFront(struct Deque* dq, struct Node* val) {
    if (dq->front == 0) {
        if (dq->rear >= MAX) {
            printf("Deque overflow at FRONT!!\n");
            return;
        }
        // Shift elements right to make space at front
        for (int i = dq->rear; i > dq->front; i--)
            dq->arr[i] = dq->arr[i - 1];
        dq->rear++;
    } else {
        dq->front--;
    }
    dq->arr[dq->front] = val;
}

struct Node* deleteFront(struct Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque underflow at FRONT!!\n");
        return NULL;
    }
    return dq->arr[dq->front++];
}

struct Node* deleteRear(struct Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque underflow at REAR!!\n");
        return NULL;
    }
    return dq->arr[--dq->rear];
}

void displayDeque(struct Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty!\n");
        return;
    }
    printf("Deque elements: ");
    for (int i = dq->front; i < dq->rear; i++)
        printf("%d ", dq->arr[i]->data);
    printf("\n");
}

int main() {
    struct Deque dq;
    initDeque(&dq);

    struct Node a = {10};
    struct Node b = {20};
    struct Node c = {30};
    struct Node d = {40};

    insertRear(&dq, &a);
    insertRear(&dq, &b);
    insertFront(&dq, &c);
    insertRear(&dq, &d);

    displayDeque(&dq);

    struct Node* temp = deleteFront(&dq);
    if (temp) printf("Deleted from front: %d\n", temp->data);

    temp = deleteRear(&dq);
    if (temp) printf("Deleted from rear: %d\n", temp->data);

    displayDeque(&dq);

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


// void displayQueue(struct Queue* q) {
//     if (q->front == NULL) {
//         printf("Queue is empty!\n");
//         return;
//     }

//     printf("Queue elements: ");
//     struct QueueNode* temp = q->front;
//     while (temp != NULL) {
//         printf("%d ", temp->data->data);
//         temp = temp->next;
//     }
//     printf("\n");
// }
