#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, rows, cols, i, j;
    int *arr1D;
    int **arr2D;

    // ---------------------- 1D ARRAY ----------------------
    printf("Enter size of 1D array: ");
    scanf("%d", &n);

    arr1D = (int*)malloc(n * sizeof(int));

    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr1D[i]);
    }

    printf("1D Array Elements: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr1D[i]);
    }
    printf("\n");

    // ---------------------- 2D ARRAY ----------------------
    printf("\nEnter number of rows and columns for 2D array: ");
    scanf("%d %d", &rows, &cols);

    arr2D = (int**)malloc(rows * sizeof(int*));
    for (i = 0; i < rows; i++) {
        arr2D[i] = (int*)malloc(cols * sizeof(int));
    }

    printf("Enter elements of %d x %d matrix:\n", rows, cols);
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            scanf("%d", &arr2D[i][j]);
        }
    }

    printf("2D Array (Matrix):\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", arr2D[i][j]);
        }
        printf("\n");
    }

    // ---------------------- FREE MEMORY ----------------------
    free(arr1D);
    for (i = 0; i < rows; i++) {
        free(arr2D[i]);
    }
    free(arr2D);

    return 0;
}
