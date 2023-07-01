#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * Have to implement scientific notation
 * if needed by scientific notation use universal stack functions
 */

// maximal length of stacks, queues and strings inside the program
#define MAXLEN 50

/*
 * operatorStack -> used to stack the operators in shunting yard algorithm
 * outputQueue -> will contain the result of the SYA
 * resultStack -> used to calculate the result of the expression in infix notation
 * top -> top of the stack; used by both stacks as they are never used at the same time
 */

char operatorStack[MAXLEN];
int top = -1;
char outputQueue[MAXLEN];
float resultStack[MAXLEN];

typedef struct {
    enum {isFloat, isOp} type;
    union {
        float fVal;
        char cVal;
    } val;
} Stack;


/*
 * Refer to the positions of numbers and operators in the ASCII-table 
 * only here to remove "magic numbers" in the functions
 */

int intLowerBound = 48, intUpperBound = 57;
int operatorLowerBound = 42, operatorUpperBound = 47;

/*
 * getLine() reads a line of input from the standart input and stores it in whatever 
 * array is passed to it as reference. The reading stops when either the maximal input
 * length is met or and EOF / newline is read. The function appends a Null character at 
 * the end of the string to mark it as finished. 
 */

int getLine(char s[]) {
    int i, c;
    for (i = 0; i < MAXLEN - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    s[i] = '\0';
    return 0;
}

/*
 * 
*/

int isOperator(char c) {
    switch (c) {
        case '+':
        case '/':
        case '-':
        case '*':
            return 1;
        default:    
            return 0;
    }
}

/*
 * Function will take in a string as argument and the adress of the stack.
 * Floating point numbers have to be processed
 * 
 */

void createStack(char s[], Stack stack[]) {
    char c;
    for (int i = 0; (c = s[i]) != '\0'; ++i) {
        if (isdigit(c)) {
            stack[i].type = isFloat;
            stack[i].val.fVal = (float) (c - '0'); // convert c to f
        } 
        if (isOperator(c)) {
            stack[i].type = isOp;
            stack[i].val.cVal = c;
        }
    }
}

/*
 * push() and pop() are commonly used stack-functions pushResult() and popResult()
 * do the same thing but use stack's of different data types. 
 * Note:
 * Maybe this can be done in a different / more efficient way but I do not know how.
 */

int push(char data) {
    if (top == MAXLEN - 1) {
        return -1; // stack is overflown
    }
    top++;
    operatorStack[top] = data;
    return 0;
}

char pop() {
    char data = operatorStack[top];
    top--;
    return data;
}

int pushResult(float data) {
    if (top == MAXLEN - 1) {
        return -1; // stack is overflown
    }
    top++;
    resultStack[top] = data;
    return 0;
}

float popResult() {
    float data = resultStack[top];
    top--;
    return data;
}

/*
 * getPrecedence() returns the precedence of an operator based on normal algebraic
 * rules. It is a support function of hasGreaterPrecedence().
 */

int getPrecedence(char operator) {
    switch (operator) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;

    default:
        return -1; // for unknown operators
    }
}

/*
 * hasGreaterPrecendence() takes in two operators as characters and returns True if the
 * first operator has the grater precedence and returns False in the other case. 
 * The >= handles the case where the operators have the same precedence but it is important
 * to return True in this case because of the / operator.
 */

int hasGreaterPrecedence(char topOperator, char incomingOperator) {
    int op1 = getPrecedence(topOperator);
    int op2 = getPrecedence(incomingOperator);

    if (op1 >= op2) {
        return 1; // True: operator1 has greater precedence
    } else {
        return 0; // False: operator1 does not have greater precedence
    }
}

/*
 * convertToPostfix() is an implementation of the shunting yard algorithm. It takes 
 * an algebraic expression in string format as input and returns the postfix (reverse
 * polish notation) of the expression. 
 * Limitations: Can only handle single digit numbers 0-9 and no floats. 
 */

int convertToPostfix(char s[]) {
    char c;
    int j = 0;
    for (int i = 0; (c = s[i]) != '\0'; ++i) {
        // skip the garbage
        if (c == '\n' || c == '\t' || c == ' ')
            continue;
        //if number
        if ((intLowerBound <= (int) c) && ((int) c <= intUpperBound))
            outputQueue[j++] = c;
        //if operator
        if ((operatorLowerBound <= (int) c) && ((int) c <= operatorUpperBound)) {
            while (top != -1 && hasGreaterPrecedence(operatorStack[top], c))
                outputQueue[j++] = pop();
            push(c);
        }
        // handle brackets
        if (c == '(')
            push(c);
        if (c == ')') {
            while (operatorStack[top] != '(')
                outputQueue[j++] = pop();
            pop();
        }
    }
    while (top != -1) {
        outputQueue[j++] = pop();
    }
    outputQueue[j] = '\0';
    return 0;
}

/*
 * evaluatePostfix() uses a very common stack based solution to calculate
 * the result of the expression, in postfix notation. 
 * Explanation: 
 * 1. Push all the integers you find into a stack.
 * 2. If you find an operator pop two int's from the stack
 * 3. Calculate using the operator and push result in the stack
 * 4. Repeat as long as there are operators / until the end of the string
 * 5. The result is the last element in the stack
 */

float evaluatePostfix(char s[]) {
    char c;
    top = -1;
    for (int i = 0;
        (c = s[i]) != '\0'; ++i) {
        // if number
        if ((intLowerBound <= (int) c) && ((int) c <= intUpperBound))
            pushResult((int) c - 48);
        // if operator and stack has enough elements
        else if ((operatorLowerBound <= (int) c) && ((int) c <= operatorUpperBound && top >= 1)) {
            float a = popResult();
            float b = popResult();
            float result = 0;
            switch (c) {
                case '+':
                    result = b + a;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = b * a;
                    break;
                case '/':
                    result = b / a;
                    break;
            }
            pushResult(result);
        }
    }
    //last stack element shoult contain final result
    return popResult();
}

/*
 * main() gives the program a little command line interface. 
 */

int main() {
    char expression[MAXLEN];
    printf("Usage:\n \t 1. Input algebraic expressions\n \t 2. Press Control + C to quit\n \t 3. ENJOY!\n");
    printf("########################################################\n");
    printf("THE CALCULATOR DOES NOT WORK WITH FLOATING POINT ANSWERS\n");
    printf("########################################################\n");

    Stack stack[MAXLEN];

    while (1) {
        printf("Type in your expression: ");
        while (getLine(expression) > 0); //read the input
        if (expression[0] == 'q')
            break;
        convertToPostfix(expression);
        puts(outputQueue);
        printf("The result is: %.2f\n", evaluatePostfix(outputQueue));
    }
    return 0;
}