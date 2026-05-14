#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <signal.h>
#include <unistd.h>

void handle_segv(int sig) {
    printf("\n[!] SIGSEGV received: Stack overflow or memory limit reached!\n");
    exit(1);
}

void recursive_function(int depth) {
    char buffer[1024]; 
    if (depth % 100 == 0) {
        printf("Current depth: %d\n", depth);
    }
    recursive_function(depth + 1);
}

int main() {
    struct rlimit rl;
    rl.rlim_cur = 64 * 1024;
    rl.rlim_max = 64 * 1024;

    if (setrlimit(RLIMIT_STACK, &rl) == -1) {
        perror("setrlimit error");
        return 1;
    }

    signal(SIGSEGV, handle_segv);

    printf("Starting recursive function. Stack limit: %ld bytes.\n", (long)rl.rlim_cur);

    recursive_function(1);

    return 0;
}
