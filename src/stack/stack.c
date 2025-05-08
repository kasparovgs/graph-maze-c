#include <stdio.h>
#include <stdlib.h>
#include "stack/stack.h"

Stack* init_stack() {
    Stack* stack = (Stack*)calloc(1, sizeof(Stack));
    return stack;
}


void stack_push(Stack* stack, List* list) {
    StackNode* new = (StackNode*)malloc(sizeof(StackNode));
    new->list = list;
    new->next = stack->head;
    stack->head = new;
}


List* stack_pop(Stack* stack) {
    StackNode* poped = stack->head;
    stack->head = poped->next;
    List* list = poped->list;
    free(poped);
    return list;
}


int is_empty_stack(Stack* stack) {
    return stack->head == NULL;
}


void free_stack(Stack* stack) {
    StackNode* current = stack->head;
    StackNode* prev = NULL;
    while (current != NULL) {
        prev = current;
        current = current->next;
        free(prev);
    }
    free(stack);
}
