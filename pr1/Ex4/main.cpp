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
