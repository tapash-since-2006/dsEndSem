#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Node {
    int data;
};

struct Queue {
    struct Node* arr[MAX];
    int front;
    int rear;
};

void initQueue(struct Queue* q) {
    q->front = 0;
    q->rear = 0;
}

int isEmpty(struct Queue* q) {
    return q->front == q->rear;
}

int isFull(struct Queue* q) {
    return q->rear >= MAX;
}

void enqueue(struct Queue* q, struct Node* val) {
    if (isFull(q)) {
        printf("Queue overflow!!\n");
        return;
    }
    q->arr[q->rear++] = val;
}

struct Node* dequeue(struct Queue* q) {
    if (isEmpty(q)) {
        printf("Queue underflow!!\n");
        return NULL;
    }
    return q->arr[q->front++];
}
  
void displayQueue(struct Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = q->front; i < q->rear; i++)
        printf("%d ", q->arr[i]->data);
    printf("\n");
}

int main() {
    struct Queue q;
    initQueue(&q);

    struct Node a = {10};
    struct Node b = {20};
    struct Node c = {30};

    enqueue(&q, &a);
    enqueue(&q, &b);
    enqueue(&q, &c);

    displayQueue(&q);

    struct Node* temp = dequeue(&q);
    if (temp) printf("Dequeued: %d\n", temp->data);

    displayQueue(&q);

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