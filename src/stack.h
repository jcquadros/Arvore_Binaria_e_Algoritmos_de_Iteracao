
#ifndef _STACK_H_
#define _STACK_H_


typedef struct Stack Stack;
typedef void(*destroy_stack)(void*);

Stack *stack_construct();
void stack_push(Stack *stack, void *data);
int stack_empty(Stack *stack);
void *stack_pop(Stack *stack);
void stack_destroy(Stack *stack);

#endif