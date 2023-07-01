#include <stdio.h>

#define MAXLEN 10

/*
 * This method could be implemented to make the algebraic calculator 
 * work with floating point input.
*/

struct {
    enum {isFloat, isChar} type;
    union {
        float fVal;
        char cVal;
    } val;
} stack[MAXLEN];

int main() {

    char s[] = "lord";

    int j;
    for (j = 0; j < sizeof(s)-1; ++j) {
        stack[j].type = isChar;
        stack[j].val.cVal = s[j];
    }

    stack[j].type = isFloat;
    stack[j].val.fVal = .1;

    for (int i = 0; i <= sizeof(s)-1; ++i) {
        switch (stack[i].type) {
            case isFloat:
                printf("%.2f\n", stack[i].val.fVal);
                break;
            case isChar:
                printf("%c\n", stack[i].val.cVal);
                break;
            default:
                break;
        }
    }
        


}