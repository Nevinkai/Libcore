//
// Created by nevinkai on 11/1/26.
//
#include <stdio.h>
#include "../include/vec.h"

int main(void) {
    vec *v = vec_new(sizeof(int));

    if (!v) {
        return -1;
    }

    int a = 1;

    vec_push(v, &a);

    int out = 0;

    vec_pop(v, &out);

    // printf("%d\n", out);


    for (int i = 1; i < 10; i++) {
        vec_push(v, &i);
    }

    int b = 50;
    vec_insert(v, 2, &b);


    // for (int i = 0; i < 10; i++) {
    //     int error_code = vec_pop(v, &out);
    //     if (error_code == -1) {
    //         continue;
    //     }
    //     printf("%d\n", out);
    // }

    int error_code = vec_remove(v, 2, &out);
    if (error_code == -1) {
        return -1;
    }
    // printf("%d\n", out);


    // Test Swap
    vec_swap(v, 1, 2);

    // Test reserve
    // printf("%zu\n", v->cap);
    // printf("%zu\n", v->len);
    error_code = vec_reserve(v, 31);
    if (error_code == -1) {
        return -1;
    }

    // printf("%zu\n", v->cap);
}
