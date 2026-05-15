#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>

void handler(int sig, siginfo_t *info, void *context)
{
    (void)sig;
    (void)context;

    printf("\n=== SIGBUS detected ===\n");

    if (info->si_code == BUS_ADRERR)
    {
        printf("Причина: помилка доступу до фізичної пам'яті або вирівнювання\n");
    }
    else if (info->si_code == BUS_OBJERR)
    {
        printf("Причина: помилка mmap або відображеного файлу\n");
    }
    else
    {
        printf("Невідома причина SIGBUS\n");
    }

    printf("Адреса помилки: %p\n", info->si_addr);
    exit(1);
}

int main()
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));

    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;

    sigaction(SIGBUS, &sa, NULL);

    printf("Створення mmap області...\n");

    int fd = open("testfile.bin", O_RDWR | O_CREAT, 0666);
    ftruncate(fd, 100);

    char *map = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    printf("Спроба доступу за межі mmap...\n");

    map[5000] = 'A';

    return 0;
}
