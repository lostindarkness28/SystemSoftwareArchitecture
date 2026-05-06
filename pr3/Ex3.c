#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/resource.h>
#include <string.h>

void handle_xfsz(int sig) {
    printf("\n[!] Отримано сигнал SIGXFSZ: Досягнуто максимальний розмір файлу!\n");
    exit(0);
}

int main() {
    struct rlimit rl;
    const char *filename = "dice_results.txt";
    rl.rlim_cur = 1024; 
    rl.rlim_max = 2048; 

    if (setrlimit(RLIMIT_FSIZE, &rl) == -1) {
        perror("Помилка setrlimit");
        return 1;
    }
    signal(SIGXFSZ, handle_xfsz);
    srand(time(NULL));

    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        perror("Помилка відкриття файлу");
        return 1;
    }

    printf("Починаємо кидати кубик. Ліміт файлу: %ld байт.\n", (long)rl.rlim_cur);

    int rolls = 0;
    while (1) {
        int dice = (rand() % 6) + 1;
        if (fprintf(f, "Кидок %d: результат = %d\n", ++rolls, dice) < 0) {
            break;
        }
        
        fflush(f);
        printf("Кидок %d записано...\n", rolls);
        usleep(50000); 
    }

    fclose(f);
    return 0;
}
