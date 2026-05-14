# Лабораторна робота №3

### Дослідження обмежень ресурсів у середовищі Docker
## Завдання 1
### Запустіть Docker-контейнер і поекспериментуйте з максимальним лімітом ресурсів відкритих файлів.
Спочатку перевріємо чи встановлено Docker
```
docker --version
```
Якщо не має то встановлюємо
```
sudo apt install docker.io
```
Запускаємо контейнер
```
sudo docker run --rm -it ubuntu bash
```
#### Запуск команд
```
ulimit -n
```
В результаті отримаємо число 1024,воно відображає максимальну можливу к-сть відкритих файлів одночасно.
```
ulimit -aS | grep "open files"
ulimit -aH | grep "open files"
```
Перша команда відображає поточний ліміт,а друга максимально дозволений:
```
root@59b0f4a60cfa:/# ulimit -aS | grep "open files"
open files                          (-n) 1024
root@59b0f4a60cfa:/# ulimit -aH | grep "open files"
open files                          (-n) 524288
```
Команда для встановлення ліміту 3000 файлів:
```
ulimit -n 3000
```
Перевіряємо:
```
root@59b0f4a60cfa:/# ulimit -n
3000
```
Тепер і поточний і максимально довзволений ліміт однакові:
```
root@59b0f4a60cfa:/# ulimit -aS | grep "open files"
open files                          (-n) 3000
root@59b0f4a60cfa:/# ulimit -aH | grep "open files"
open files                          (-n) 3000
```
Якщо ми не маємо прав Root тоді при зменшені ліміту все буде добре,але збільшити його назад ми вже ніяк не зможемо:
```
ulimit -n 3000
bash: ulimit: open files: cannot modify limit: Operation not permitted
```
## Завдання 2
### У Docker-контейнері встановіть утиліту perf(1). Поекспериментуйте з досягненням процесом встановленого ліміту.
Встановлюємо утиліту perf
```
apt update
apt install -y linux-tools-6.8.0-110-generic linux-cloud-tools-6.8.0-110-generic
```
Встановлюємо ліміт
```
ulimit -n 15
```
Створюємо та компілюємо програму,яка в циклі відкриває файли до моменту вичерпання доступних дескрипторів. Це дозволяє зафіксувати точну межу, встановлену операційною системою.
```
gcc Ex2.c -o Ex2
```
Імітуємо роботу perf за допомогою time
```
time ./Ex2
```
В результаті отримаємо
```
Start opening files
Open failed: Too many open files
Limit reached. Total opened files in loop: 47

real    0m0.008s
user    0m0.001s
sys     0m0.006s
```
Пояснення:
У ході експерименту було підтверджено механізм обмеження ресурсів процесу. Хоча ліміт був встановлений на значення 50, програма змогла відкрити лише 47 файлів.
Різниця пояснюється тим, що кожен новий процес у Linux автоматично отримує три відкриті дескриптори:\
0 (stdin)\
1 (stdout)\
2 (stderr)
## Завдання 3
Напишіть програму, що імітує кидання шестигранного кубика. Імітуйте кидки, результати записуйте у файл, для якого попередньо встановлено обмеження на його максимальний розмір (max file size). Коректно обробіть ситуацію перевищення ліміту.
Створюємо та компілюємо програму
```
gcc dice.c -o Ex3
```
Запускаємо програму,вона буде імітувати підкидання кубика поки не досягне ліміту
```
Starting simulation. File limit: 1024 bytes.
Roll 1 recorded.
Roll 2 recorded.
Roll 3 recorded.
Roll 4 recorded.
Roll 5 recorded.
Roll 6 recorded.
Roll 7 recorded.
Roll 8 recorded.
Roll 9 recorded.
Roll 10 recorded.
Roll 11 recorded.
Roll 12 recorded.
Roll 13 recorded.
Roll 14 recorded.
Roll 15 recorded.
Roll 16 recorded.
Roll 17 recorded.
Roll 18 recorded.
Roll 19 recorded.
Roll 20 recorded.
Roll 21 recorded.
Roll 22 recorded.
Roll 23 recorded.
Roll 24 recorded.
Roll 25 recorded.
Roll 26 recorded.
Roll 27 recorded.
Roll 28 recorded.
Roll 29 recorded.
Roll 30 recorded.
Roll 31 recorded.
Roll 32 recorded.
Roll 33 recorded.
Roll 34 recorded.
Roll 35 recorded.
Roll 36 recorded.
Roll 37 recorded.
Roll 38 recorded.
Roll 39 recorded.
Roll 40 recorded.
Roll 41 recorded.
Roll 42 recorded.
Roll 43 recorded.
Roll 44 recorded.
Roll 45 recorded.
Roll 46 recorded.
Roll 47 recorded.
Roll 48 recorded.
Roll 49 recorded.
Roll 50 recorded.
Roll 51 recorded.

[!] SIGXFSZ received: Max file size reached!
```
Перевірка створеного файлу
```
cat dice_results.txt
Roll 1: result = 3
Roll 2: result = 3
Roll 3: result = 2
Roll 4: result = 4
Roll 5: result = 6
Roll 6: result = 4
Roll 7: result = 1
Roll 8: result = 2
Roll 9: result = 5
Roll 10: result = 1
...
```
Перевіряємо розмір файлу
```
ls -l dice_results.txt
-rw-r--r-- 1 root root 1024 May  6 13:35 dice_results.txt
```
Спрацювало обмеження в 1024 байти
