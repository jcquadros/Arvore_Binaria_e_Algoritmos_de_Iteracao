#ifndef VECTOR_H
#define VECTOR_H
typedef struct Vector Vector;
typedef void* data_vector;
typedef void (*destroy_vector)(data_vector);

Vector* vector_create(destroy_vector destroy);
void vector_push_back(Vector* vector, data_vector data);
data_vector vector_pop_back(Vector* vector);
int vector_size(Vector* vector);
int vector_is_empty(Vector *vector);
void vector_destroy(Vector* vector);

#endif // VECTOR_H