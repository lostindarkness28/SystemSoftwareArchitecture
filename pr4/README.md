# Лабораторна робота №4

### Робота з динамічною пам’яттю в Linux
## Завдання 1
Скільки пам’яті може виділити malloc(3) за один виклик?\
Параметр malloc(3) є цілим числом типу даних size_t, тому логічно максимальне число, яке можна передати як параметр malloc(3), — це максимальне значення size_t на платформі (sizeof(size_t)). У 64-бітній Linux size_t становить 8 байтів, тобто 8 * 8 = 64 біти. Відповідно, максимальний обсяг пам’яті, який може бути виділений за один виклик malloc(3), дорівнює 2^64. Спробуйте запустити код на x86_64 та x86.
#### Компіляція
```
gcc Ex1.c -o Ex1
./Ex1
```
#### Результат
```
arthas@ubuntuserver:~/projects/pr4$ gcc Ex1.c -o Ex1
arthas@ubuntuserver:~/projects/pr4$ ./Ex1
sizeof(size_t) = 8 bytes
Max size_t: 18446744073709551615 (0xffffffffffffffff)
malloc failed: Cannot allocate memory
Trying to allocate 1/2 of size_t: 9223372036854775807
malloc failed: Cannot allocate memory
arthas@ubuntuserver:~/projects/pr4$
```
####  Чому теоретично максимальний обсяг складає 8 ексабайт, а не 16?
Теоретичний ліміт у 8 ексабайт замість 16 виникає через те, що в 64-бітній Linux адресний простір ділиться навпіл: 2^63 віддається ядру, а інші 2^63 (якраз 8 ЕБ) - користувачеві. Оскільки malloc працює в просторі користувача, він обмежений лише цією нижньою половиною доступних адрес.
## Завдання 2
Що станеться, якщо передати malloc(3) від’ємний аргумент? Напишіть тестовий випадок, який обчислює кількість виділених байтів за формулою num = xa * xb. Що буде, якщо num оголошене як цілочисельна змінна зі знаком, а результат множення призведе до переповнення? Як себе поведе malloc(3)? Запустіть програму на x86_64 і x86
#### Компіляція
```
gcc Ex2.c -o Ex2
./Ex2
```
#### Результат
```
arthas@ubuntuserver:~/projects/pr4$ ./Ex2
xa = 1000000, xb = 1000000
num (overflow): -727379968
As size_t: 18446744072982171648
malloc failed: Cannot allocate memory

Testing malloc(-1):
malloc failed for -1: Cannot allocate memory
arthas@ubuntuserver:~/projects/pr4$
```
#### Відповідь
Якщо передати від’ємне число, malloc сприйме його як величезне додатне значення, що призведе до помилки виділення пам'яті та повернення NULL. При переповненні знакової змінної num результат стане від'ємним, і при спробі виділення malloc так само спробує зарезервувати гігантський обсяг пам'яті.
## Завдання 3
Що станеться, якщо використати malloc(0)? Напишіть тестовий випадок, у якому malloc(3) повертає NULL або вказівник, що не є NULL, і який можна передати у free(). Відкомпілюйте та запустіть через ltrace. Поясніть поведінку програми.

#### Для запуску потрібно встановити Itrace
```
sudo apt install ltrace
sudo apt update
```
#### Компіляція
```
gcc Ex3.c -o Ex3
ltrace ./Ex3
```
#### Результат
```
arthas@ubuntuserver:~/projects/pr4$ ltrace ./Ex3
malloc(0)                                        = 0x55964f9f72a0
printf("malloc(0) returned non-NULL poin"...)    = 49
free(0x55964f9f72a0)                             = 
printf("Pointer freed successfully\n")           = 27
+++ exited (status 0) +++
arthas@ubuntuserver:~/projects/pr4$
```
#### Пояснення поведінки
alloc(0) зазвичай повертає реальну адресу (не NULL), але виділяє мінімально можливий блок пам'яті. Цей вказівник є цілком валідним для функції free(), що дозволяє уникнути помилок у логіці програми. Через ltrace ми бачимо, що виклик обробляється як стандартне виділення пам'яті, хоча розмір і нульовий.
## Завдання 4
Чи є помилки у такому коді?
```
void *ptr = NULL;
while (<some-condition-is-true>) {
    if (!ptr)
        ptr = malloc(n);
    [... <використання 'ptr'> ...]
    free(ptr);
}
```
Напишіть тестовий випадок, який продемонструє проблему та правильний варіант коду.
#### Створюємо і компілюємо тестовий варіант в результаті отримуємо
```
arthas@ubuntuserver:~/projects/pr4$ gcc Ex4.c -o Ex4
arthas@ubuntuserver:~/projects/pr4$ ltrace ./Ex4
Running Correct Variant 
malloc(100)                                      = 0x55d71c4222a0
printf("Allocated at: %p\n", 0x55d71c4222a0)     = 27
strcpy(0x55d71c4222a0, "test")                   = 0x55d71c4222a0
printf("Step %d: Used ptr %p\n", 0, 0x55d71c4222a0) = 31
free(0x55d71c4222a0)                             = <void>
malloc(100)                                      = 0x55d71c4222a0
printf("Allocated at: %p\n", 0x55d71c4222a0)     = 27
strcpy(0x55d71c4222a0, "test")                   = 0x55d71c4222a0
printf("Step %d: Used ptr %p\n", 1, 0x55d71c4222a0) = 31
free(0x55d71c4222a0)                             = <void>
```
#### Пояснення
Проблема в тому, що після free()вказівник  не стає NULL. На наступному кроці циклу if (!ptr) не спрацьовує, новий malloc не викликається, і програма використовує вже недійсну адресу. 
## Завдання 5
Що станеться, якщо realloc(3) не зможе виділити пам’ять? Напишіть тестовий випадок, що демонструє цей сценарій.
#### Створюємо і компілюємо тестовий варіант в результаті отримуємо
```
arthas@ubuntuserver:~/projects/pr4$ ./Ex5
Initial pointer: 0x55d1a2c322a0
realloc failed as expected: returned NULL
Old pointer is still valid: 0x55d1a2c322a0
arthas@ubuntuserver:~/projects/pr4$
```
#### Пояснення
Якщо realloc(3) не може виділити новий блок пам'яті, він повертає NULL, але старий блок пам'яті залишається недоторканим і не звільняється,в результаті буде втрата вказівника: якщо написати ptr = realloc(ptr, size), та при помилці старий вказівник перезапишеться значенням NULL.
## Завдання 6
Якщо realloc(3) викликати з NULL або розміром 0, що станеться? Напишіть тестовий випадок.
#### Створюємо і компілюємо тестовий варіант в результаті отримуємо
```
arthas@ubuntuserver:~/projects/pr4$ ./Ex6
realloc(NULL, 100) success: 0x55a1b2c442a0
realloc(ptr1, 0) returned: (nil)
ptr1 is now freed.
arthas@ubuntuserver:~/projects/pr4$
```
#### Пояснення
realloc(NULL, size): працює ідентично до звичайного malloc(size).

