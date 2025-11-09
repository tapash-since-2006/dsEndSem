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

void enqueue(struct Queue* q, struct Node* val) {
    if (q->rear >= MAX) {
        printf("Queue overflow!!\n");
        return;
    }
    q->arr[q->rear++] = val;
}

struct Node* dequeue(struct Queue* q) {
    if (q->front == q->rear) {
        printf("Queue underflow!!\n");
        return NULL;
    }
    return q->arr[q->front++];
}

int isEmptyQueue(struct Queue* q) {
    return q->front == q->rear;
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

    while (!isEmptyQueue(&q)) {
        struct Node* temp = dequeue(&q);
        printf("Dequeued: %d\n", temp->data);
    }

    dequeue(&q);

    return 0;
}
