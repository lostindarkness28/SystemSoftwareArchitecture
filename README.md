# Практична робота №1

## Огляд
Мета цієї роботи — ознайомитися з процесом налаштування середовища розробки в Ubuntu Linux та опанувати базові навички програмування мовою C, зокрема роботу з математичними бібліотеками та системними викликами.

## Завдання №1: Обчислення інтеграла нормального розподілу
Програма розраховує ймовірність того, що випадкова величина потрапить у заданий довірчий інтервал [-Z; Z], використовуючи функцію помилок `erf`.

1.Правильно скомпілювати програму з використанням бібліотеки math.h.

2.Додати обробку помилок, щоб перевірити правильність виклику erf.

3.Розширити програму, щоб вона обчислювала довірчі інтервали не тільки для 95%, але й double ci90 = 1.64485;
  
4.Додати можливість введення значень від користувача для довірчого інтервалу.

## Компіляція та запуск

### 1. Компіляція
Використовуйте прапорець `-lm` для підключення математичної бібліотеки та `-Wall` для відображення всіх попереджень:
```bash
gcc -Wall Ex1.c -o Ex1 -lm
```

### Запуск програми
```bash
./Ex1
```
### Результат виконання програми

Вводимо значення 1.96
```
Enter Z-score: 1.96
The integral of a Normal (0,1) distribution between -Z and Z i’s: 0.950004
```
Введемо нечислове значення для змінної Z-score
```
Enter Z-score: e
Invalid input!
```
Отримуємо повідомлення про некоректність вводу.
  
### Результати для 90,95 та 99 відсотків
Додаємо 3 зміні double :

ci90 = 1.64485;\
ci95 = 1.95996;\
ci99 = 2.57583;

В результаті виконання програми отримаємо: 
```
Confidence intervals (integral from -Z to Z):
90% CI: 0.899999
95% CI: 0.95
99% CI: 0.99
```
Також додаємо можливість користувачу обрати значення для довірчого інтегралу(серед 90%,95%,99)
```
Enter Z-score: 2
The integral of a Normal (0,1) distribution between -Z and Z i’s: 0.9545

Choose confidence integral:
1 - 90% Confidence Interval
2 - 95% Confidence Interval
3 - 99% Confidence Interval
Your choice: 1
90% CI: 0.899999
```
### Додамо розрахунок для розподілу Стьюдента
В результаті отримаємо
``` 
Enter Z-score: 1.96
Enter degrees of freedom (df): 20
The integral of a Normal (0,1) distribution between -Z and Z i’s: 0.950004
The integral of a Student distribution: 0.947071 (df=20)
```

## Структура проекту
Проєкт реалізовано у вигляді модульної структури для забезпечення чистоти коду та розділення логіки:
* `Ex1.c` — головний файл програми (інтерфейс користувача, введення даних та меню стандартних інтервалів).
* `erf_module.c` — реалізація математичних функцій (логіка обчислень).
* `erf_module.h` — заголовочний файл із прототипами функцій та макросами стандартних Z-значень (`#define`).
## Інструкція з компіляції та запуску
Оскільки проєкт розбитий на модулі, для збірки необхідно скомпілювати всі файли `.c` разом та підключити математичну бібліотеку:

```bash
gcc Ex1.c erf_module.c -o Ex1 -lm
```
#### Запуск 
``` bash
./Ex1
```
## Компіляція з оптимізацією

Для підвищення продуктивності математичних обчислень програму можна скомпілювати з різними рівнями оптимізації компілятора `gcc`:

### Рівень O2 (стандартна оптимізація):
Оптимізує швидкість виконання без значного збільшення розміру файлу.
```bash
gcc -O2 Ex1.c erf_module.c -o Ex1_O2 -lm
```

### Рівень O3 (максимальна оптимізація):
Найвищий рівень оптимізації, який фокусується виключно на швидкості роботи програми. Компілятор намагається максимально розпаралелити обчислення та вбудувати функції безпосередньо в місця їх виклику (inlining).
```bash
gcc -O3 Ex1.c erf_module.c -o Ex1_O3 -lm
```

# Завдання №2:Дослідити бібліотеки доступні у системі
1)Використовуйте команду ldd, щоб перевірити, які бібліотеки використовуються вашими програмами (наприклад, ls або gcc).\
2)Знайдіть бібліотеку з math-функціями, визначте її точне місце розташування (find /usr/lib -name "*math*").\
3)Перевірте символи бібліотеки за допомогою nm або objdump. Наприклад:
 nm -D /usr/lib/libm.so | grep erf\
