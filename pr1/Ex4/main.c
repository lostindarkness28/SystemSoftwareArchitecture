#include <aio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd < 0) {
        perror("Помилка відкриття файлу");
        return 1;
    }

    const char* msg = "Асинхронний запис!\n";

    struct aiocb cb;
    memset(&cb, 0, sizeof(cb));
    cb.aio_fildes = fd;
    cb.aio_buf =(void*) msg;
    cb.aio_nbytes = strlen(msg);
    cb.aio_offset = 0;

    aio_write(&cb);

    for(int i=0; i<5; i++) {
        printf("Основний потік працює: %d\n", i);
        usleep(200000);
    }


    printf("Асинхронна запис завершена!\n");
    close(fd);

    return 0;
}
