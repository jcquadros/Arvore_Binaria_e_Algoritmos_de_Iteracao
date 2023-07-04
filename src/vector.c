#include "vector.h"
#include <stdlib.h>
#include <stdio.h>
#define INITIAL_CAPACITY 10
#define GROWTH_FACTOR 2

struct Vector
{
    data_vector *data;
    int size;
    int capacity;
};

Vector *vector_create()
{
    Vector *vector = (Vector *)calloc(1, sizeof(Vector));
    vector->data = (data_vector *)calloc(INITIAL_CAPACITY, sizeof(data_vector));
    vector->size = 0;
    vector->capacity = INITIAL_CAPACITY;
    return vector;
}

void vector_push_back(Vector *vector, data_vector data)
{
    if (vector->size == vector->capacity)
    {
        vector->capacity *= GROWTH_FACTOR;
        vector->data = (data_vector *)realloc(vector->data, vector->capacity * sizeof(data_vector));
    }
    vector->data[vector->size] = data;
    vector->size++;
}

data_vector vector_pop_back(Vector *vector)
{
    if (vector->size == 0)
    {
        printf("vector_pop_back: Vector is empty\n");
        exit(1);
    }
    vector->size--;
    return vector->data[vector->size];
}

int vector_size(Vector *vector)
{
    return vector->size;
}

int vector_is_empty(Vector *vector)
{
    return vector->size == 0;
}

data_vector vector_get(Vector *vector, int index)
{
    if (index < 0 || index >= vector->size)
    {
        printf("vector_get: Index out of bounds\n");
        exit(1);
    }
    return vector->data[index];
}

void vector_destroy(Vector *vector)
{
    // assume que o vetor não contém ponteiros para memória alocada dinamicamente
    free(vector->data);
    free(vector);
}