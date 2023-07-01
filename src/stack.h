#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdio.h>

#define MAXLEN 100

typedef struct {
    void *elems[MAXLEN];
    int top;
    size_t elemSize;
    void (*freeFn)(void *);
} Stack;

void StackNew(Stack *s, size_t elemSize, void (*freeFn)(void *));
int StackEmpty(Stack *s);
void StackPush(Stack *s, void *elemAddr);
void StackPop(Stack *s, void *elemAddr);
void freeChar();
void freeFloat();

#endif