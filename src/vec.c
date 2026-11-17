//
// Created by nevinkai on 11/1/26.
//
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "../include/vec.h"
#include <stdbool.h>

#include <string.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define CAPMULTIPLIER 2
#define BUF 256

/* Helper Functions */
static int vec_change_cap(vec *v, size_t new_cap) {
    // Overflow check
    if (new_cap > SIZE_MAX / v->elem_size) {
        return -1;
    }

    // Cap size 0 check, prevent null pointers
    if (new_cap == 0) {
        return -1;
    }

    // Null check
    void *temp = realloc(v->data, v->elem_size * new_cap);
    if (!temp) {
        free(v->data);
        v->data = NULL;
        return -1;
    }

    v->data = temp;
    v->cap = new_cap;
    return 0;
}

static int vec_allocate_data(vec *v) {
    // Overflow check
    if (v->cap > SIZE_MAX / v->elem_size) {
        return -1;
    }

    // Null check
    void *temp = malloc(v->elem_size * v->cap);
    if (!temp) {
        return -1; // Failed to get new pointer
    }

    v->data = temp;
    return 0;
}

static int vec_ensure_room(vec *v) {
    // Assign data pointer if its null
    if (!v->data) {
        int errorCode = vec_allocate_data(v);

        if (errorCode) {
            return -1;
        }
    }

    if (v->len == v->cap) {
        size_t newCap;

        // Check if cap is 0, then set it to 1 if it is zero
        if (v->cap == 0) {
            newCap = 1;
        } else {
            newCap = v->cap * CAPMULTIPLIER;
        }

        int errorCode = vec_change_cap(v, newCap);
        if (errorCode) {
            return -1;
        }
    }

    return 0;
}

static void swap_any(void *a, void *b, size_t size) {
    unsigned char *ptr1 = a;
    unsigned char *ptr2 = b;

    // Check memory addresses to see if they are the same variable
    if (ptr1 == ptr2) {
        return;
    }

    // Catch illegal sizes
    if (size == 0) return;

    // Create buffer, and store size in another variable
    unsigned char temp[BUF];
    size_t remaining = size;

    // size_t chunkSize = MIN(remaining, BUF);

    while (true) {
        // Check which size is smaller, the buffer or the remaining bytes

        size_t chunkSize = MIN(remaining, BUF);

        // Copy memory one buffer chunk at a time
        memcpy(temp, ptr1, chunkSize);
        memcpy(ptr1, ptr2, chunkSize);
        memcpy(ptr2, temp, chunkSize);

        // If remaining is less than BUF, then the loop is done
        if (remaining <= BUF) {
            break;
        }

        // Track amount of iterations, and subtract the buffer amount from remaining, so the program does not repeat bytes
        ptr1 += chunkSize;
        ptr2 += chunkSize;
        remaining -= BUF;
    }
}

/* Lifecycle */

vec *vec_new(size_t elem_size) {
    // Check if elem_size is 0, to prevent program from crashing later
    if (elem_size == 0) {
        return NULL;
    }

    vec *vectemp = malloc(sizeof(vec));

    // Check for null
    if (!vectemp) {
        return NULL;
    }

    // Assign default values
    vectemp->data = NULL;
    vectemp->len = 0;
    vectemp->cap = 0; //
    vectemp->elem_size = elem_size;

    return vectemp;
}

vec *vec_with_capacity(size_t elem_size, size_t cap) {
    vec *vectemp = malloc(sizeof(vec));

    // Check for null
    if (!vectemp) {
        return NULL;
    }

    // Check for overflow
    if (cap > SIZE_MAX / elem_size) {
        free(vectemp);
        return NULL;
    }

    // Assign default values
    vectemp->data = NULL; // TODO set data
    vectemp->len = 0;
    vectemp->cap = cap;
    vectemp->elem_size = elem_size;

    int error_code = vec_ensure_room(vectemp);
    if (error_code == -1) {
        free(vectemp);
        return NULL;
    }

    return vectemp;
}

void vec_free(vec *v) {
    // Check for null
    if (!v) {
        return;
    }

    free(v->data);
    free(v);
}

/* Info */
size_t vec_len(const vec *v) {
    return v->len;
}

size_t vec_cap(const vec *v) {
    return v->cap;
}

int vec_is_empty(const vec *v) {
    return v->len == 0;
}

