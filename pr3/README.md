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
## Завдання 4
Напишіть програму, що імітує лотерею, вибираючи 7 різних цілих чисел у діапазоні від 1 до 49 і ще 6 з 36. Встановіть обмеження на час ЦП (max CPU time) і генеруйте результати вибору чисел (7 із 49, 6 із 36). Обробіть ситуацію, коли ліміт ресурсу вичерпано.
```
gcc Ex4.c -o Ex4
```
Встановлюємо обмеження 
```
ulimit -St 1
ulimit -Ht 2
```
Результат:
```
Starting lottery simulation. CPU limit: 1 sec.
Lottery 7 of 49: 12 45 3 22 19 31 7 
Lottery 6 of 36: 5 28 14 2 33 11 
Lottery 7 of 49: 40 1 25 8 16 49 33 
Lottery 6 of 36: 12 9 36 21 4 18 
Lottery 7 of 49: 5 13 22 44 2 17 38 
Lottery 6 of 36: 30 1 15 22 7 19 
Lottery 7 of 49: 21 4 48 33 10 15 2 
Lottery 6 of 36: 11 25 3 8 32 14 

[ SIGXCPU received: CPU time limit exceeded!
```
## Завдання 5
Напишіть програму для копіювання одного іменованого файлу в інший. Імена файлів передаються у вигляді аргументів.
#### Компіляція програми
```
gcc Ex5.c -o Ex5_copy
```
Перевірка:
```
echo "Hello, Docker!" > test.txt
./Ex5 test.txt test_copy.txt
```
Результат:
```
root@334e9e1bb64e:/work# gcc copy.c -o Ex5
root@334e9e1bb64e:/work# echo "Hello world" > test.txt
root@334e9e1bb64e:/work# ./Ex5 test.txt test_copy.txt
File copied successfully
root@334e9e1bb64e:/work# cat test_copy.txt
Hello world
```
обробляти ситуацію перевищення обмеження на розмір файлу^
```
dd if=/dev/urandom of=big_file.txt bs=1k count=20
./Ex5 big_file.txt output.txt
```
Результат:
```
[!] SIGXFSZ received: File size limit reached during copying!
```
## Завдання 6
Напишіть програму, що демонструє використання обмеження (max stack segment size). Підказка: рекурсивна програма активно використовує стек.
#### Компіляція
```
gcc Ex6.c -o Ex6
```
Результат:
```
root@334e9e1bb64e:work# ./Ex6
Starting recursive function. Stack limit: 65536 bytes.
Current depth: 1

[!] SIGSEGV received: Stack overflow or memory limit reached!
```
## Завдання по варіантам(3-варіант):
Написати програму, яка використовує багато пам'яті та перевірити обмеження (ulimit -v).
#### Компіляція
```
gcc Ex7.c -o Ex7
```
Встановлюємо обмеження
```
ulimit -v 50000
```
Результат
```
root@334e9e1bb64e:/work# ./Ex7
Starting memory allocation loop...
Check ulimit -v to see the current shell limit.
Allocated: 10 MB
Allocated: 20 MB
Allocated: 30 MB

[!] MALLOC FAILED!
Total allocated before failure: 30 MB
```
## Висновок:
У ході виконання практичної роботи я поглибив знання про системні ресурси ОС Linux та механізми керування ними за допомогою мови програмування C.\
##### Було вивчено
Керування ресурсами: На практиці застосовано функцію setrlimit та утиліту ulimit для встановлення обмежень на розмір файлу, час процесора, об'єм віртуальної пам'яті та розмір стеку.

Обробка сигналів: Реалізовано механізми перехоплення сигналів, що надсилаються ядром при порушенні лімітів.

Робота з пам'яттю: Шляхом створення рекурсивних функцій та циклічного виділення пам'яті через malloc продемонстровано виникнення помилок сегментації та відмову у виділенні ресурсів при досягненні встановлених меж.
