#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t len, cap;
} intvec;

int reallocCounter = 0;

void intvec_init(intvec *v) {
    v->data = NULL;
    v->len = 0;
    v->cap = 0;
}

int intvec_push(intvec *v, const int x) {
    // Check if the vector either has no length, or if the len and cap are equal, then double the array
    if (v->len == v->cap && v->cap != 0) {
        size_t newCap = v->cap * 2;

        // Check for overflow
        if (newCap > SIZE_MAX / sizeof(int)) {
            return -1;
        }

        // int *oldPointer = v->data;
        // have to store old pointer before calling realloc,
        // don't need to check actually, realloc automatically frees old address when successful

        // Null check
        int *temp = realloc(v->data, sizeof(int) * newCap);
        if (!temp) {
            return -1; // Failed to get new pointer
        }

        v->data = temp;

        v->cap = newCap; // cap only changed when realloc is successful
        reallocCounter++;
    }

    // Assign data pointer if its null
    if (!v->data) {
        // Null check
        int *temp = malloc(sizeof(int));
        if (!temp) {
            return -1; // Failed to get new pointer
        }

        v->data = temp;
        v->cap = 1;
    }

    v->data[v->len] = x; // Put value at vec length
    v->len += 1;

    return 0;
}

int intvec_pop(intvec *v, int *out) {
    // Empty vector
    if (!v->data || v->len == 0) {
        return -1;
    }

    // Check if out is null
    if (!out) {
        return -1;
    }

    v->len -= 1;
    *out = v->data[v->len];

    return 0;
}

/*
 */
void intvec_free(intvec *v) {
    int **data = &v->data;

    free(*data);

    *data = NULL; // Most C libraries do this when free data structure

    v->len = 0;
    v->cap = 0;
}

int main(void) {
    intvec v;
    intvec_init(&v);

    for (int i = 0; i <= 1000000; i++) {
        int error = intvec_push(&v, i);

        if (error == -1) {
            intvec_free(&v);
            return -1;
        }
    }

    printf("%d\n", reallocCounter);
    intvec_free(&v);
}
