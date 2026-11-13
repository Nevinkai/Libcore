#include <stdio.h>
//
// Created by nevinkai on 10/31/26.
//
void print_bytes(const void *p, size_t n) {
    const unsigned char *c = p;
    for (size_t i = 0; i < n; i++) {
        printf("%02hhX\n", c[i]);
    }
}

typedef struct {
    int integers;
    char characters;
    float floats;
    double doubles;
    long double longs;
} allOfTypes;

int main() {
    int a = 100;

    printf("Int bytes \n");
    print_bytes(&a, sizeof(int));

    double b = 525245346;
    printf("Double bytes \n");
    print_bytes(&b, sizeof(double));

    allOfTypes v = {654, 'b', 432.123, 423521521, 521453416316316};

    printf("Struct\n");
    print_bytes(&v, sizeof(allOfTypes));
}
