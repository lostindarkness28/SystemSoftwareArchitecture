#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    int count = 0;
    FILE *f;

    printf("Start opening files...\n");

    while (1) {
        f = fopen("/dev/null", "r");

        if (f == NULL) {
            printf("Open failed: %s\n", strerror(errno));
            break;
        }

        count++;
    }

    printf("Limit reached. Total opened files in loop: %d\n", count);
    
    return 0;
}
