#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

char stack[SIZE];
int top = -1;

void push(char c) { stack[++top] = c; }
char pop() { return stack[top--]; }
int isEmpty() { return top == -1; }

int isMatching(char open, char close) {
    return (open=='(' && close==')') ||
           (open=='{' && close=='}') ||
           (open=='[' && close==']');
}

int isBalanced(char expr[]) {
    top = -1; // reset stack
    for(int i=0; expr[i]!='\0'; i++) {
        char c = expr[i];
        if(c=='(' || c=='{' || c=='[') {
            push(c);
        } else if(c==')' || c=='}' || c==']') {
            if(isEmpty() || !isMatching(pop(), c)) {
                return 0; // not balanced
            }
        }
    }
    return isEmpty(); // balanced if stack empty
}

int main() {
    char expr[SIZE];
    printf("Enter expression: ");
    fgets(expr, SIZE, stdin);
    expr[strcspn(expr, "\n")] = 0; // remove newline

    if(isBalanced(expr)) {
        printf("Parentheses are balanced.\n");
    } else {
        printf("Parentheses are NOT balanced.\n");
    }

    return 0;
}
