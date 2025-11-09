#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100

// ---------------- Stack ----------------
char stack[SIZE];
int top = -1;

void initStack() { top = -1; }
int isEmpty() { return top == -1; }
char pop() { return stack[top--]; }
char peek() { return stack[top]; }
void push(char c) { stack[++top] = c; }

// ---------------- Helper Functions ----------------
int isOperator(char c) {
    return c=='+'||c=='-'||c=='*'||c=='/'||c=='^';
}

int precedence(char c){
    if(c=='+'||c=='-') return 1;
    if(c=='*'||c=='/') return 2;
    if(c=='^') return 3;
    return 0;
}

// ---------------- Reverse & Swap Parentheses ----------------
void reverseAndSwap(char expr[]) {
    int n = strlen(expr);
    // Reverse string
    for(int i=0; i<n/2; i++){
        char temp = expr[i];
        expr[i] = expr[n-i-1];
        expr[n-i-1] = temp;
    }
    // Swap parentheses
    for(int i=0; i<n; i++){
        if(expr[i]=='(') expr[i]=')';
        else if(expr[i]==')') expr[i]='(';
    }
}

// ---------------- Infix → Postfix ----------------
void infixToPostfix(char infix[], char postfix[]){
    int k = 0;
    initStack();

    for(int i=0; i<strlen(infix); i++){
        char c = infix[i];

        if(isalnum(c)){
            postfix[k++] = c;
        }
        else if(c == '('){
            push(c);
        }
        else if(c == ')'){
            while(!isEmpty() && peek() != '('){
                postfix[k++] = pop();
            }
            if(!isEmpty()) pop(); // remove '('
        }
        else if(isOperator(c)){
            while(!isEmpty() && peek() != '('){
                if((c == '^' && precedence(c) <= precedence(peek())) ||
                   (c != '^' && precedence(c) < precedence(peek()))) {
                    postfix[k++] = pop();
                } else {
                    break; // no need of popping can move forward to pushing into the stack the operator
                }
            }
            push(c);  // push operator after popping
        }
    }

    while(!isEmpty()){
        postfix[k++] = pop();
    }

    postfix[k] = '\0';
}

// ---------------- Infix → Prefix ----------------
void infixToPrefix(char infix[], char prefix[]){
    char temp[SIZE];
    strcpy(temp, infix);

    reverseAndSwap(temp);           
    char postfix[SIZE];
    infixToPostfix(temp, postfix);  // Convert reversed infix → postfix
    reverseAndSwap(postfix);        // Reverse postfix → prefix
    strcpy(prefix, postfix);
}

// ---------------- Main ----------------
int main(){
    char infix[SIZE], prefix[SIZE], postfix[SIZE];

    printf("Enter an infix expression: ");
    scanf("%s", infix);

    // Infix → Postfix
    infixToPostfix(infix, postfix);
    printf("Postfix: %s\n", postfix);

    // Infix → Prefix
    infixToPrefix(infix, prefix);
    printf("Prefix: %s\n", prefix);

    return 0;
}
