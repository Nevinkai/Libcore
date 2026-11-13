#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define BUF 256

void swap_any(void *a, void *b, size_t size) {
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

typedef struct {
    int integers;
    char characters;
    float floats;
    double doubles;
    long double longs;
} allOfTypes;

int main(void) {
    int a = 19;
    int b = 453;

    printf("Ints\n");
    printf("A: %d\n", a);
    printf("B: %d\n", b);

    swap_any(&a, &b, sizeof(int));

    printf("A: %d\n", a);
    printf("B: %d\n", b);

    double c = 3423.432;
    double d = 8768.43;

    printf("Doubles\n");
    printf("C: %f\n", c);
    printf("D: %f\n", d);

    swap_any(&c, &d, sizeof(double));

    printf("C: %f\n", c);
    printf("D: %f\n", d);

    allOfTypes v1 = {654, 'b', 432.123, 423521521, 521453416316316};
    allOfTypes v2 = {4252, 'y', 13093.44802564, 609781595, 21643769626453};

    printf("Structs\n");
    printf("v1: %d, %c, %f, %f, %Lf \n", v1.integers, v1.characters, v1.floats, v1.doubles, v1.longs);
    printf("v2: %d, %c, %f, %f, %Lf \n", v2.integers, v2.characters, v2.floats, v2.doubles, v2.longs);

    swap_any(&v1, &v2, sizeof(allOfTypes));

    printf("v1: %d, %c, %f, %f, %Lf \n", v1.integers, v1.characters, v1.floats, v1.doubles, v1.longs);
    printf("v2: %d, %c, %f, %f, %Lf \n", v2.integers, v2.characters, v2.floats, v2.doubles, v2.longs);

    char ia[1000];

    for (int i = 0; i < 1000; i++) {
        ia[i] = 'a';
    }

    char ib[1000];

    for (int i = 0; i < 1000; i++) {
        ib[i] = 'b';
    }

    printf("IA:");
    for (int i = 0; i < 1000; i++) {
        printf("%c", ia[i]);
    }
    printf("\n");

    printf("IB:");
    for (int i = 0; i < 1000; i++) {
        printf("%c", ib[i]);
    }
    printf("\n");

    swap_any(&ia, &ib, sizeof(char) * 1000);

    printf("IA:");
    for (int i = 0; i < 1000; i++) {
        printf("%c", ia[i]);
    }
    printf("\n");

    printf("IB:");
    for (int i = 0; i < 1000; i++) {
        printf("%c", ib[i]);
    }
    printf("\n");

    swap_any(&v1, &v1, sizeof(allOfTypes));
}