4)Проаналізуйте залежності бібліотек за допомогою ldd або objdump -p.\
5)Напишіть скрипт на Bash, який аналізує всі бібліотеки у /usr/lib, витягує з них символи та шукає певні функції (наприклад, sin, cos, exp).

### Перевіримо бібліотеки за допомогою команди ldd
```bash
ldd Ex1
```
### В підсумку побачимо список динамічних бібліотек від яких залежить працездатність програми.
```bash
    linux-vdso.so.1 (0x00007ffca8929000)
    libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007b6d88239000)
    libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007b6d88000000)
    /lib64/ld-linux-x86-64.so.2 (0x00007b6d88331000)

```
### Шукаємо бібліотеку  з math-функціями.
```bash
    find /usr/lib -name "*math*"
```
### В результаті отримаємо даний перелік.
```bash
    /usr/lib/x86_64-linux-gnu/libquadmath.so.0
    /usr/lib/x86_64-linux-gnu/libquadmath.so.0.0.0
    /usr/lib/gcc/x86_64-linux-gnu/13/libquadmath.so
    /usr/lib/gcc/x86_64-linux-gnu/13/include/quadmath.h
    /usr/lib/gcc/x86_64-linux-gnu/13/include/quadmath_weak.h
    /usr/lib/gcc/x86_64-linux-gnu/13/crtfastmath.o
    /usr/lib/gcc/x86_64-linux-gnu/13/libquadmath.a
```
Можемо зробити висновок,що більша частина math-функцій знаходяться в бібліотеці libm.so.

### Перевіряємо символи бібліотеки 
```bash
nm -D /usr/lib/x86_64-linux-gnu/libm.so.6 | grep erf
```
#### В результаті отримаємо
```bash   
000000000002df70 W erf@@GLIBC_2.2.5
000000000002e520 W erfc@@GLIBC_2.2.5
0000000000041200 W erfcf@@GLIBC_2.2.5
000000000005dbd0 W erfcf128@@GLIBC_2.26
0000000000041200 W erfcf32@@GLIBC_2.27
000000000002e520 W erfcf32x@@GLIBC_2.27
000000000002e520 W erfcf64@@GLIBC_2.27
000000000001bec0 W erfcf64x@@GLIBC_2.27
000000000001bec0 W erfcl@@GLIBC_2.2.5
0000000000040cf0 W erff@@GLIBC_2.2.5
000000000005fc90 W erff128@@GLIBC_2.26
0000000000040cf0 W erff32@@GLIBC_2.27
000000000002df70 W erff32x@@GLIBC_2.27
000000000002df70 W erff64@@GLIBC_2.27
000000000001ba60 W erff64x@@GLIBC_2.27
000000000001ba60 W erfl@@GLIBC_2.2.5
```
### Перевіряємо залежності бібліотек 
```bash
ldd /lib/x86_64-linux-gnu/libm.so.6
```
#### В результаті отримаємо
```bash
linux-vdso.so.1 (0x00007fffa82b7000)
libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fc337c00000)
/lib64/ld-linux-x86-64.so.2 (0x00007fc337fee000)
```
Робимо висновок,що математична бібліотека сама залежить від:
* `libc.so.6` — стандартна бібліотека С (забезпечує базові системні виклики).
* `ld-linux-x86-64.so.2` — динамічний завантажувач.

###Написання Bash-скрипта для автоматизації пошуку функцій
Для автоматизації аналізу бібліотек було створено скрипт Ex2.sh. Він дозволяє швидко знайти адреси функцій (наприклад, sin, cos, exp) у системних файлах.

Код Bash
```
#!/bin/bash

# Шлях до знайденої математичної бібліотеки
LIB_PATH="/lib/x86_64-linux-gnu/libm.so.6"

echo "--- Аналіз бібліотеки $LIB_PATH ---"

# Список функцій для пошуку
FUNCTIONS=("sin" "cos" "exp")

for FUNC in "${FUNCTIONS[@]}"; do
    echo "Пошук функції: $FUNC..."
    # nm витягує символи, grep шукає точний збіг назви функції
    nm -D "$LIB_PATH" | grep -w "$FUNC"
done

echo "--- Пошук завершено ---"
```
#### Налаштування прав доступу

