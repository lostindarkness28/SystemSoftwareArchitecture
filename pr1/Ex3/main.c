#include <stdio.h>

int get_input();
void output(int x);

int process(int x);
int process1(int x);

int main() {
    int a=get_input();
    int b=process(a);
    int c=process1(a);
    output(a);
    return 0;
}
