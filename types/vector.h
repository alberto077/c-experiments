#include <stddef.h>
#include <stdint.h>

typedef struct {
    size_t capacity;
    size_t size;
    int64_t *arr;
} vector_t_int;

void push_back (vector_t_int *vec, int64_t val);

vector_t_int new_int_vec (size_t capacity);
