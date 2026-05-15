#include <stdio.h>
#include <stdlib.h>

struct sbar {
    int id;
    char data[64];
};

int main() {
    struct sbar *ptr, *newptr;

    ptr = calloc(1000, sizeof(struct sbar));
    if (!ptr) return 1;
    printf("Initial allocation (calloc): %p\n", ptr);

    newptr = reallocarray(ptr, 500, sizeof(struct sbar));
    if (!newptr) {
        free(ptr);
        return 1;
    }
    printf("Reallocated (reallocarray): %p\n", newptr);

    free(newptr);
    return 0;
}
