// #include <stdio.h>
// #define SIZE 10

// // ===============================
// // APPROACH 1: Insert in sorted order
// // ===============================
// int sortedPQ[SIZE];
// int sortedSize = 0;

// void insertSorted(int value) {
//     if (sortedSize == SIZE) {
//         printf("[SortedPQ] Queue Overflow!\n");
//         return;
//     }

//     int i = sortedSize - 1;
//     // Shift larger elements to the right
//     while (i >= 0 && sortedPQ[i] > value) {
//         sortedPQ[i + 1] = sortedPQ[i];
//         i--;
//     }

//     // Insert at correct position
//     sortedPQ[i + 1] = value;
//     sortedSize++;

//     printf("[SortedPQ] Inserted %d\n", value);
// }

// int deleteMinSorted() {
//     if (sortedSize == 0) {
//         printf("[SortedPQ] Queue Underflow!\n");
//         return -1;
//     }

//     int minElement = sortedPQ[0]; // smallest is at curr

//     // Shift elements left
//     for (int i = 0; i < sortedSize - 1; i++) {
//         sortedPQ[i] = sortedPQ[i + 1];
//     }
//     sortedSize--;

//     return minElement;
// }

// void displaySorted() {
//     if (sortedSize == 0) {
//         printf("[SortedPQ] Queue is empty!\n");
//         return;
//     }

//     printf("[SortedPQ] ");
//     for (int i = 0; i < sortedSize; i++) {
//         printf("%d ", sortedPQ[i]);
//     }
//     printf("\n");
// }



// // ===============================
// // APPROACH 2: Insert normally, remove smallest on delete
// // ===============================
// int unsortedPQ[SIZE];
// int unsortedSize = 0;

// void insertUnsorted(int value) {
//     if (unsortedSize == SIZE) {
//         printf("[UnsortedPQ] Queue Overflow!\n");
//         return;
//     }

//     unsortedPQ[unsortedSize++] = value;
//     printf("[UnsortedPQ] Inserted %d\n", value);
// }

// int deleteMinUnsorted() {
//     if (unsortedSize == 0) {
//         printf("[UnsortedPQ] Queue Underflow!\n");
//         return -1;
//     }

//     // find index of minimum element
//     int minIndex = 0;
//     for (int i = 1; i < unsortedSize; i++) {
//         if (unsortedPQ[i] < unsortedPQ[minIndex])
//             minIndex = i;
//     }

//     int minElement = unsortedPQ[minIndex];

//     // shift elements left
//     for (int i = minIndex; i < unsortedSize - 1; i++) {
//         unsortedPQ[i] = unsortedPQ[i + 1];
//     }
//     unsortedSize--;

//     return minElement;
// }

// void displayUnsorted() {
//     if (unsortedSize == 0) {
//         printf("[UnsortedPQ] Queue is empty!\n");
//         return;
//     }

//     printf("[UnsortedPQ] ");
//     for (int i = 0; i < unsortedSize; i++) {
//         printf("%d ", unsortedPQ[i]);
//     }
//     printf("\n");
// }



// // ===============================
// // MAIN FUNCTION TO TEST BOTH
// // ===============================
// int main() {
//     printf("=== Min Priority Queue Comparison ===\n\n");

//     printf("---- Approach 1: Sorted Insert ----\n");
//     insertSorted(30);
//     insertSorted(10);
//     insertSorted(40);
//     insertSorted(20);
//     displaySorted();

//     printf("Deleted: %d\n", deleteMinSorted());
//     displaySorted();

//     insertSorted(5);
//     displaySorted();

//     printf("Deleted: %d\n", deleteMinSorted());
//     displaySorted();


//     printf("\n---- Approach 2: Unsorted Insert ----\n");
//     insertUnsorted(30);
//     insertUnsorted(10);
//     insertUnsorted(40);
//     insertUnsorted(20);
//     displayUnsorted();

//     printf("Deleted: %d\n", deleteMinUnsorted());
//     displayUnsorted();

//     insertUnsorted(5);
//     displayUnsorted();

//     printf("Deleted: %d\n", deleteMinUnsorted());
//     displayUnsorted();

//     return 0;
// }





// // maximum priroty queue with usnorted array

// #include <stdio.h>
// #include <stdlib.h>

// #define size 100
// #define gloabalmin -100000000

// int pq[size];
// int curr=-1;


// void enqueue(int data){
//     if(curr==size-1){
//         printf("priorty queue is full");
//         return;
//     }
//     curr++;
//     pq[curr]=data;
// }


// int dequeue() {
//     if (curr < 0) {
//         return gloabalmin;
//     }

//     int max_index = curr;

//     // Find index of element with highest priority (max value)
//     for (int i = curr - 1; i >= 0; i--) {
//         if (pq[i] > pq[max_index]) {
//             max_index = i;
//         }
//     }

//     int removed = pq[max_index];

//     // Shift elements left to preserve order
//     for (int i = max_index; i < curr; i++) {
//         pq[i] = pq[i + 1];
//     }

//     curr--;

//     return removed;
// }




// maximum priority queue with the sorted array

#include <stdio.h>
#include <stdlib.h>

#define size 100
#define gloabalmin -100000000

int pq[size];
int curr=-1;

void enqueue(int data){
    if(curr==size-1){
        printf("The queue is full");
        return;
    }

    curr++;
    pq[curr]=data;

    int i=curr;

    while(i>0 && pq[i]<pq[i-1]){
        int temp=pq[i];
        pq[i]=pq[i-1];
        pq[i-1]=temp;
        i--;
    }
}

int dequeue(){
    if(curr<0){
        printf("Empty queue");
        return;
    }
    int removed=pq[curr];
    curr--;

    return removed;
}