// queue of structure

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define size 3

struct node{
    char name[100];
    char event[100];
    int reg_id;
};

struct node q[size];
int front=0;
int rear=0;

void enqueue(char name[], char event[], int reg_id){
    if(rear>=size){
        return;
    }
    strcpy(q[rear].name, name);
    strcpy(q[rear].event, event);
    q[rear].reg_id=reg_id;
    rear++;
}

void dequeue(char res_name[], char res_event[], int *res_id) {
    if(front == rear){
        printf("Queue is empty!\n");
        return;
    }

    strcpy(res_name, q[front].name);
    strcpy(res_event, q[front].event);
    *res_id = q[front].reg_id;

    front++;
    if(front == rear){
        front = rear = 0;
    }
}




void display(){
    if(front==rear){
        return;
    }

    for(int i=front; i<rear; i++){
        printf("%s", q[i].name);
    }
}
