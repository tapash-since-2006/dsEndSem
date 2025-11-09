#include<stdio.h>
#include<stdlib.h>

struct stack{
    int* age;
    int top;
};

struct stack s1;
struct stack s2;

void initStack(struct stack* s, int n){
    s->top=-1;
    s->age=(int*)malloc(n*sizeof(int));
}

void push(struct stack* s, int val){
    s->age[++s->top]=val;
}

int isEmpty(struct stack* s){
    return s->top==-1;
}

int pop(struct stack* s){
    return s->age[s->top--];
}

void Split(int n){
    printf("enter the age one by one: ");
    for(int i=0;i<n;i++){
        int age;
        scanf("%d", &age);
        if(age%2==0){
            push(&s1, age);
        }else{
            push(&s2, age);
        }
    }
}

void calculateAvg(int n){
    int evenSum=0;
    int oddSum=0;
    int totalSum=0;

    int x=0;
    int y=0;
    int z=0;

    while(!isEmpty(&s1)){
        x++;
        evenSum+=pop(&s1);
    }

    while(!isEmpty(&s2)){
        y++;
        oddSum+=pop(&s2);
    }

    z=x+y;
    totalSum=evenSum+oddSum;

    printf("Even Avg is %d", evenSum/x);
    printf("Odd Avg is %d", oddSum/y);
    printf("Total Avg is %d", totalSum/z);

}


int main(){
    printf("Enter the number of people: ");
    int n;
    scanf("%d", &n);
    initStack(&s1, n);
    initStack(&s2, n);
    Split(n);
    calculateAvg(n);
    return 0;
}