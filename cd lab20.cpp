#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

// Define grammar productions
char productions[MAX][MAX] = {
    "E=E+T",
    "E=T",
    "T=T*F",
    "T=F",
    "F=(E)",
    "F=id"
};
int numProductions = 6;

// Function to find trailing symbols
void findTrailing(char nonTerminal, char trailing[MAX]) {
    for (int i = 0; i < numProductions; i++) {
        if (productions[i][0] == nonTerminal) {
            int len = strlen(productions[i]);
            for (int j = len - 1; j >= 2; j--) {
                if (isalnum(productions[i][j]) || productions[i][j] == ')') {
                    strncat(trailing, &productions[i][j], 1);
                    break;
                } else if (isupper(productions[i][j])) {
                    findTrailing(productions[i][j], trailing);
                    break;
                }
            }
        }
    }
}

int main() {
    char trailing[MAX] = "";
    char nonTerminal;
    
    printf("Enter a non-terminal (E, T, or F): ");
    scanf(" %c", &nonTerminal);
    
    findTrailing(nonTerminal, trailing);
    
    printf("TRAILING(%c) = { %s }\n", nonTerminal, trailing);
    return 0;
}

