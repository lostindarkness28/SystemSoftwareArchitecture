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