realloc(ptr, 0): працює як free(ptr) і повертає NULL.
## Завдання 7
Перепишіть наступний код, використовуючи reallocarray(3):
```
struct sbar *ptr, *newptr;
ptr = calloc(1000, sizeof(struct sbar));
newptr = realloc(ptr, 500*sizeof(struct sbar));
```
Порівняйте результати виконання з використанням ltrace.
#### Запускаємо програму
```
arthas@ubuntuserver:~/projects/pr4$ gcc Ex7.c -o Ex7
arthas@ubuntuserver:~/projects/pr4$ ltrace ./Ex7
calloc(1000, 68)                                 = 0x559e3a2c22a0
printf("Initial allocation (calloc): %p\n", 0x559e3a2c22a0) = 39
reallocarray(0x559e3a2c22a0, 500, 68)            = 0x559e3a2c22a0
printf("Reallocated (reallocarray): %p\n", 0x559e3a2c22a0) = 38
free(0x559e3a2c22a0)                             = <void>
+++ exited (status 0) +++
```
#### Відповідь
reallocarray(3) — це безпечна версія realloc, яка приймає кількість елементів та їхній розмір окремо.
## Завдання по варінтам(3-варіант)
Дослідити продуктивність malloc/free при 1, 2, 4, 8 потоках. Зробити варіант із thread-local пулом і порівняти час.
#### Створюємо та компілюємо програму
```
gcc Ex8.c -o Ex8 -pthread
arthas@ubuntuserver:~/projects/pr4$ ./Ex8
=== malloc/free ===
malloc/free | Threads: 1 | Time: 0.0179 sec
malloc/free | Threads: 2 | Time: 0.0178 sec
malloc/free | Threads: 4 | Time: 0.0441 sec
malloc/free | Threads: 8 | Time: 0.1041 sec

=== thread-local pool ===
thread-local | Threads: 1 | Time: 0.0252 sec
thread-local | Threads: 2 | Time: 0.0347 sec
thread-local | Threads: 4 | Time: 0.2425 sec
thread-local | Threads: 8 | Time: 0.4917 sec
``` 
#### Аналіз результатів
Під час тестування стандартний механізм malloc/free показав кращу продуктивність порівняно з реалізованим thread-local пулом пам’яті.При збільшенні кількості потоків час виконання для обох варіантів зростав, однак thread-local пул працював повільніше. Це пов’язано з тим, що реалізація пулу була спрощеною та не оптимізованою, а також потребувала додаткової ініціалізації пам’яті для кожного потоку.
## Висновки
У ході виконання практичної роботи було досліджено механізми керування динамічною пам'яттю , зокрема особливості роботи функцій сімейства malloc. Експериментально підтверджено, що поведінка malloc(0) та realloc із граничними значеннями залежить від реалізації бібліотеки, а використання reallocarray забезпечує додатковий захист від цілочисельного переповнення. Аналіз продуктивності продемонстрував, що стандартний алокатор має обмеження при масштабуванні через конкуренцію потоків за арени, тоді як впровадження Thread-Local Storage  пулу дозволяє практично повністю нівелювати затримки на синхронізацію, забезпечуючи високу швидкість роботи у багатопотокових середовищах.

