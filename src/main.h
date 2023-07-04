#ifndef MAIN_H
#define MAIN_H

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define true 1
#define false 0
#define bool int

#define TESTPHASE false

#define MAXLEN 100
#define PI 3.14159265358979323846264338327950288419716939937
#define UI "\
UNSCIENTIFIC CALCULATOR: \n\
* to quit press: q\n\
* log2 -> lb; log10 -> lg;\n"


enum angleUnit {degrees, radians} au;

typedef struct {
    enum { isFloat, isOp, isLeftPar, isRightPar, isEnd } type;
    union {
        float fVal;
        char cVal;
    } val;
} Array;


void getLine(char s[]);
float evalFunc(int n, float number);
int isOperator(char c);
void createArray(char s[], Array *arr);
float performOperation(char op, float a, float b);
int getPrecedence(char op);
int hasGreaterPrecedence(char topOperator, char incomingOperator);
void convertToPostfix(Array *infixNotation, Array *reversePolish);
float evaluatePostfix(Array *reversePolish);

#endif