#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
};


struct Node* head=NULL;

struct Node* createNode(int data){
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    newNode->next=NULL;
    newNode->data=data;
    return newNode;
}

// insert at the middle

void insertAtMiddle(struct Node* head, int data){
    if(head==NULL){
        head=createNode(data);
        return;
    }
    if(head->next==NULL){
        head->next=createNode(data);
        return;
    }

    struct Node* newNode=createNode(data);

    struct Node* temp=head;
    int count=0;

    while(temp!=NULL){
        count++;
        temp=temp->next;
    }

    int index_loc=count/2; // here we calcuakted ourself hence index=loc otherwise index= loc-1
    temp=head;

    for(int i=0;i<index_loc-1;i++){
        temp=temp->next;
    }

    newNode->next=temp->next;
    temp->next=newNode;
}



void deleteKey(struct Node** head, int key){
    if(*head==NULL){
        return;
    }

    if((*head)->next==NULL){
        if((*head)->data==key){
            *head=NULL;
            return;
        }

        printf("Item not found");
        return;
    }

    struct Node* temp=*head;
    struct Node* prev=NULL;
    
    while(temp!=NULL && temp->data!=key){
        prev=temp;
        temp=temp->next;
    }

    if(temp==NULL){
        printf("Element not found");
        return;
    }

    //case when the node was the first node at that point prev will still be at  the NULL

    if(prev==NULL){
        struct Node* del=*head;
        *head=(*head)->next;
        free(del);
        return;
    }


    prev->next=temp->next;
    free(temp);

}



// for a doubly linked list deleteing a key value

void deleteKeyDLL(struct Node** head, int key){
    if(*head==NULL){
        return;
    }

    if((*head)->next==NULL){
        if((*head)->data=key){
            *head=NULL;
            return;
        }
        printf("Not found");
        return;
    }


    struct Node* temp=*head;

    while(temp!=NULL && temp->data!=key){
        temp=temp->next;
    }

    if(temp==NULL){
        printf("Element not found!!!");
        return;
    }

    if(temp->prev==NULL){ // first element case
        *head=temp->next;
        temp->next->prev=NULL;
        return;
    }else if(temp->next=NULL){ // last element case
        temp->prev->next=NULL;
        return;
    }

    temp->prev->next=temp->next;
    temp->next->prev=temp->prev;
    free(temp);

}