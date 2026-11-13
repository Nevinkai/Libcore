#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Take s and duplicate it
char *my_strdup(const char *s) {
    size_t stringSize = strlen(s); // Does not include null terminator

    char *dupS = malloc(stringSize + 1);

    dupS = strcpy(dupS, s);

    if (!dupS)
        return NULL;

    return dupS;
}

char *my_strndup(const char *s, size_t n) {

    char *dupS = malloc(n + 1);

    // char *stringSection = dupS;
    for(size_t i = 0; i <= n; i++) {
        dupS[i] = s[i];
    } 

    dupS[n+1] = '\0';

    return dupS;
}

int main(void) {
    char hello[] = "Hello World!";
    char *test;

    test = my_strdup(hello);

    printf("%s\n", test);
    printf("%s\n", hello);

    test[0] = 't';
    hello[0] = 'n'; // Breaks when I edit hello string pointer, why? Because *hello is put into the read-only data section of the program,
    // while test is put into the heap, which does allow write access, switch to array to allow write access

    printf("%s\n", test);
    printf("%s\n", hello);

    free(test);

}

