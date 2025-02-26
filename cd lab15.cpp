#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

// Operator precedence table
char precedenceTable[MAX][MAX] = {
    //  +    -    *    /    i    (    )    $
    { '>', '>', '<', '<', '<', '<', '>', '>' }, // +
    { '>', '>', '<', '<', '<', '<', '>', '>' }, // -
    { '>', '>', '>', '>', '<', '<', '>', '>' }, // *
    { '>', '>', '>', '>', '<', '<', '>', '>' }, // /
    { '>', '>', '>', '>', '-', '-', '>', '>' }, // i (operand)
    { '<', '<', '<', '<', '<', '<', '=', '-' }, // (
    { '>', '>', '>', '>', '-', '-', '>', '>' }, // )
    { '<', '<', '<', '<', '<', '<', '-', 'A' }  // $
};

char operators[] = "+-*/i()$";

// Function to get the precedence table index of a symbol
int getIndex(char c) {
    for (int i = 0; i < 8; i++) {
        if (operators[i] == c)
            return i;
    }
    return -1;
}

void operatorPrecedenceParser(char *input) {
    char stack[MAX];
    int top = 0;
    stack[top] = '$';  // Initial stack symbol
    int i = 0;

    printf("Stack\tInput\tAction\n");
    printf("---------------------------\n");
    while (1) {
        // Print stack and input
        printf("%s\t%s\t", stack, input + i);
        
        char stackTop = stack[top];
        char currentSymbol = input[i];
        
        int stackIndex = getIndex(stackTop);
        int inputIndex = getIndex(currentSymbol);
        
        if (stackIndex == -1 || inputIndex == -1) {
            printf("Error: Invalid symbol\n");
            return;
        }
        
        char precedence = precedenceTable[stackIndex][inputIndex];
        
        if (precedence == '<' || precedence == '=') {
            // Shift operation
            printf("Shift\n");
            stack[++top] = currentSymbol;
            i++;
        } else if (precedence == '>') {
            // Reduce operation
            printf("Reduce\n");
            top--; // Pop one element from the stack
        } else if (precedence == 'A') {
            // Accept the input string
            printf("Accepted\n");
            return;
        } else {
            printf("Error: Invalid syntax\n");
            return;
        }
    }
}

int main() {
    char input[MAX];
    printf("Enter expression (end with $): ");
    scanf("%s", input);

    operatorPrecedenceParser(input);
    return 0;
}
