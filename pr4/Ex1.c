#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    size_t max_size = SIZE_MAX;
    printf("sizeof(size_t) = %zu bytes\n", sizeof(size_t));
    printf("Max size_t: %zu (0x%zx)\n", max_size, max_size);

    void *ptr = malloc(max_size);
    if (ptr == NULL) {
        perror("malloc failed");
    } else {
        printf("Success!\n");
        free(ptr);
    }

    size_t half_max = max_size / 2;
    printf("Trying to allocate 1/2 of size_t: %zu\n", half_max);
    ptr = malloc(half_max);
    if (ptr == NULL) {
        perror("malloc failed");
    } else {
        printf("Success!\n");
        free(ptr);
    }

    return 0;
}
