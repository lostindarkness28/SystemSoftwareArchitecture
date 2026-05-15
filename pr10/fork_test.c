#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Parent PID: %d\n", getpid());

    fork();
    fork();

    printf("PID=%d PPID=%d\n", getpid(), getppid());

    return 0;
}
