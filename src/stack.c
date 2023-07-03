#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "forward_list.h"

struct Stack{
    Deque *data;
};

Stack *stack_construct(){
    Stack *stack = (Stack *)calloc(1, sizeof(Stack));
    stack->data = forward_list_construct();
    return stack;
}

void stack_push(Stack *stack, void *data){
    forward_list_push_front(stack->data, data);
}


int stack_empty(Stack *stack){
    return forward_list_size(stack->data) == 0;
}


void *stack_pop(Stack *stack){
    return forward_list_pop_front(stack->data);
}

void stack_destroy(Stack *stack){
    forward_list_destroy(stack->data);
    free(stack);
}