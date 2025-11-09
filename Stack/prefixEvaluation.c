#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define size 100

int stack[size];
int top = -1;

void initStack() { top = -1; }
int isEmpty() { return top == -1; }
int pop() { return stack[top--]; }
int peek() { return stack[top]; }
void push(int c) { stack[++top] = c; }

int isOperator(char c) {
    return c=='+'||c=='-'||c=='*'||c=='/'||c=='^';
}

void evaluate(char prefix[]){
    int i=strlen(prefix)-1;
    while(i>=0){ 
        char token=prefix[i];
        if(!isOperator(token)){// not a operator i.e some value
            push(token-'0');
        }else{// operator
            int op1=pop();
            int op2=pop();

            switch(token){
                case '+': push(op1+op2);
                break;
                case '-': push(op1-op2);
                break;
                case '/': push(op1/op2);
                break;
                case '*': push(op1*op2);
                break;
                case '^': push((int)(pow((double)op1,(double)op2)));
                break;
            }
        }
        i--;
    }

    printf("The ans is : %d", peek());
}
