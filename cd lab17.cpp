#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void lexicalAnalyzer(FILE *file) {
    char ch;
    int charCount = 0, wordCount = 0, lineCount = 0;
    int inWord = 0;
    
    while ((ch = fgetc(file)) != EOF) {
        charCount++;
        
        if (ch == '\n') {
            lineCount++;
        }
        
        if (isspace(ch)) {
            inWord = 0;
        } else if (!inWord) {
            inWord = 1;
            wordCount++;
        }
    }
    
    printf("Characters: %d\n", charCount);
    printf("Words: %d\n", wordCount);
    printf("Lines: %d\n", lineCount);
}

int main() {
    char filename[100];
    FILE *file;
    
    printf("Enter the filename: ");
    scanf("%s", filename);
    
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    
    lexicalAnalyzer(file);
    
    fclose(file);
    return 0;
}

