#include <stdio.h>
int main() {
    int i = 1;
    char arr1[10000];
    char arr2[20000];
    char arr3[30000];

    printf("The stack top is near %p\n", &i);
    printf("Address of arr1: %p\n", arr1);
    printf("Address of arr2: %p\n", arr2);
    printf("Address of arr3: %p\n", arr3);

    return 0;
}