У Linux після створення файлу йому потрібно надати права на виконання, інакше система видасть помилку "Permission denied". Це робиться за допомогою команди:

```
chmod +x Ex2.sh
```
Результат виконання скрипта:
Запуск здійснюється командою ./Ex2.sh. Отриманий результат:
```
Пошук функції: sin...
0000000000030ae0 i sin@@GLIBC_2.2.5
Пошук функції: cos...
0000000000030b30 i cos@@GLIBC_2.2.5
Пошук функції: exp...
0000000000013b10 T exp@GLIBC_2.2.5
000000000003a700 T exp@@GLIBC_2.29
--- Пошук завершено ---
```
Висновок:
Скрипт успішно ідентифікував точки входу для функцій у бібліотеці. Наявність прапорців i та T підтверджує, що ці символи є "текстовими" (тобто містять виконуваний код) і доступні для лінкування з іншими програмами.
# Завдання 3
### Припустимо, у вас є програма на C, що складається з кількох файлів:

-main.c\
-input.c\
-output.c\
-process1 (бібліотека у /usr/lib)\
-process (бібліотека у ~/mylibs)

### Вам потрібно:

1)Написати команду компіляції з використанням gcc.\
Створюємо програму з файлом main.c,файлом input.c який буде приймати число від користувача та файл output.c який буде виводити результат,компілюємо: 
```
gcc main.c input.c output.c -o Ex2
```
При запуску отримаємо
```
Input:
print x=2
Output: 2
```
2)Змінити команду, щоб програма використовувала process1 із /usr/lib.\
```
gcc main.c input.o output.o -L/usr/lib -lprocess1 -o my_program
```
Прапорець ***-L*** - вказує шлях до папки, де лежать бібліотеки.\
Прапорець -l - вказує назву конкретної бібліотеки, яку треба підключити.

3)Змінити команду, щоб програма використовувала process із домашнього каталогу.\
```
gcc main.c input.o output.o -L/usr/lib -lprocess1 -L$HOME/mylibs -lprocess -o my_program
```
***$HOME***-шукати бібліотеку в домашньому каталозі.

4)Додати прапорці для генерації налагоджувальної інформації (-g) і перевірки продуктивності (-O2).\
```
gcc main.c input.o output.o -L/usr/lib -lprocess1 -L$HOME/mylibs -lprocess -g -O2 -o my_program
```
5)Створити статичну (.a) і динамічну (.so) версії бібліотек process1 і process та перевірити різницю у виконанні.

Створюємо папку
```
mkdir -p ~/mylibs
```
Копіюємо process у домашню папку
```
cp libprocess.a libprocess.so ~/mylibs/
```
Копіюємо process1 у системну папку 
```
sudo cp libprocess1.a libprocess1.so /usr/lib/
```
-gcc -c input.c output.c\
-gcc main.c input.o output.o -L/usr/lib -lprocess1 -L~/mylibs -lprocess -o my_program\

-Використовуйте Makefile для автоматизації процесу компіляції.\
-Додайте до Makefile ціль clean, яка видаляє .o файли та виконуваний файл.\
```
all:
	gcc -c input.c output.c
	gcc main.c input.o output.o -L/usr/lib -lprocess1 -L$(HOME)/mylibs -lprocess -g -O2 -o my_program

clean:
	rm -f *.o my_program
```
-Напишіть CMakeLists.txt для збирання програми за допомогою CMake.
```
cmake_minimum_required(VERSION 3.10)
project(MyProcessProject C)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O2")
link_directories(/usr/lib $ENV{HOME}/mylibs)
add_executable(my_program main.c input.c output.c)
target_link_libraries(my_program process1 process)
```
# Завдання 4
У вас є програма на C, яка складається з кількох модулів (main.c, module1.c, module2.c) та використовує бібліотеку pthread.
#### 1)Напишіть команду компіляції з підтримкою багатопоточності (-pthread).
main.c:
```
#include <stdio.h>
#include <pthread.h>

void print1();
void print2();

void* thread_function(void* arg) {
    printf("Потік: Виконання завдання успішно розпочато.\n");
    return NULL;
}

int main() {
    pthread_t thread;

    print1();
    print2();

    pthread_create(&thread, NULL, thread_function, NULL);

    pthread_join(thread, NULL);

    printf("Головна програма: Усі операції завершено.\n");

    return 0;
}
```
Для компіляції використовується команда 
```
gcc main.c module1.c module2.c -pthread -o my_program
```
 де прапорець -pthread дозволяє програмі працювати з потоками; у самому коді ми використовуємо pthread_create, щоб запустити функцію паралельно з основною програмою, та pthread_join, щоб головна частина почекала завершення цієї роботи перед виходом.

