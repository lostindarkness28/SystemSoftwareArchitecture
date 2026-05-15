#include <stdio.h>
#include <stdlib.h>

int main() {
    int xa = 1000000;
    int xb = 1000000;
    int num = xa * xb;

    printf("xa = %d, xb = %d\n", xa, xb);
    printf("num (overflow): %d\n", num);
    printf("As size_t: %zu\n", (size_t)num);

    void *ptr = malloc(num);
    if (ptr == NULL) {
        perror("malloc failed");
    } else {
        free(ptr);
    }

    printf("\nTesting malloc(-1):\n");
    void *ptr2 = malloc(-1);
    if (ptr2 == NULL) {
        perror("malloc failed for -1");
    }

    return 0;
}
