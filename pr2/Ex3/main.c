#include <stdio.h>
#include <stdlib.h>
int g_data=62;
int g_bss;
int main() {
   	int i=1;
   	printf("The stack top is near %p\n", &i);
	int *heap=malloc(sizeof(int));
	printf("Addres of heap is near %p\n", heap);
	printf("Addres of text is near %p\n", &main);
	printf("Addres of bss is near %p\n", &g_bss);
	printf("Addres of data is near %p\n", &g_data);
   	return 0;
}
