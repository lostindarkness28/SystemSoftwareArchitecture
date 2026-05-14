#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/resource.h>

void handle_sigxcpu(int sig) {
    printf("\n[!] SIGXCPU received: CPU time limit exceeded!\n");
    exit(0);
}

void draw_numbers(int count, int max) {
    int numbers[count];
    for (int i = 0; i < count; i++) {
        int unique;
        do {
            unique = 1;
            numbers[i] = (rand() % max) + 1;
            for (int j = 0; j < i; j++) {
                if (numbers[i] == numbers[j]) {
                    unique = 0;
                    break;
                }
            }
        } while (!unique);
    }

    printf("Lottery %d of %d: ", count, max);
    for (int i = 0; i < count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
}

int main() {
    struct rlimit rl;
    
    rl.rlim_cur = 1; 
    rl.rlim_max = 2; 

    if (setrlimit(RLIMIT_CPU, &rl) == -1) {
        perror("setrlimit error");
        return 1;
    }

    signal(SIGXCPU, handle_sigxcpu);
    srand(time(NULL));

    printf("Starting lottery simulation. CPU limit: %ld sec.\n", (long)rl.rlim_cur);

    while (1) {
        draw_numbers(7, 49);
        draw_numbers(6, 36);
        usleep(100000); 
    }

    return 0;
}
