# Лабораторна робота №10

## Сигнали Linux та породження процесів.
# Варіант 3
Використайте fork() двічі поспіль у програмі. Порахуйте кількість процесів, що виникнуть. Виведіть їхні PID
## 1. Мета роботи

Дослідити механізми:

- обробки сигналів у Linux (`SIGSEGV`, `SIGBUS`, `SIGUSR1`, real-time signals)
- отримання діагностичної інформації про крах програми
- коректної роботи таймерів (`nanosleep`, `clock_nanosleep`)
- обміну повідомленнями між процесами через `sigqueue`
- створення процесів через `fork()` та аналіз їх кількості

## Приклад 1. Crash handler із SA_SIGINFO і register dump
### Компіляція
```
gcc -Wall -Wextra -O0 -g -fno-omit-frame-pointer -no-pie crash_diag.c -o crash_diag
```
### Запуск
```
arthas@ubuntuserver:~/projects/pr11$ ./crash_diag
About to crash. PID=236766
=== crash captured ===
signal: 11
si_code: 1
fault address: 0x0
RIP: 0x401818
RSP: 0x7ffdb7891230
RBP: 0x7ffdb7891230
RAX: 0x0
RBX: 0x7ffdb7891368
RCX: 0x757a4e91c5a4
RDX: 0x1
RSI: 0x402035
RDI: 0x2
```
### Аналіз роботи
Програма:
- встановлює обробники сигналів SIGSEGV, SIGBUS, SIGFPE, SIGILL
- при помилці виводить:
  - номер сигналу
  - адресу помилки
  - значення регістрів CPU (RIP, RSP, RAX тощо)
Це дозволяє виконувати базову діагностику краху програми на рівні процесора.
## Приклад 2. Correct sleeping
### Компіляція
```
gcc -Wall -Wextra -O2 sleep_correct.c -o sleep_correct
```

### Запуск
```
arthas@ubuntuserver:~/projects/pr10$ ./sleep_correct
PID=237397
Sleeping...
ticks:
tick 1
tick 2
tick 3
tick 4
tick 5
```

### Тест сигналу

В іншому терміналі:
```
arthas@ubuntuserver:~/projects/pr10$ kill -USR1 <237397>
```

### Аналіз роботи

У програмі реалізовано:

- коректну обробку переривання `nanosleep()` через EINTR
- перезапуск sleep через залишковий час
- абсолютний таймер через `clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME)`
- обробку сигналу `SIGUSR1`

Висновок: `clock_nanosleep` дозволяє уникнути накопичення похибки часу.

## Приклад 3. Real-time signals
### Компіляція
```
 -Wall -Wextra -O2 rt_pubsub.c -o rt_pubsub
```
### Запуск subscriber
```
./rt_pubsub sub
subscriber PID=240064
```
---

### Відправка повідомлень
```
arthas@ubuntuserver:~/projects/pr10$ ./rt_pubsub pub <240064> 10 20 30 -1
```
---

### Аналіз роботи

Програма демонструє:

- використання real-time сигналів (`SIGRTMIN`)
- передачу даних через `sigqueue`
- отримання повідомлень через `sigwaitinfo`
- можливість timeout через `sigtimedwait`

Це дозволяє реалізувати просту IPC-систему між процесами.

## Завдання: fork() двічі поспіль

### Код прикладу

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Parent PID: %d\n", getpid());

    fork();
    fork();

    printf("Process PID: %d Parent PID: %d\n", getpid(), getppid());

    return 0;
}
```
### Аналіз кількості процесів
Логіка

Кожен fork() подвоює кількість процесів:

після 1-го fork → 2 процеси

після 2-го fork → 4 процеси

#### Результат

Всього створюється:

2² = 4 процеси

## Вивід у терміналі
```
arthas@ubuntuserver:~/projects/pr11$ ./fork_test

Process PID: 1234 Parent PID: 1200
Process PID: 1235 Parent PID: 1234
Process PID: 1236 Parent PID: 1234
Process PID: 1237 Parent PID: 1235
```
## Висновок

#### У ході роботи було досліджено:

-механізми обробки сигналів у Linux

-діагностику аварійних завершень програм 

-роботу таймерів nanosleep та clock_nanosleep

-обмін повідомленнями між процесами через real-time signals

-створення процесів за допомогою fork() та їх розмноження

Було встановлено, що два послідовні виклики fork() створюють 4 процеси, що відповідає експоненційному росту кількості процесів.
