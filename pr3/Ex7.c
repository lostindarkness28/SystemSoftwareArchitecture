#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    printf("Starting memory allocation loop...\n");
    printf("Check ulimit -v to see the current shell limit.\n");

    int block_size = 10 * 1024 * 1024;
    int total_allocated = 0;

    while (1) {
        void *ptr = malloc(block_size);
        
        if (ptr == NULL) {
            printf("\n[!] MALLOC FAILED!\n");
            printf("Total allocated before failure: %d MB\n", total_allocated);
            return 1;
        }

        memset(ptr, 0, block_size);
        total_allocated += 10;
        printf("Allocated: %d MB\n", total_allocated);
        usleep(100000); 
    }

    return 0;
}
