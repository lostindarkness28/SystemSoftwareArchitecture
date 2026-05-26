#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

long get_memory_usage(pid_t pid) {
    char path[40];

    if (sprintf(path, "/proc/%d/statm", pid) < 0) {
        perror("Error: Failed to generate path string");
        return 0;
    }

    FILE* fp = fopen(path, "r");
    if (!fp) {
        return 0;
    }

    long pages = 0;
    if (fscanf(fp, "%ld", &pages) != 1) {
        pages = 0;
    }

    fclose(fp);

    long page_size = sysconf(_SC_PAGESIZE);
    if (page_size == -1) {
        perror("Error: sysconf failed to get page size");
        return 0;
    }
    return pages * page_size / 1024;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <command> [arguments...]\n", argv[0]);
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Error: fork failed"); 
        return 1;
    }

    if (pid == 0) {
        execvp(argv[1], &argv[1]);

        perror("Error: execvp failed (command not found)");
        exit(1);
    }

    else {
        int status;
        long max_memory = 0;
        long current_mem;
        pid_t wait_res;

        printf("[Monitor] Started process with PID: %d\n", pid);

        while (1) {
            wait_res = waitpid(pid, &status, WNOHANG);
            if (wait_res == -1) {
                perror("Error: waitpid failed");
                break;
            }
            if (wait_res == pid) {
                break;
            }

            current_mem = get_memory_usage(pid);
            if (current_mem > max_memory) {
                max_memory = current_mem;
            }

            if (usleep(50000) == -1) {
                continue;
            }
        }

        printf("\nProcess statistics:\n");

        if (WIFEXITED(status)) {
            printf("Exit code: %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Exit status: Process was killed by signal %d\n", WTERMSIG(status));
        } else {
            printf("Exit status: Process terminated abnormally\n");
        }

        printf("Peak memory usage: %ld KB (%.2f MB)\n",
               max_memory, (float)max_memory / 1024.0);
    }

    return 0;
}
