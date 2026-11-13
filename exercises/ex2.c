#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *join_words(const char *a, const char *b);

int main(void) {
    char *hello = join_words("Hello", "World!");

    printf("%s\n", hello);
    free(hello);
}

char *join_words(const char *a, const char *b) {
    char *out;
    char *temp = malloc(strlen(a) + strlen(b) + 2); // Needed one more byte for null terminator.

    if (!temp) // Added null checking
        return NULL;
    out = temp;

    strcpy(out, a);
    strcat(out, " ");
    strcat(out, b);
    return out;
}