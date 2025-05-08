#ifndef STACK_H
#define STACK_H


typedef struct List List;

typedef struct StackNode {
    List* list;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    StackNode* head;
} Stack;

Stack* init_stack();
void stack_push(Stack* stack, List* list);
List* stack_pop(Stack* stack);
int is_empty_stack(Stack* stack);
void free_stack(Stack* stack);

#endif