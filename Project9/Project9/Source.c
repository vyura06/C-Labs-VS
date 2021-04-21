#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "stdbool.h"

#pragma warning(disable : 4996)

char strType(char i, int state) {
    if (65 <= i && i <= 90 && state == 1) {
        return 0;
    }
    if (i != '\\' && i != '|' && i != '"' && i != '*' && i != ':' && i != '<' && i != '>'
        && i != '?' && i != '/' && i != ' ') {
        return 3;
    }
    if (i == ':') {
        return 1;
    }
    if (i == '\\') {
        return 2;
    }
    return 0;
}

bool lexer(char str[]) {
    int matrix[7][4] = {
            {0, 0, 0, 0},
            {2, 0, 0, 0},
            {0, 3, 0, 0},
            {0, 0, 4, 0},
            {0, 0, 0, 5},
            {0, 0, 6, 5},
            {0, 0, 0, 5},
    };
    int state = 1;
    for (int i = 0; i < strlen(str); i++) {
        state = matrix[state][strType(str[i], state)];
    }
    if (state == 5) {
        return true;
    }
    else {
        return false;
    }
}


void findRegex(char str[]) {
    char* buff = (char*)calloc(strlen(str) + 1, sizeof(char));
    for (int i = 0; i < strlen(str); i++) {
        if (65 <= str[i] && str[i] <= 90) {
            int j = (int)strlen(str) - 1;
            while (j > i) {
                memset(buff, 0, strlen(str) + 1);
                strncpy(buff, str + i, j - i + 1);
                if (lexer(buff)) {
                    printf("Regex: %s\n", buff);
                    i = j;
                    break;
                }
                j--;
            }
        }
    }
    free(buff);
}

int main() {
    char str[255];
    gets(str);
    printf("%s\n", str);
    if (lexer(str)) {
        printf("True\n");
    }
    else {
        printf("False\n");
    }
    findRegex(str);
    return 0;
}