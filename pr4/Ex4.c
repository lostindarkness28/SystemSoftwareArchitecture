#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void broken_variant() {
    printf("Running Broken Variant\n");
    void *ptr = NULL;
    int i = 0;
    while (i < 2) {
        if (!ptr) {
            ptr = malloc(100);
            printf("Allocated at: %p\n", ptr);
        }
        strcpy((char*)ptr, "test"); 
        printf("Step %d: Used ptr %p\n", i, ptr);
        
        free(ptr);
        i++;
    }
}
void correct_variant() {
    printf("\nRunning Correct Variant\n");
    void *ptr = NULL;
    int i = 0;
    while (i < 2) {
        if (!ptr) {
            ptr = malloc(100);
            printf("Allocated at: %p\n", ptr);
        }
        strcpy((char*)ptr, "test");
        printf("Step %d: Used ptr %p\n", i, ptr);
        
        free(ptr);
        ptr = NULL; 
        i++;
    }
}
int main() {
    correct_variant();
    broken_variant();
    return 0;
}
