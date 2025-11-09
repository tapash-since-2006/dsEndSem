#include <stdio.h>
#include <string.h>

#define SIZE 100

char stack[SIZE];
int top = -1;

void push(char c) { stack[++top] = c; }
char pop() { return stack[top--]; }


char peek() { 
    if(top==-1){
        return '\0';
    }
    return stack[top]; 
}

int isEmpty() { return top == -1;}

int redundantParenthesis(char expr[]) {
    top = -1; // reset stack
    for(int i=0; expr[i]!='\0'; i++) {
        char c = expr[i];
        if(c == ')') {
            int operatorFound = 0;
            while(peek() != '\0' && peek() != '(') {
                char t = pop();
                if(t=='+' || t=='-' || t=='*' || t=='/' || t=='^')
                    operatorFound = 1;
            }
            if(peek() == '(') pop();
            if(!operatorFound) return 1; // redundant
        } else {
            push(c);
        }
    }
    return 0;
}


int main() {
    char expr[100];
    printf("Enter expression: ");
    fgets(expr, 100, stdin);
    expr[strcspn(expr, "\n")] = 0;

    if(redundantParenthesis(expr))
        printf("Expression has redundant parentheses.\n");
    else
        printf("No redundant parentheses.\n");

    return 0;
}

