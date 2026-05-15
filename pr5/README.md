# Лабораторна робота №5

### Помилки роботи з пам’яттю в Linux та засоби їх усунення
#### Варіант 3
Реалізувати сценарій use-after-free, який проявляється лише після кількох успішних повторних алокацій того ж розміру.
### Теоретичні відомості

У програмуванні на C ручне керування пам’яттю часто призводить до помилок:

- **Use-after-free** — використання пам’яті після її звільнення
- **Memory leak** — витік пам’яті
- **Buffer overflow** — вихід за межі буфера
- **Double free** — подвійне звільнення пам’яті
- **Undefined behavior** — невизначена поведінка

Особливо небезпечним є use-after-free, оскільки він може:
- не викликати помилку одразу
- працювати “ніби нормально”
- призводити до випадкових збоїв або вразливостей
### Реалізація сценарію Use-after-free:
```c
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
```
### Компіляція
```
gcc -g Ex1.c -o Ex1
```
### Запуск програми
```
arthas@ubuntuserver:~/projects/pr5$ ./Ex1
OLD DATA: XXXXXXXXXXXX
```
## Аналіз результату

На перший погляд програма працює коректно і не завершується з помилкою.

Однак це є прикладом помилки **use-after-free**:

- спочатку пам’ять була виділена через `malloc`
- потім вона була звільнена через `free`
- після цього вказівник `p` все ще використовується

Виведене значення (`XXXXXXXXXXXX`) є наслідком того, що:

- звільнена пам’ять була повторно використана алокатором  
- дані в цій області були перезаписані новими значеннями
## Перевірка через Valgrind

При спробі запуску Valgrind було отримано повідомлення про помилку:

```
arthas@ubuntuserver:~/projects/pr5$ valgrind --leak-check=full --track-origins=yes ./ex1
Command 'valgrind' not found, but can be installed with:
sudo apt install valgrind  # version 1:3.22.0-0ubuntu2
```
Для встановлення Valgrind необхідно виконати команду:
```
sudo apt update
sudo apt install valgrind
```
### Результат
```
arthas@ubuntuserver:~/projects/pr5$ valgrind --leak-check=full --track-origins=yes ./Ex1
==211097== Memcheck, a memory error detector
==211097== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==211097== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==211097== Command: ./Ex1
==211097==
==211097== Invalid read of size 1
==211097==    at 0x484F226: strlen (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==211097==    by 0x48CDDA7: __printf_buffer (vfprintf-process-arg.c:435)
==211097==    by 0x48CE73A: __vfprintf_internal (vfprintf-internal.c:1544)
==211097==    by 0x48C31B2: printf (printf.c:33)
==211097==    by 0x109224: main (Ex1.c:18)
==211097==  Address 0x4a78040 is 0 bytes inside a block of size 32 free'd
==211097==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==211097==    by 0x1091C6: main (Ex1.c:9)
==211097==  Block was alloc'd at
==211097==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==211097==    by 0x10919E: main (Ex1.c:6)
==211097==
...
```
## Аналіз результатів Valgrind

Після запуску програми з використанням Valgrind було виявлено помилку роботи з пам’яттю типу **use-after-free**.

Valgrind зафіксував наступні проблеми:

- **Invalid read** — спроба читання даних із пам’яті після її звільнення
- адреса вказує на блок пам’яті, який вже був звільнений через `free`
- помилка виникає при зверненні до вказівника `p` після виклику `free(p)`

Також Valgrind підтвердив, що:

- програма використовує звільнену пам’ять
- поведінка програми є невизначеною
- помилка може не призводити до аварійного завершення, але є критичною

## Висновок
У ході виконання практичної роботи було досліджено основні типи помилок роботи з пам’яттю , зокрема: use-after-free, витоки пам’яті, вихід за межі масиву та невизначену поведінку.

Було реалізовано програму, що демонструє сценарій **use-after-free**, при якому використання пам’яті після її звільнення може не призводити до негайної помилки, але викликає невизначену поведінку програми.

Також було використано інструмент **Valgrind** для аналізу помилок роботи з пам’яттю. Він дозволив виявити:

- використання звільненої пам’яті (Invalid read)
- факт звернення до вже звільненого блоку heap
- наявність невизначеної поведінки програми

У результаті роботи було встановлено, що помилки роботи з пам’яттю можуть бути прихованими і не проявлятися одразу, тому для їх виявлення необхідно використовувати спеціалізовані інструменти, такі як Valgrind.





