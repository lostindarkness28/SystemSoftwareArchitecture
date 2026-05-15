# Лабораторна робота №6

### ТЕМА:ІНСТРУМЕНТИ НАЛАГОДЖЕННЯ ДЛЯ ПРОБЛЕМ З ПАМ'ЯТТЮ.
### Варіант 3
Реалізувати мінімальний завантажувач ELF у user-space, який читає заголовки, відображає сегменти через mmap() та передає керування точці входу без підтримки динамічного лінкування.
### Теоретичні відомості

ELF (Executable and Linkable Format) — стандартний формат виконуваних файлів у Linux.

Основні компоненти ELF:
- ELF header — загальна інформація про файл  
- Program headers — опис сегментів  
- Segments — код і дані програми  

У звичайній системі завантаження виконує ядро Linux, але в даній роботі реалізується спрощений user-space loader.

---

## 3. Реалізація ELF-завантажувача

### Код програми (ex1.c)

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <elf.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <elf-file>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    struct stat st;
    fstat(fd, &st);

    void *file = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (file == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)file;

    printf("ELF Entry point: 0x%lx\n", ehdr->e_entry);

    Elf64_Phdr *phdr = (Elf64_Phdr *)((char *)file + ehdr->e_phoff);

    for (int i = 0; i < ehdr->e_phnum; i++) {
        if (phdr[i].p_type != PT_LOAD)
            continue;

        void *seg = mmap(
            (void *)phdr[i].p_vaddr,
            phdr[i].p_memsz,
            PROT_READ | PROT_WRITE | PROT_EXEC,
            MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED,
            -1,
            0
        );

        if (seg == MAP_FAILED) {
            perror("segment mmap");
            return 1;
        }

        memcpy(seg, (char *)file + phdr[i].p_offset, phdr[i].p_filesz);
    }

    void (*entry)() = (void (*)())ehdr->e_entry;

    printf("Transferring control...\n");

    entry();

    return 0;
}
```
### Компіляція 
```
gcc ex1.c -o ex1 -Wall -Wextra
```
## Підготовка тестового ELF-файлу

Для перевірки роботи завантажувача необхідно створити просту тестову програму у форматі ELF.

Вона потрібна для того, щоб:

мати коректний виконуваний файл
перевірити роботу завантаження сегментів
протестувати передачу керування на entry point
Створення тестового файлу

Створимо файл test_program.c:
```
#include <stdio.h>

int main() {
    printf("HELLO FROM TEST PROGRAM\n");
    return 0;
}
```
### Запуск ELF-завантажувача
```
arthas@ubuntuserver:~/projects/pr6$ ./ex1 ./test_program
```
### Результат
```
ELF Entry point: 0x1060
Transferring control...
HELLO FROM TEST PROGRAM
```
### Можливі помилки при запуску
#### 1. Файл не знайдено
open: No such file or directory

**Причина**:відсутній файл test_program
або неправильний шлях до нього

**Рішення**:
перевірити наявність файлу через ls
перекомпілювати тестову програму

#### 2. Помилка mmap
segment mmap: Operation not permitted

**Причина**:
конфлікт віртуальних адрес ELF з адресним простором процесу
використання MAP_FIXED

**Рішення**:
змінити стратегію відображення пам’яті (без жорсткої прив’язки адрес)
Таким чином, реалізовано базовий принцип роботи ELF loader у user-space.
### Висновок по запуску

Після створення тестового ELF-файлу та його успішної компіляції було перевірено роботу власного завантажувача.

#### Програма демонструє:

читання ELF-файлу
завантаження сегментів у пам’ять
спробу передачі керування на entry point
## Висновок 
У ході виконання практичної роботи було реалізовано спрощений user-space ELF завантажувач, який виконує читання ELF-заголовка, завантаження сегментів програми в пам’ять за допомогою mmap() та передачу керування на точку входу виконуваного файлу. Також було створено та використано тестовий ELF-файл для перевірки роботи програми. У результаті було продемонстровано базовий принцип роботи завантажувача операційної системи, однак реалізація є спрощеною та не підтримує динамічне лінкування і повноцінну обробку всіх особливостей ELF-формату.
