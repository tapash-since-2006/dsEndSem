#include <stdio.h>
#include <stdlib.h>
#define size 100


// // unsorted mannner
// int arr[size];
// int pointer = -1;

// void insertItem(int data){
//     if(pointer >= size-1){
//         return;
//     }
//     arr[++pointer] = data;
// }

// int popItem(){
//     if(pointer == -1){
//         return -1;
//     }

//     int minIndex = 0;
//     for(int i = 1; i <= pointer; i++){
//         if(arr[i] < arr[minIndex]){
//             minIndex = i;
//         }
//     }

//     int min = arr[minIndex];
//     arr[minIndex] = arr[pointer]; 
//     pointer--;
//     return min;
// }


//sorted manner for minmum priorirty  than in  descending order it will be needed to sort as pointer will be at the end

int arr[size];
int pointer=-1;

int popItem(){
    if(pointer==-1){
        return -1;
    }
    return arr[pointer--];
}


void insertItem(int data){
    if(pointer>=size-1){
        return;
    }
    // arr[++pointer]=data;
    // bubblesort(arr,pointer+1);

    if(pointer==-1){
        arr[++pointer]=data;
        return;
    }

    int i=pointer;
    while(i>=0 && data>arr[i]){
        arr[i+1]=arr[i];
        i--;
    }
    arr[i+1]=data;
    pointer++; // important to increment the pointer after adding the new item

}


// void bubblesort(int arr1[], int n){
//     for(int i=0;i<n-1;i++){
//         for(int j=0;j<n-i-1;j++){
//             if(arr1[j]<arr1[j+1]){
//                 int temp=arr1[j];
//                 arr1[j]=arr1[j+1];
//                 arr1[j+1]=temp;
//             }
//         }
//     }
// }