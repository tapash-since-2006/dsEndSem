# include<stdio.h>
# include<stdlib.h>

#define size 100
#define n 3

struct multiStack{
    int arr[size];
    int top[n];
    int freeSpot;
    int next[size];
};

void init(struct multiStack* ms){
    for(int i=0;i<n;i++){
        ms->top[i]=-1;
    }

    for(int i=0;i<size-1;i++){
        ms->next[i]=i+1;
    }

    ms->next[size-1]=-1;
    ms->freeSpot=0;
}

void push(struct multiStack* ms, int stackNum, int data){
    if(ms->freeSpot==-1){
        printf("The stack is full\n");
        return;
    }

    int index=ms->freeSpot;
    ms->freeSpot=ms->next[index];

    ms->arr[index]=data;
    ms->next[index]=ms->top[stackNum];
    ms->top[stackNum]=index;
}

int pop(struct multiStack* ms, int stackNum){
    if(ms->top[stackNum]==-1){
        printf("Cannot pop from an empty stack!!\n");
        return -1;
    }

    int index=ms->top[stackNum];
    int popped=ms->arr[index];

    ms->top[stackNum]=ms->next[index];
    ms->next[index]=ms->freeSpot;
    ms->freeSpot=index;

    return popped;
}

void display(struct multiStack* ms, int stackNum){
    if(ms->top[stackNum]==-1){
        printf("Stack %d is empty\n", stackNum);
        return;
    }

    printf("Stack %d: ", stackNum);
    int index=ms->top[stackNum];
    while(index!=-1){
        printf("%d ", ms->arr[index]);
        index=ms->next[index];
    }
    printf("\n");
}

int main() {
    struct multiStack ms;
    init(&ms);

    push(&ms, 0, 10);
    push(&ms, 0, 20);
    push(&ms, 1, 30);
    push(&ms, 2, 40);
    push(&ms, 1, 50);

    display(&ms, 0);
    display(&ms, 1);
    display(&ms, 2);

    printf("Popped from stack 0: %d\n", pop(&ms, 0));
    printf("Popped from stack 1: %d\n", pop(&ms, 1));
    printf("Popped from stack 2: %d\n", pop(&ms, 2));

    display(&ms, 0);
    display(&ms, 1);
    display(&ms, 2);

    return 0;
}
