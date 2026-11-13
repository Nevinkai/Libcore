#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    /* (a) 
        This code an array to the heap (withnout null checking), and tries to access
        an int outside of the array's bounds, so there will be undefined behavior

        As I expected, the
    */
    // int *p = malloc(3 * sizeof *p);
    // p[3] = 7;
    // printf("%d\n", p[3]);
    // free(p);



    /* (b) 
        Does not allocate space for the null terminator, so will write outside of array's bounds.
        Use after free
    */
    // char *s = malloc(6);
    // strcpy(s, "hello");
    // free(s);
    // printf("%s\n", s);

    /* (c)  
        Memory Leak, pointer to "nevin" string is lost
    */
    char *name = strdup("nevin");
    name = strdup("carroll");
    free(name);
}

