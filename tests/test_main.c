//
// Created by nevinkai on 11/1/26.
//
#include <stdio.h>
#include "../include/vec.h"
#include "../include/tests.h"

// vec_new

static void tests_new_happy_path(void) {
    vec *v = vec_new(4);
    CHECK(v);
    CHECK(v->data == NULL);
    CHECK(v->len == 0);
    CHECK(v->cap == 0);
    CHECK(v->elem_size == 4);
    vec_free(v);
}

static void tests_new_elem_size_0(void) {
    vec *v = vec_new(0);
    CHECK(!v);
}

// vec_with_capacity

static void tests_new_capacity_happy(void) {
    vec *v = vec_with_capacity(4, 10);
    CHECK(v);
    CHECK(v->data == NULL);
    CHECK(v->len == 0);
    CHECK(v->cap == 10);
    CHECK(v->elem_size == 4);
    vec_free(v);
}

static void tests_new_capacity_elem_size_0(void) {
    vec *v = vec_with_capacity(0, 10);
    CHECK(!v);
}

static void tests_new_capacity_cap_size_0(void) {
    vec *v = vec_with_capacity(4, 0);
    CHECK(v);
    CHECK(v->data == NULL);
    CHECK(v->len == 0);
    CHECK(v->cap == 0);
    CHECK(v->elem_size == 4);
    vec_free(v);
}

int main(void) {
    // vec_new
    RUN_TEST(tests_new_happy_path);
    RUN_TEST(tests_new_elem_size_0);

    // vec_with_capacity
    RUN_TEST(tests_new_capacity_happy);
    RUN_TEST(tests_new_capacity_elem_size_0);
    RUN_TEST(tests_new_capacity_cap_size_0);


    TEST_SUMMARY();
}
