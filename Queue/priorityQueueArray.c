#include <stdio.h>
#define SIZE 10

int values[SIZE];
int priority[SIZE];
int count = 0;

// ---------------------------------------------
// Insert element into priority queue
// ---------------------------------------------
void enqueue(int val, int pri) {
    if (count == SIZE) {
        printf("Queue Overflow!\n");
        return;
    }

    values[count] = val;
    priority[count] = pri;
    count++;
    printf("Inserted value %d with priority %d\n", val, pri);
}

// ---------------------------------------------
// Delete (highest priority first)
// ---------------------------------------------
void dequeue() {
    if (count == 0) {
        printf("Queue Underflow!\n");
        return;
    }

    // Find index of highest priority
    int highest = 0;
    for (int i = 1; i < count; i++) {
        if (priority[i] < priority[highest]) // smaller value = higher priority
            highest = i;
    }

    printf("Deleted value %d with priority %d\n", values[highest], priority[highest]);

    // Shift elements left
    for (int i = highest; i < count - 1; i++) {
        values[i] = values[i + 1];
        priority[i] = priority[i + 1];
    }
    count--;
}

// ---------------------------------------------
// Display queue
// ---------------------------------------------
void display() {
    if (count == 0) {
        printf("Queue is empty\n");
        return;
    }

    printf("Value\tPriority\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%d\n", values[i], priority[i]);
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

    dequeue();
    display();

    return 0;
}