#### 2)Змініть код так, щоб він використовував OpenMP (#pragma omp parallel).
main.c:
```
#include <stdio.h>
#include <omp.h>

void print1();
void print2();

int main() {
    print1();
    print2();

    #pragma omp parallel
    {
        printf("Потік OpenMP: виконання паралельної секції.\n");
    }

    printf("Головна програма: Усі операції завершено.\n");

    return 0;
}
```
Компіляція
```
gcc main.c module1.c module2.c -fopenmp -o my_omp_program
```
прапорець -fopenmp вмикає підтримку багатопоточності; у коді ми використовуємо директиву #pragma omp parallel, яка автоматично розпаралелює блок коду.

#### 3)Використовуйте valgrind або gprof для аналізу продуктивності.
Комілюємо програму
``` 
-gcc -Wall -Wextra -pthread main.c module1.c module2.c -o threaded_program\
```
Після запуску програми qpof створює файл який ми перенаправляємо в формат .txt
```
gprof threaded_program gmon.out > analysis.txt
```
В цьому текствому файлі отримуємо аналіз продуквтивності
```
Flat profile:

Each sample counts as 0.01 seconds.
 no time accumulated

  %   cumulative   self              self     total
 time   seconds   seconds    calls  Ts/call  Ts/call  name
  0.00      0.00     0.00        1     0.00     0.00  print1
  0.00      0.00     0.00        1     0.00     0.00  print2

 %         the percentage of the total running time of the
time       program used by this function.

cumulative a running sum of the number of seconds accounted
...
```
#### -Оптимізуйте код для роботи з багатоядерними процесорами.
```
#include <stdio.h>
#include <omp.h>

void print1();
void print2();

int main() {
    #pragma omp parallel sections
    {
        #pragma omp section
        print1();

        #pragma omp section
        print2();

        #pragma omp section
        printf("Потік OpenMP: виконання паралельної секції.\n");
    }

    printf("Головна програма: Усі операції завершено.\n");
    return 0;
}
```
Для оптимізації програми під багатоядерні процесори використано OpenMP. За допомогою директиви #pragma omp parallel sections функції print1(), print2() та додатковий блок виконуються одночасно у різних потоках.

#### -Використовуйте асинхронний ввід/вивід (aio.h) замість стандартного stdio.h.
```
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
```
У цій програмі використовується асинхронний ввід/вивід (aio.h) для запису повідомлення у файл output.txt. Асинхронність дозволяє операції запису виконуватись паралельно з основним потоком,одночасно продовжує виконання інших дій — простого лічильника в циклі.aio_write() запускає запис у файл, а основний потік продовжує роботу.
#### -Реалізуйте версію програми на C++ з використанням std::thread.
main.cpp
```
#include <iostream>
#include <thread>

void print1();
void print2();

void thread_function() {
    std::cout << "Потік: Виконання завдання успішно розпочато." << std::endl;
}

int main() {
    std::thread t(thread_function);

    print1();
    print2();

    t.join();

    std::cout << "Головна програма: Усі операції завершено." << std::endl;

    return 0;
}
```
# Завдання 5
### Уявіть, що ваша програма на C складається з кількох окремих файлів, і вони використовують заголовкові файли, як показано нижче:
main.c - stdio.h, process1.h  
input.c - stdio.h, list.h  
output.c - stdio.h  
process1.c - stdio.h, process1.h  
process2.c - stdio.h, list.h

