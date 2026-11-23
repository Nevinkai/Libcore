//
// Created by nevinkai on 11/1/26.
//

#ifndef LIBCORE_VEC_H
#define LIBCORE_VEC_H
#include <stdlib.h>

typedef struct {
    void *data;
    size_t len, cap, elem_size;
} vec;

/* Lifecycle */

/**
 *
 * @param elem_size
 * @return
 */
vec *vec_new(size_t elem_size);

vec *vec_with_capacity(size_t elem_size, size_t cap);

void vec_free(vec *v);

/* Info */
size_t vec_len(const vec *v);

size_t vec_cap(const vec *v);

int vec_is_empty(const vec *v);

/* Access (index must be < len; checked with assert) */
void *vec_get(const vec *v, size_t i);

void vec_set(vec *v, size_t i, const void *elem);

void *vec_data(const vec *v); /* pointer to first element, or NULL if empty */

/* Modifying */
int vec_push(vec *v, const void *elem);

int vec_pop(vec *v, void *out); /* out may be NULL; -1 if empty */
int vec_insert(vec *v, size_t i, const void *elem); /* i <= len */
int vec_remove(vec *v, size_t i, void *out); /* shifts later items left */
void vec_swap(vec *v, size_t i, size_t j);

void vec_clear(vec *v); /* len = 0, keeps capacity */

/* Capacity */
int vec_reserve(vec *v, size_t additional); /* ensure room for len + additional */
int vec_shrink_to_fit(vec *v);

/* Algorithms */
void vec_sort(vec *v, int (*cmp)(const void *, const void *)); /* may use qsort */
long vec_find(const vec *v, const void *elem,
              int (*cmp)(const void *, const void *)); /* index, or -1 */

#endif //LIBCORE_VEC_H
