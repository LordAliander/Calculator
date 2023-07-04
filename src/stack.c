#include "stack.h"
#include <stdlib.h>
#include <string.h>

void StackNew(Stack *s, size_t elemSize, void (*freeFn)(void *)) {
    s->top = -1;
    s->elemSize = elemSize;
    s->freeFn = freeFn;
}

int StackEmpty(Stack *s) { return s->top == -1; }

void StackPush(Stack *s, void *elemAddr) {
    if (s->top >= MAXLEN - 1) {
        //fprintf(stderr, "Stack overflow\n");
        return;
    }
    s->top++;
    s->elems[s->top] = malloc(s->elemSize);
    memcpy(s->elems[s->top], elemAddr, s->elemSize);
}

void StackPop(Stack *s, void *elemAddr) {
    if (StackEmpty(s)) {
        // fprintf(stderr, "Stack underflow\n");
        return;
    }
    memcpy(elemAddr, s->elems[s->top], s->elemSize);
    if (s->freeFn != NULL) {
        s->freeFn(s->elems[s->top]);
    }
    free(s->elems[s->top]);
    s->top--;
}

void freeChar() {}
void freeFloat() {}
