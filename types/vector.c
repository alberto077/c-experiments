#include "vector.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>


void push_back (vector_t_int *vec, int64_t val) {
    if (vec->capacity == vec->size) {
        int64_t *temp_arr = malloc(sizeof(int64_t) * (size_t)(vec->capacity * 2));

        if (temp_arr == NULL) {
            perror("Could not allocate enough space for the array");
        }

        memcpy(temp_arr, vec->arr, vec->capacity);

        vec->arr = temp_arr;
        vec->capacity *= 2;

    }

    vec->arr[vec->size] = val;
    vec->size +=1;
}

vector_t_int new_int_vec (size_t capacity) {
    int64_t *new_arr = malloc(sizeof(int64_t) * (size_t)capacity);
    if (new_arr == NULL ) {
        perror("Could not create underlying array");
    }

    vector_t_int v = {.capacity = capacity, .size = 0, .arr = new_arr};
    return v;


}

int main(void){

    vector_t_int vec = new_int_vec(10);

    push_back(&vec, 1);
    push_back(&vec, 2);
    push_back(&vec, 3);
    push_back(&vec, 4);


    for (size_t i = 0; i < vec.size; ++i) {
        printf("Value at %zu: %" PRId64 "\n", i, vec.arr[i]);
    }
    free(vec.arr);
    return 0;
}
