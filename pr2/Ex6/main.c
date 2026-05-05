#include <stdio.h>
char memory[1024];
size_t counter=0;
void* my_malloc(size_t size){
	if(counter+size>1024){
   		return NULL;
       	}
        void* ptr=&memory[counter];
        counter+=size;
        return ptr;
}
void* my_free(void* ptr){
	counter = 0;
}

int main(){
	int* mal = (int*)my_malloc(sizeof(int));
    	*mal = 1000;
    	printf("mal = %d\n", *mal);
	my_free(mal);
	return 0;
}

