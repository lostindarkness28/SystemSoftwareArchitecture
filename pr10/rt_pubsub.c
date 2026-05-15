#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int app_signal(void) {
    return SIGRTMIN;
}

static void subscriber(int timeout) {
    int sig = app_signal();

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, sig);

    sigprocmask(SIG_BLOCK, &set, NULL);

    printf("subscriber PID=%ld\n", (long)getpid());

    while (1) {
        siginfo_t si;
        memset(&si, 0, sizeof(si));

        int r;
        if (timeout)
            r = sigtimedwait(&set, &si, &(struct timespec){5,0});
        else
            r = sigwaitinfo(&set, &si);

        if (r == -1) {
            if (errno == EAGAIN) {
                puts("timeout");
                continue;
            }
            continue;
        }

        printf("got %d value=%d\n", r, si.si_value.sival_int);

        if (si.si_value.sival_int < 0)
            break;
    }
}

static void publisher(pid_t pid, int argc, char **argv) {
    int sig = app_signal();

    for (int i = 3; i < argc; i++) {
        union sigval v;
        v.sival_int = atoi(argv[i]);
        sigqueue(pid, sig, v);
    }
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;

    if (!strcmp(argv[1], "sub"))
        subscriber(0);
    else if (!strcmp(argv[1], "sub-timeout"))
        subscriber(1);
    else if (!strcmp(argv[1], "pub"))
        publisher(atoi(argv[2]), argc, argv);

    return 0;
}