#### Які файли потрібно перекомпілювати після внесення змін до process1.c?
Тільки сам файл process1.c
#### Які файли потрібно перекомпілювати після внесення змін до process1.h?
Треба перекомпілювати файли main.c,process1.c,бо вони мають в своєму складі файл process.h
#### Які файли потрібно перекомпілювати після внесення змін до list.h?
Файли input.c,process2.c\
### Додайте ще один файл (utility.c) із залежністю від process1.h та stdio.h.
utility.c:
```
#include <stdio.h>
#include "process1.h"

void utility_function() {
    printf("Utility function\n"); 
}
```
# Завдання 6
Напишіть програму на ANSI C, яка приймає ціле число (кількість секунд) як вхідні дані та виводить еквівалентний час у годинах, хвилинах і секундах.
Рекомендований формат виводу:
7322 секунд еквівалентно 2 годинам 2 хвилинам 2 секундам.
Створюю програму для розрахунку,щоб вона була за стандартом ANSI ,компілюємо
```
gcc -std=c89 main.c -o Ex6
```
Запускаємо
```
./Ex6
Enter number of seconds: 85444
85444 seconds its 0 days 23 hours 44 minutes 4 seconds.
```
#### Додайте підтримку від'ємних чисел, які мають інтерпретуватись як час у минулому.
```
./Ex6
Enter number of seconds: -7322
7322 seconds its 0 days 2 hours 2 minutes 2 seconds ago(in the past).
```
# Завдання 7
Напишіть програму на ANSI C, яка читає з stdin довільне ціле число — основу системи числення, потім ціле число у цій системі числення, а далі виводить його значення у десятковій системі. Ігноруйте всі недопустимі символи.
Приклад:
Вхід:   8 77   
Вихід:  63 (значення 77 у системі числення з основою 8)

