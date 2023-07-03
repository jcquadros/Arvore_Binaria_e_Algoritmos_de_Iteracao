#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "forward_list.h"

struct Queue{
    Deque *data;
};

Queue *queue_construct(){
    Queue *queue = (Queue *)calloc(1, sizeof(Queue));
    queue->data = forward_list_construct();
    return queue;
}

void queue_push(Queue *queue, void *data){
    forward_list_push_back(queue->data, data);
}

int queue_empty(Queue *queue){
    return forward_list_size(queue->data) == 0;
}

void *queue_pop(Queue *queue){
    return forward_list_pop_front(queue->data);
}

void queue_destroy(Queue *queue){
    forwaed_list_destroy(queue->data);
    free(queue);
}