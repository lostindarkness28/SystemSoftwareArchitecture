#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main() {  
    void *ptr = malloc(1024);
    printf("Initial pointer: %p\n", ptr);

    size_t huge_size = SIZE_MAX;
    void *new_ptr = realloc(ptr, huge_size);

    if (new_ptr == NULL) {
        printf("realloc failed as expected: returned NULL\n");
        printf("Old pointer is still valid: %p\n", ptr);
        free(ptr); 
    } else {
        printf("Success? This shouldn't happen with SIZE_MAX!\n");
        free(new_ptr);
    }
    return 0;
}
