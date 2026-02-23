#include<stdio.h>
#include <stdlib.h>
#define MIN_SIZE 2
#define MAX_SIZE 6
size_t memory=0;
void memory_status(){
	printf("Виділено зараз:%zu байтів\n",memory);
	printf("------------------------------------------\n");
}
void* tracked_malloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr) {
        memory += size;
        printf("ПОДІЯ: Виділено %zu байтів за адресою %p\n", size, ptr);
    }
    return ptr;
}
void* tracked_realloc(void *ptr, size_t old_size, size_t new_size) {
    void *new_ptr = realloc(ptr, new_size);
    if (new_ptr || new_size == 0) {
        memory -= old_size;
        memory += new_size;
        printf("ПОДІЯ: Зміна розміру з %zu на %zu байтів\n", old_size, new_size);
    }
    return new_ptr;
}
void tracked_free(void *ptr, size_t size) {
    if (ptr) {
        free(ptr);
        memory -= size;
        printf("ПОДІЯ: Звільнено %zu байтів\n", size);
    }
}
int main(){
	int i;
	int size,new_size;
	int *arr;
	printf("Програма керування динамічною пам'яттю\n");
    	memory_status();
	printf("Print start size of array(%d-%d): ",MIN_SIZE, MAX_SIZE);
	if(scanf("%d",&size)!=1||size<MIN_SIZE||size>MAX_SIZE){
		printf("Error!\n");
		return 1;
	}
	arr=(int*)tracked_malloc(size*sizeof(int));
	for(i=0;i<size;i++){
		*(arr+i)=size;
	}
	memory_status();
	printf("Array:" );
	for(i=0;i<size;i++){
		printf("%d ",*(arr+i));
	}
	printf("\n");
	printf("Print new size of array(%d-%d): ",MIN_SIZE, MAX_SIZE);
	if(scanf("%d",&new_size)!=1||new_size<MIN_SIZE||new_size>MAX_SIZE){
                printf("Error!\n");
                return 1;
        }
	int *temp=(int*)tracked_realloc(arr,size*sizeof(int),new_size * sizeof(int));
	arr=temp;

	for(i=0;i<new_size;i++){
		*(arr+i)=new_size;
	}
	memory_status();
	printf("New array:" );
        for(i=0;i<new_size;i++){
               	printf("%d ",*(arr+i));
       	}
	printf("\n");
	tracked_free(arr,new_size*sizeof(int));
	memory_status();
	return 0;
}