#### main.c
```

#include <stdio.h>

int main() {
    int base;
    int ch;
    int result = 0;
    int value;

    printf("Введіть основу: ");
    if(scanf("%d", &base) != 1) return 0;

    while((ch = getchar()) != EOF && ch != '\n') {
        value = -1;

        if(ch >= '0' && ch <= '9') {
             value = ch-'0';
        }

        if(value >= 0 && value < base){
            result = result * base + value;
        }
    }

    printf("Результат: %d\n", result);
    return 0;
}
```
Запускаємо програму
```
./Ex7
Введіть основу: 8 77
Результат: 63
```
Додайте обробку значень із плаваючою точкою для десяткової системи числення.
```
#include <stdio.h>

int main() {
    int base;
    int ch;
    double result = 0;
    int value;
    int is_fraction=0;
    double weight=1;

    printf("Введіть основу: ");
    if(scanf("%d", &base) != 1) return 0;

    while((ch = getchar()) != EOF && ch != '\n') {
        value = -1;
        if (ch == '.') {
            is_fraction = 1;
            continue;
        }
        if(ch >= '0' && ch <= '9') {
             value = ch-'0';
        }
        else if (ch >= 'A' && ch <= 'Z') {
            value = ch - 'A' + 10;
        } else if (ch >= 'a' && ch <= 'z') {
            value = ch - 'a' + 10;
        }

        if(value >= 0 && value < base){
            if(!is_fraction){
                 result = result * base + value;
            }
            else{
                weight=weight/base;
                result = result + (value * weight);
           }
        }
    }

    printf("Результат: %f\n", result);
    return 0;
}
```
# Завдання 8
Напишіть програму на ANSI C для заповнення масиву випадковими числами з плаваючою точкою.
```
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
        double arr[10];
        int i;

        srand((int)time(NULL));
        for(i=0;i<10;i++){
                arr[i]=(1000000/(double)rand())*10000;
        }
        printf("Массив випадкових чисел:\n");
        for (i = 0; i < 10; i++) {
                 printf("arr[%d] = %f\n", i, arr[i]);
        }
        return 0;
}
```
Запуск
```
./Ex8
Массив випадкових чисел:
arr[0] = 22.614171
arr[1] = 6.628113
arr[2] = 5.040344
arr[3] = 124.850312
arr[4] = 121.723416
arr[5] = 5.566004
arr[6] = 9.781486
arr[7] = 5.429830
arr[8] = 9.018575
arr[9] = 11.231399
```
#### Реалізуйте функцію для пошуку всіх індексів заданого числа у масиві.
Додаємо пошук індекса массива за числом,яке вводить користувач,перевіряємо:
```
./Ex8
Массив випадкових чисел:
arr[0] = 4.833451
arr[1] = 11.612611
arr[2] = 14.154810
arr[3] = 6.580894
arr[4] = 18.298936
arr[5] = 12.238038
arr[6] = 14.150457
arr[7] = 5.234943
arr[8] = 15.589725
arr[9] = 7.049837

Яке число шукаємо? 7.05
Знайдено! Індекс: 9 (Значення в масиві: 7.049837)
```
#### Реалізуйте можливість використовувати багатовимірні масиви.
Додаю можливість користувачу обирати розмір массиву
```
./Ex8
Print size of matrix ROWS:2
COLS:3

Массив випадкових чисел:
matrix[0][0] = 17.602470
matrix[0][1] = 511.607871
matrix[0][2] = 21.516408

matrix[1][0] = 7.441286
matrix[1][1] = 9.277978
matrix[1][2] = 18.087853


Яке число шукаємо? 7.4
Знайдено! Індекс: [1] [0] (Значення в масиві: 7.441286)
```
# Завдання 9
Напишіть функцію replace, яка отримує вказівник на рядок, замінює всі пробіли знаком мінус, і повертає кількість замінених пробілів.
Приклад:
Вхід: "The cat sat"
Вихід: "The-cat-sat", Кількість замін: 2
main.c
```

#include <stdio.h>
int replace(char *str){
        int count=0;
        while(*str!='\0'){
                if(*str==' '){
                        *str='-';
                        count++;
                }
                str++;
        }
        return count;
}
int main(){
        char text[100];
        int replaced_count;
        printf("Введіть рядок з пробілами:\n");
        fgets(text,sizeof(text),stdin);
        replaced_count=replace(text);
        printf("%s\n",text);
        printf("Кількість пробілів:%d\n",replaced_count);
        return 0;
}
```
Робота програми
```
./Ex9
Введіть рядок з пробілами:
The cat sat sat
The-cat-sat-sat

Кількість пробілів:3
```
#### Додайте параметр для вказівки символу, на який потрібно виконати заміну.
Додаємо в функцію replace параметр,який буде отримувати від користувача символ
```

#include <stdio.h>
int replace(char *str,char new_sym){
        int count=0;
        while(*str!='\0'){
                if(*str==' '){
                        *str=new_sym;
                        count++;
                }
                str++;
        }
        return count;
}
int main(){
        char text[100];
        char user_sym;
        int replaced_count;
        printf("Введіть рядок з пробілами:\n");
        fgets(text,sizeof(text),stdin);
        printf("Введіть символ, на який замінити пробіли: ");
        scanf("%c", &user_sym);
        replaced_count=replace(text,user_sym);
        printf("%s\n",text);
        printf("Кількість змінених символів:%d\n",replaced_count);
        return 0;
}
```
Робота
```
./Ex9
Введіть рядок з пробілами:
The cat sat
Введіть символ, на який замінити пробіли: *
The*cat*sat

Кількість змінених символів:2
```
# Завдання 10
Напишіть програму з використанням перелічуваних типів для обчислення та виводу завтрашньої дати відносно заданої. 
```

#include <stdio.h>
enum Month{
                JAN=1,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC
};
struct Date{
        int day;
        enum Month month;
        int year;
};
int days_in_month(enum Month m, int year) {
    switch (m) {
        case APR: case JUN: case SEP: case NOV:
            return 30;
        case FEB:
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
                return 29;
            else
                return 28;
        default:
            return 31;
    }
}
int main(){
        struct Date today,tomorrow;
        printf("Введіть поточну дату (приклад 31 12 2025): ");
        scanf("%d %u %d",&today.day,(unsigned int*)&today.month,&today.year);
        if (today.month < JAN || today.month > DEC || today.day < 1 || today.day > days_in_month(today.month, today.year)) {
                printf("Такої дати не існує!\n");
                return 1;
        }
        tomorrow=today;
        tomorrow.day++;
        if(tomorrow.day>days_in_month(today.month,today.year)){
                tomorrow.day=1;
                tomorrow.month++;
                if (tomorrow.month > DEC) {
                        tomorrow.month = JAN;
                        tomorrow.year++;
                }
        }
        printf("Завтра буде: %02d.%02d.%d\n", tomorrow.day,(unsigned int)tomorrow.month, tomorrow.year);
        return 0;
}
```
Запуск
```
./Ex10
Введіть поточну дату (приклад 31 12 2025): 22 02 2026
Завтра буде: 23.02.2026
```
#### Додайте обробку дати в різних календарях, наприклад, григоріанському та юліанському.
```
./Ex10
Оберіть календар (1 - Григоріанський, 2 - Юліанський): 1
Введіть поточну дату (приклад 31 12 2025): 28 02 1900

За обраним календарем (Григоріанський):
Завтра буде: 01.03.1900
```
# Завдання 11
Створіть просту програму на ANSI C, яка реалізує базу даних для зберігання даних про студентів (ім'я, дата народження, адреса). Забезпечте можливість додавання, редагування та видалення записів. Реалізуйте функцію пошуку за частковим збігом.
```
1. Додати
2. Показати
3. Видалити
4. Пошук
5  Вихід
Вибір: 1
Ім'я: Никита
Дата народження (д м р): 05 03 2007
Адреса: Капап 12
Студента додано з ID: 1

1. Додати
2. Показати
3. Видалити
4. Пошук
5  Вихід
Вибір: Невірний вибір.

1. Додати
2. Показати
3. Видалити
4. Пошук
5  Вихід
Вибір: 4
Введіть частину імені: Ники

--- Результати пошуку ---
ID: 1 | Ім'я: Никита | Адреса: Капап

1. Додати
2. Показати
3. Видалити
4. Пошук
5  Вихід
Вибір: 3
Введіть ID для видалення: 1
Запис видалено.
```
# Завдання 12
Напишіть програму на ANSI C, яка працює з масивами довільного типу.
#### Заповніть масив випадковими значеннями, використовуючи покажчики.
Створюэмо массив з 10 комірками,потім вказівник `ptr` на цей массив,для генерації випадкових чисел беремо бібліотеку `stdlib.h`,використовуэмо з неї функції `rand()` `srand()`,заповнюємо массив за допомогою вказівника на нього,використовуючи цикл `for`.В результаті отримуємо:
```
./Ex12
Array:
Pointer 0x7ffe18c58790=31
Pointer 0x7ffe18c58794=79
Pointer 0x7ffe18c58798=60
Pointer 0x7ffe18c5879c=7
Pointer 0x7ffe18c587a0=27
Pointer 0x7ffe18c587a4=32
Pointer 0x7ffe18c587a8=10
Pointer 0x7ffe18c587ac=8
Pointer 0x7ffe18c587b0=79
Pointer 0x7ffe18c587b4=86
```
#### Напишіть функцію пошуку заданого значення в цьому масиві за допомогою рекурсії.
Створюю функцію `recursive`,яка приймає вказівник на массив,його розмір та значення ,яке шукаєтиься,після чого функція рекурсивно перевіряє кожне значення масиву на відповідність заданомуц значенню та повертає 1 якщо значення знайдено і -1 якщо ні.
```
./Ex12
Array:
Pointer 0x7ffc139c7d50=30
Pointer 0x7ffc139c7d54=30
Pointer 0x7ffc139c7d58=44
Pointer 0x7ffc139c7d5c=38
Pointer 0x7ffc139c7d60=22
Pointer 0x7ffc139c7d64=46
Pointer 0x7ffc139c7d68=17
Pointer 0x7ffc139c7d6c=40
Pointer 0x7ffc139c7d70=8
Pointer 0x7ffc139c7d74=34
Enter value for search: 9
Value isn`t found.
```
#### Реалізуйте додаткову функцію для бінарного пошуку, якщо масив відсортований.
Спочатку додав функцуію для сортування,яка перевіряє два сусіднгіх елемента,і якщо число зправа менше за те що зліва,то функція міняє їх місцями.Після цього створено функцію для бінарного пошуку,яка отримує параметри масиву визначає його середину та її вказівник і перевіряє середній елемент,якщо елемент відповідає заданому значнню то функція повертає успішний результ,якщо він більше то вона викликає себе і перевіряє всі елементи перед цим,якщо ж елемент менше за значення то навпаки,функція буде перевіряти всі елементи праворуч від нього.
```
./Ex12
Pointer 0x7ffcd66c20d0=57
Pointer 0x7ffcd66c20d4=15
Enter value for search: 57
Value 57 is found!
Enter value for binary search: 57
Value 57 is found!
```
#### Додайте можливість вибору типу даних (int, float, char) через параметри командного рядка.
Додаємо оператор if який буде перевыряти параметр отриманий з командного рядка,і в залежності від типу даних буде викликано відповідні функції та створено відповідні масиви.На виході отримаємо:
```
./Ex12 char
Обрано роботу з символами (char).
Array(char):
Pointer 0x7ffe9970546e=F
Pointer 0x7ffe9970546f=W
Pointer 0x7ffe99705470=E
Pointer 0x7ffe99705471=S
Pointer 0x7ffe99705472=W
Pointer 0x7ffe99705473=F
Pointer 0x7ffe99705474=J
Pointer 0x7ffe99705475=A
Pointer 0x7ffe99705476=C
Pointer 0x7ffe99705477=Q
Enter char for search: A
Char A is found!
Enter char for binary search: C
Char C is found!
```