/* Access (index must be < len; checked with assert) */
void *vec_get(const vec *v, size_t i) {
    assert(i < v->len);

    unsigned char *bytes = v->data; // Convert to unsinged char for proper pointer arithmetic
    return &bytes[i * v->elem_size];
}

void vec_set(vec *v, size_t i, const void *elem) {
    assert(i < v->len);

    unsigned char *bytes = v->data; // Convert to unsinged char for proper pointer arithmetic
    memcpy(bytes + i * v->elem_size, elem, v->elem_size);
}

/* pointer to first element, or NULL if empty */
void *vec_data(const vec *v) {
    if (!v->data || v->len == 0) {
        return NULL;
    }

    unsigned char *bytes = v->data; // Convert to unsinged char for proper pointer arithmetic

    return &bytes[0];
}

/* Modifying */
int vec_push(vec *v, const void *elem) {
    int errorCode = vec_ensure_room(v);
    if (errorCode == -1) {
        return -1;
    }

    unsigned char *bytes = v->data;
    memcpy(bytes + v->len * v->elem_size, elem, v->elem_size);
    v->len += 1;

    return 0;
}

/* out may be NULL; -1 if empty */
int vec_pop(vec *v, void *out) {
    // Empty vector
    if (!v->data || v->len == 0) {
        return -1;
    }

    v->len -= 1;

    // Don't copy any bytes if out is null
    if (out == NULL) {
        return 0;
    }

    unsigned char *bytes = v->data;
    memcpy(out, bytes + v->len * v->elem_size, v->elem_size);

    return 0;
}

/* i <= len */
int vec_insert(vec *v, size_t i, const void *elem) {
    assert(i <= v->len);

    int errorCode = vec_ensure_room(v);
    if (errorCode == -1) {
        return -1;
    }

    unsigned char *bytes = v->data;
    unsigned char *source = bytes + i * v->elem_size;

    // Shift elements starting from the index to the right by one
    memmove(source + v->elem_size, source, (v->len - i) * v->elem_size);

    // Insert data into empty position
    memcpy(bytes + i * v->elem_size, elem, v->elem_size);
    v->len += 1;

    return 0;
}

/* shifts later items left */
int vec_remove(vec *v, size_t i, void *out) {
    assert(i < v->len);

    unsigned char *bytes = v->data;
    unsigned char *source = bytes + i * v->elem_size;

    v->len -= 1;

    // Copy element to pointer, then elements to the right to the left by one
    memcpy(out, source, v->elem_size);

    // Don't copy any bytes if out is null
    if (out == NULL) {
        return 0;
    }

    memmove(source, source + v->elem_size, (v->len - i) * v->elem_size);



    return 0;
}

void vec_swap(vec *v, size_t i, size_t j) {
    assert(i < v->len);
    assert(j < v->len);

    unsigned char *bytes = v->data;
    unsigned char *ptr1 = bytes + i * v->elem_size;
    unsigned char *ptr2 = bytes + j * v->elem_size;

    swap_any(ptr1, ptr2, v->elem_size);
}

/* len = 0, keeps capacity */
void vec_clear(vec *v) {
    v->len = 0;
}

/* Capacity */
/* ensure room for len + additional */
int vec_reserve(vec *v, size_t additional) {
    // Don't resize if sum of additional and len is less than or equal to vector cap
    // if (v->len + additional <= v->cap) {
    //     return 0;
    // }

    // Possible fix
    if (v->len >= v->cap - additional) {
        return 0;
    }

    // realloc
    int error_code = vec_change_cap(v, v->len + additional);
    if (error_code == -1) {
        return -1;
    }

    return 0;
}

int vec_shrink_to_fit(vec *v) {
    if (v->len == v->cap) {
        return 0;
    }

    int error_code = vec_change_cap(v, v->len);
    if (error_code == -1) {
        return -1;
    }

    return 0;
}

/* Algorithms */
/* may use qsort */
void vec_sort(vec *v, int (*cmp)(const void *, const void *)) {
    // Check if vector is empty to prevent undefined behavior
    if (v->len == 0) {
        return;
    }

    qsort(v->data, v->len, v->elem_size, cmp);
}

long vec_find(const vec *v, const void *elem, int (*cmp)(const void *, const void *)) {
    char *bytes = v->data;

    /* index, or -1 */
    for (size_t i = 0; i < v->len; i++) {
        int result = cmp(elem, bytes + i * v->elem_size);
        if (result == 0) {
            return (long) i;
        }
    }

    return -1;
}
