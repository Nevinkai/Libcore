//
// Created by nevinkai on 11/1/26.
//
#include <stdbool.h>
#include <stdint.h>
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

static void tests_new_capacity_happy_path(void) {
    vec *v = vec_with_capacity(4, 10);
    CHECK(v);
    CHECK(v->data != NULL);
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

// vec_free

// NONE

// vec_len
static void tests_len_happy_path(void) {
    vec *v = vec_new(4);
    CHECK(v);
    CHECK(vec_len(v) == 0);
    int a = 5;
    CHECK(vec_push(v, &a) == 0);
    CHECK(vec_len(v) == 1);
    vec_free(v);
}

// vec_cap
static void tests_cap_happy_path(void) {
    vec *v = vec_new(4);
    CHECK(v);
    CHECK(vec_cap(v) == 0);
    int a = 5;
    CHECK(vec_push(v, &a) == 0);
    CHECK(vec_cap(v) == 1);
    vec_free(v);
}

// vec_is_empty
static void tests_is_empty_happy_path(void) {
    vec *v = vec_new(4);
    CHECK(v);
    CHECK(vec_is_empty(v) != 0);
    vec_free(v);
}

static void tests_is_empty_added_element(void) {
    vec *v = vec_new(4);
    CHECK(v);
    int a = 5;
    CHECK(vec_push(v, &a) == 0);
    CHECK(vec_is_empty(v) == 0);
    vec_free(v);
}

// vec_get
static void tests_get_first_element(void) {
    vec *v = vec_new(4);
    CHECK(v);
    int a = 5;
    CHECK(vec_push(v, &a) == 0);
    CHECK(vec_get(v, 0) == &a);
    vec_free(v);
}

static void tests_get_second_element(void) {
    vec *v = vec_new(4);
    CHECK(v);
    int a = 5;
    int b = 7;
    int c = 33;
    CHECK(vec_push(v, &a) == 0);
    CHECK(vec_push(v, &b) == 0);
    CHECK(vec_push(v, &c) == 0);

    CHECK(vec_get(v, 1) == &b);
    vec_free(v);
}

static void tests_get_greater_than_cap(void) {
    vec *v = vec_new(4);
    CHECK(v);
    int a = 5;
    int b = 7;
    int c = 33;
    CHECK(vec_push(v, &a) == 0);
    CHECK(vec_push(v, &b) == 0);
    CHECK(vec_push(v, &c) == 0);

    // CHECK(vec_get(v, 5) == NULL);
    vec_free(v);
}

    // Overflow cap check?? Probably not here
// static void tests_cap_max_size(void) {
//     vec *v = vec_with_capacity(1, SIZE_MAX - 1);
//     CHECK(v);
//     char a = 'a';
//     CHECK(vec_push(v, &a) == 0);
//     CHECK(vec_push(v, &a) == -1);
//     vec_free(v);
// }

int main(void) {
    // vec_new
    RUN_TEST(tests_new_happy_path);
    RUN_TEST(tests_new_elem_size_0);

    // vec_with_capacity
    RUN_TEST(tests_new_capacity_happy_path);
    RUN_TEST(tests_new_capacity_elem_size_0);
    RUN_TEST(tests_new_capacity_cap_size_0);

    // vec_len
    RUN_TEST(tests_len_happy_path);

    // vec_cap
    RUN_TEST(tests_cap_happy_path);

    // vec_is_empty
    RUN_TEST(tests_is_empty_happy_path);
    RUN_TEST(tests_is_empty_added_element);

    // vec_get
    RUN_TEST(tests_get_first_element);
    RUN_TEST(tests_get_second_element);
    RUN_TEST(tests_get_greater_than_cap);

    TEST_SUMMARY();
}
