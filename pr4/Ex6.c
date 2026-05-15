#include <stdio.h>
#include <stdlib.h>

int main() {
    realloc(NULL, size) 
    void *ptr1 = realloc(NULL, 100);
    if (ptr1 != NULL) {
        printf("realloc(NULL, 100) success: %p\n", ptr1);
    }

    realloc(ptr, 0) 
    void *ptr2 = realloc(ptr1, 0);
    printf("realloc(ptr1, 0) returned: %p\n", ptr2);
    printf("ptr1 is now freed.\n");

    return 0;
}
