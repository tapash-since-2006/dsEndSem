#include <stdio.h>

// ---------------- RECURSIVE BUBBLE SORT ----------------
void bubbleSort(int arr[], int n) {
    if (n == 1) return;

    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            int temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
        }
    }
    bubbleSort(arr, n - 1);
}

// ---------------- RECURSIVE SELECTION SORT ----------------
void selectionSort(int arr[], int start, int n) {
    if (start >= n - 1) return;

    int minIndex = start;
    for (int i = start + 1; i < n; i++) {
        if (arr[i] < arr[minIndex]) {
            minIndex = i;
        }
    }

    if (minIndex != start) {
        int temp = arr[start];
        arr[start] = arr[minIndex];
        arr[minIndex] = temp;
    }

    selectionSort(arr, start + 1, n);
}

// ---------------- RECURSIVE INSERTION SORT ----------------
void insertionSort(int arr[], int n) {
    if (n <= 1) return;

    insertionSort(arr, n - 1);

    int last = arr[n - 1];
    int j = n - 2;

    while (j >= 0 && arr[j] > last) {
        arr[j + 1] = arr[j];
        j--;
    }
    arr[j + 1] = last;
}

// ---------------- RECURSIVE BINARY SEARCH ----------------
int binarySearch(int arr[], int low, int high, int key) {
    if (low > high) return -1;

    int mid = (low + high) / 2;

    if (arr[mid] == key) return mid;
    else if (arr[mid] > key) return binarySearch(arr, low, mid - 1, key);
    else return binarySearch(arr, mid + 1, high, key);
}


// =================================================================
//                ITERATIVE VERSIONS BELOW
// =================================================================

// ---------------- ITERATIVE BUBBLE SORT ----------------
void bubbleSortIterative(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// ---------------- ITERATIVE SELECTION SORT ----------------
void selectionSortIterative(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

// ---------------- ITERATIVE INSERTION SORT ----------------
void insertionSortIterative(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

// ---------------- ITERATIVE BINARY SEARCH ----------------
int binarySearchIterative(int arr[], int n, int key) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}


// =================================================================

// Print Array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}


// =================================================================
//                          MAIN MENU
// =================================================================

int main() {
    int choice, n, key;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("\nMenu:\n");
    printf("1. Bubble Sort (Recursive)\n");
    printf("2. Selection Sort (Recursive)\n");
    printf("3. Insertion Sort (Recursive)\n");
    printf("4. Binary Search (Recursive)\n");
    printf("5. Bubble Sort (Iterative)\n");
    printf("6. Selection Sort (Iterative)\n");
    printf("7. Insertion Sort (Iterative)\n");
    printf("8. Binary Search (Iterative)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            bubbleSort(arr, n);
            printf("Sorted Array (Recursive Bubble): ");
            printArray(arr, n);
            break;

        case 2:
            selectionSort(arr, 0, n);
            printf("Sorted Array (Recursive Selection): ");
            printArray(arr, n);
            break;

        case 3:
            insertionSort(arr, n);
            printf("Sorted Array (Recursive Insertion): ");
            printArray(arr, n);
            break;

        case 4:
            insertionSort(arr, n); // ensure sorted
            printf("Sorted Array: ");
            printArray(arr, n);
            printf("Enter key to search: ");
            scanf("%d", &key);
            int index = binarySearch(arr, 0, n - 1, key);
            if (index != -1)
                printf("Key found at index %d\n", index);
            else
                printf("Key not found.\n");
            break;

        case 5:
            bubbleSortIterative(arr, n);
            printf("Sorted Array (Iterative Bubble): ");
            printArray(arr, n);
            break;

        case 6:
            selectionSortIterative(arr, n);
            printf("Sorted Array (Iterative Selection): ");
            printArray(arr, n);
            break;

        case 7:
            insertionSortIterative(arr, n);
            printf("Sorted Array (Iterative Insertion): ");
            printArray(arr, n);
            break;

        case 8:
            insertionSortIterative(arr, n);
            printf("Sorted Array: ");
            printArray(arr, n);
            printf("Enter key to search: ");
            scanf("%d", &key);
            int idx = binarySearchIterative(arr, n, key);
            if (idx != -1)
                printf("Key found at index %d\n", idx);
            else
                printf("Key not found.\n");
            break;

        default:
            printf("Invalid choice!\n");
    }

    return 0;
}
