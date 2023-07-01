#include "main.h"
#include "stack.h"

// -> have to add invalid input checks
// -> have to patch some bugs

void getLine(char s[]) {
    int i;
    char c;
    for (i = 0; i < MAXLEN - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    s[i] = '\0';
}

int isOperator(char c) {
    switch (c) {
        case '+':
        case '/':
        case '-':
        case '*':
        case '^':
            return 1;
        default:
            return 0;
    }
}

float evalFunc(int n, float number) {
    float i = 1;
    if (!au) i = PI / 180;
    switch (n) {
        case 0:
            return (float)sin(i * number);
        case 1:
            return (float)cos(i * number);
        case 2:
            return (float)tan(i * number);
        case 3:
            return (float)sqrt(number);
        default:
            return 1.;
    }
}

void createArray(char s[], Array *arr) {
    char c;
    int i, j, k = 0;
    int x;
    char temp[MAXLEN];  // Temporary string to store a number
    enum func { sin, cos, tan, sqrt };
    enum func f;
    for (i = 0; (c = s[i]) != '\0'; i++) {  // <--- increment 'i' here
        if (c == ' ' || c == '\t' || c == '\n') {
            continue;
        }
        if (isdigit(c) || c == '.' || c == 'e' || c == 'E' ||
            (i > 0 && c == '-' && (s[i - 1] == 'e' || s[i - 1] == 'E'))) {
            // If character is part of a float, capture the entire number
            for (j = 0;
                 isdigit(s[i]) || s[i] == '.' || s[i] == 'e' || s[i] == 'E' ||
                 (s[i] == '-' && (s[i - 1] == 'e' || s[i - 1] == 'E'));
                 ++j, ++i) {
                temp[j] = s[i];
            }
            temp[j] = '\0';  // null-terminate the temp string
            arr[k].type = isFloat;
            arr[k].val.fVal =
                (float)atof(temp);  // convert string to float using atof
            k++;                    // increment the index for Array struct
            i--;  // decrement 'i' to avoid skipping characters
        } else {
            if (isOperator(c)) {
                arr[k].type = isOp;
                arr[k].val.cVal = c;
                k++;
            } else if (c == 't' || c == 's' || c == 'c' || c == 'r') {
                switch (c) {
                    case 'c':
                        f = cos;
                        break;
                    case 's':
                        f = sin;
                        break;
                    case 't':
                        f = tan;
                        break;
                    case 'r':
                        f = sqrt;
                        break;
                    default:
                        break;
                }
                for (; s[i] != '('; ++i)
                    ;
                ++i;
                for (x = 0; isdigit(s[i]) || s[i] == '.'; ++i, ++x) {
                    temp[x] = s[i];
                }
                temp[x] = '\0';
                if (atoi(temp) == 90 && f == 2)
                    fprintf(stderr, "tan(90) is undefined\n");
                arr[k].type = isFloat;
                arr[k].val.fVal = evalFunc(f, (float)atof(temp));
                k++;
            } else if (c == '(') {
                arr[k].type = isLeftPar;
                arr[k].val.cVal = c;
                k++;
            } else if (c == ')') {
                arr[k].type = isRightPar;
                arr[k].val.cVal = c;
                k++;
            }
        }
    }
    arr[k].type = isEnd;
}

float performOperation(char op, float a, float b) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return b - a;
        case '*':
            return a * b;
        case '/':
            return b / a;
        case '^':
            return (float) pow(b, a);
        default:
            return 1.;
    }
}

int getPrecedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;

        default:
            return -1;  // for unknown operators
    }
}

int hasGreaterPrecedence(char topOperator, char incomingOperator) {
    int op1 = getPrecedence(topOperator);
    int op2 = getPrecedence(incomingOperator);

    if (op1 >= op2) {
        return 1;  // True: operator1 has greater precedence
    } else {
        return 0;  // False: operator1 does not have greater precedence
    }
}

void convertToPostfix(Array *infixNotation, Array *reversePolish) {
    Stack operatorStack;
    StackNew(&operatorStack, sizeof(char), freeChar);
    int j = 0;
    for (int i = 0; infixNotation[i].type != isEnd; ++i) {
        if (infixNotation[i].type == isFloat) {
            reversePolish[j].type = isFloat;
            reversePolish[j++].val.fVal = infixNotation[i].val.fVal;
        }
        if (infixNotation[i].type == isOp) {
            char topOfStack;
            char currentOperator = infixNotation[i].val.cVal;
            if (!StackEmpty(&operatorStack)) {  // Check if the stack is empty
                                                // before popping
                StackPop(&operatorStack, &topOfStack);
                StackPush(&operatorStack, &topOfStack);
            }
            while (!StackEmpty(&operatorStack) &&
                   hasGreaterPrecedence(topOfStack, currentOperator)) {
                char operator;
                StackPop(&operatorStack, &operator);
                reversePolish[j].type = isOp;
                reversePolish[j++].val.cVal = operator;
            }
            StackPush(&operatorStack, &currentOperator);
        }
        if (infixNotation[i].type == isLeftPar) {
            char parenthesis = infixNotation[i].val.cVal;
            StackPush(&operatorStack, &parenthesis);
        }
        if (infixNotation[i].type == isRightPar) {
            char c;
            if (!StackEmpty(&operatorStack)) {  // Check if the stack is empty
                                                // before popping
                StackPop(&operatorStack, &c);
                while (c != '(' && !StackEmpty(&operatorStack)) {
                    reversePolish[j].type = isOp;
                    reversePolish[j++].val.cVal = c;
                    StackPop(&operatorStack, &c);
                }
            }
        }
    }
    while (!StackEmpty(&operatorStack)) {
        char c;
        StackPop(&operatorStack, &c);
        reversePolish[j].type = isOp;
        reversePolish[j++].val.cVal = c;
    }
    reversePolish[j].type = isEnd;
}

float evaluatePostfix(Array *reversePolish) {
    Stack resultStack;
    float resultFinal;
    StackNew(&resultStack, sizeof(float), freeFloat);
    int i;
    for (i = 0; reversePolish[i].type != isEnd; ++i) {
        if (reversePolish[i].type == isFloat) {
            float value = reversePolish[i].val.fVal;
            StackPush(&resultStack, &value);
        } else {
            float op1, op2, result;
            StackPop(&resultStack, &op1);
            StackPop(&resultStack, &op2);
            result = performOperation(reversePolish[i].val.cVal, op1, op2);
            StackPush(&resultStack, &result);
        }
    }
    StackPop(&resultStack, &resultFinal);
    return resultFinal;
}

int main() {
    Array infixNotation[MAXLEN];
    Array reversePolish[MAXLEN];
    char s[MAXLEN];
    char s1[MAXLEN];
    printf(UI);
    printf("* select angle unit (r/d): \n -> ");
    getLine(s1);
    au = (s1[0] == 'd') ? degrees : radians;
    while (1) {
        printf("\nInput expression: ");
        getLine(s);
        if (s[0] == 'q') return 0;
        createArray(s, infixNotation);
        convertToPostfix(infixNotation, reversePolish);
        float result = 0.;
        result = evaluatePostfix(reversePolish);
        printf("The result is: %f", result);
    }
    return 0;
}