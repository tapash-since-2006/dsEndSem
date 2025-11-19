// to only reverse the second half of the linked list


#include <stdio.h>
#include <stdlib.h>

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


struct Node* reverseRec(struct Node *head){

    if(head==NULL || head->next==NULL){
        return head;
    }

    struct Node* newHead=reverseRec(head->next);
    head->next->next=head;
    head->next=NULL;

    return newHead;

}


struct Node* reverseFromMiddle(struct Node** head){
    struct Node* slow=*head;
    struct Node* fast=*head;

    while(fast!=NULL && fast->next!=NULL){
        fast=fast->next->next;
        slow=slow->next;
    }

    // middle node is at the slow pointer

    // now we need to reverse only the later part

    slow->next=reverseRec(slow->next);
}



