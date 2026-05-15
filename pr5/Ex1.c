#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *p = (char*)malloc(32);
    strcpy(p, "HELLO_WORLD");

    free(p);

    // Імітація повторного використання пам’яті
    for (int i = 0; i < 10000; i++) {
        char *tmp = (char*)malloc(32);
        strcpy(tmp, "XXXXXXXXXXXX");
    }

    // Використання звільненої пам’яті
    printf("OLD DATA: %s\n", p);

    return 0;
}
