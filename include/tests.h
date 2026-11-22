//
// Created by nevin on 11/21/2026.
//

#include <stdio.h>

static int tests_run = 0, tests_failed = 0, current_failed = 0;

#ifndef LIBCORE_TESTS_H
#define LIBCORE_TESTS_H

#define CHECK(cond) do { \
    if (!(cond)) { \
        fprintf(stderr, "  FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond); \
        current_failed = 1; \
    } } while (0)

#define CHECK_EQ_INT(a, b) do { \
    long _a = (a), _b = (b); \
    if (_a != _b) { \
        fprintf(stderr, "  FAIL %s:%d: %s == %s (got %ld, expected %ld)\n", \
                __FILE__, __LINE__, #a, #b, _a, _b); \
        current_failed = 1; \
    } } while (0)

#define RUN_TEST(fn) do { \
    current_failed = 0; tests_run++; fn(); \
    if (current_failed) { tests_failed++; printf("[FAIL] %s\n", #fn); } \
    else printf("[ OK ] %s\n", #fn); \
    } while (0)

#define TEST_SUMMARY() \
    (printf("\n%d/%d passed\n", tests_run - tests_failed, tests_run), tests_failed ? 1 : 0)

#endif //LIBCORE_TESTS_H
