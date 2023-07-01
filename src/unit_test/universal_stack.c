#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Test to see if universal stacks are viable and easy to use
*/

#undef NULL
#define NULL ((void *)0)
#define MAXLEN 50

typedef struct {
    void *elems[MAXLEN];
    int top;
    size_t elemSize;
    void (*freeFn)(void *);
} Stack;

void StackNew(Stack *s, size_t elemSize, void (*freeFn)(void *)) {
    s->top = -1;
    s->elemSize = elemSize;
    s->freeFn = freeFn;
}

int StackEmpty(Stack *s) {
    return s->top == -1;
}

void StackPush(Stack *s, void *elemAddr) {
    if (s->top == MAXLEN - 1) {
        exit(EXIT_FAILURE);
    }
    s->top++;
    s->elems[s->top] = malloc(s->elemSize);
    memcpy(s->elems[s->top], elemAddr, s->elemSize);
}

void StackPop(Stack *s, void *elemAddr) {
    if (StackEmpty(s)) {
        exit(EXIT_FAILURE);
    }
    memcpy(elemAddr, s->elems[s->top], s->elemSize);
    if (s->freeFn != NULL) {
        s->freeFn(s->elems[s->top]);
    }
    free(s->elems[s->top]);
    s->top--;
}

void freeInt(void *elem) {

}

void freeChar(void *elem) {

}

int main() {

    Stack s;
    Stack n;
    StackNew(&s, sizeof(int), freeInt);
    StackNew(&n, sizeof(char), freeChar);

    int x = 5, y = 6;

    StackPush(&s, &x);
    StackPush(&s, &y);

    int z;
    StackPop(&s, &z);

    char c = 'c', d = 'd';
    StackPush(&n, &c);
    StackPush(&n, &d);
    char f;
    StackPop(&n, &f);
    printf("%c ", f);

    printf("%d ", z);


    return 0;
}