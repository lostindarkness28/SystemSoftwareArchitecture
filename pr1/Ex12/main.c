#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
void sort_int(int *ptr,int size){
	int i,j,temp;
	for(i=0;i<size-1;i++){
		for(j=0;j<size-i-1;j++){
			if(*(ptr+j)>*(ptr+j+1)){
				temp=*(ptr+j);
				*(ptr+j)=*(ptr+j+1);
				*(ptr+j+1)=temp;
			}
		}
	}
}
int binary_int(int *ptr,int size,int value){
	int mid;
	int *mid_ptr;
	if(size == 0){
		return -1;
	}
	mid=size/2;
	mid_ptr=ptr+mid;
	if(*mid_ptr == value){
		return 1;
	}
	if(*mid_ptr>value){
		return binary_int(ptr,mid,value);
	}else{
		return binary_int(mid_ptr+1,size-mid-1,value);
	}
}
void sort_char(char *ptr,int size){
        int i,j;
	char temp;
        for(i=0;i<size-1;i++){
                for(j=0;j<size-i-1;j++){
                        if(*(ptr+j)>*(ptr+j+1)){
                                temp=*(ptr+j);
                                *(ptr+j)=*(ptr+j+1);
                                *(ptr+j+1)=temp;
                        }
                }
        }
}
int binary_char(char *ptr,int size,char value){
        int mid;
        char *mid_ptr;
        if(size == 0){
                return -1;
        }
        mid=size/2;
        mid_ptr=ptr+mid;
        if(*mid_ptr == value){
                return 1;
        }
        if(*mid_ptr>value){
                return binary_char(ptr,mid,value);
        }else{
                return binary_char(mid_ptr+1,size-mid-1,value);
        }
}

int recursive_int(int *ptr,int size,int value){
	if(size == 0){
		return -1;
	}
	if(*ptr == value){
		return 1;
	}
	return recursive_int(ptr+1,size-1,value);
}
int recursive_char(char *ptr,int size,int value){
        if(size == 0){
                return -1;
        }
        if(*ptr == value){
                return 1;
        }
        return recursive_char(ptr+1,size-1,value);
}

int main(int argc,char *argv[]){
	int i;
        srand(time(NULL));

	if (argc < 2) {
        	printf("Використання: %s [int|float|char]\n", argv[0]);
        	return 1;
    	}
    	if (strcmp(argv[1], "int") == 0) {
		int i;
	        int val;
        	int res;

        	printf("Обрано роботу з цілими числами (int).\n");
		int arr[10];
        	int *ptr;
		ptr=arr;
		printf("Array(int): \n");
        	for(i=0;i<10;i++){
                	*(ptr+i)=rand()%100;
                	printf("Pointer %p=%d\n",ptr+i,*(ptr+i));
        	}
		sort_int(ptr,10);
		printf("Enter value for search: ");
	        scanf("%d",&val);
        	res=recursive_int(ptr,10,val);
        	if (res!=-1){
                	printf("Value %d is found!\n",val);
        	}else{
                	printf("Value isn`t found.\n ");
        	}
        	sort_int(ptr,10);
        	printf("Enter value for binary search: ");
        	scanf("%d",&val);
        	res=binary_int(ptr,10,val);
        	if (res!=-1){
                	printf("Value %d is found!\n",val);
        	}else{
                	printf("Value isn`t found.\n ");
        	}
    	}
    	else if (strcmp(argv[1], "char") == 0) {
	        char value;
		int result;
		printf("Обрано роботу з символами (char).\n");
		char arr[10];
		char *ptr=arr;
		printf("Array(char): \n");
                for(i=0;i<10;i++){
                        *(ptr+i)='A'+(rand()%26);
                        printf("Pointer %p=%c\n",ptr+i,*(ptr+i));
                }
                sort_char(ptr,10);
		printf("Enter char for search: ");
	        scanf(" %c",&value);
        	result=recursive_char(ptr,10,value);
        	if (result!=-1){
                	printf("Char %c is found!\n",value);
        	}else{
                	printf("Char isn`t found.\n ");
        	}
        	sort_char(ptr,10);
        	printf("Enter char for binary search: ");
        	scanf(" %c",&value);
        	result=binary_char(ptr,10,value);
        	if (result!=-1){
                	printf("Char %c is found!\n",value);
        	}else{
                	printf("Char isn`t found.\n ");
        	}


    	}
    	else {
        	printf("Невідомий тип даних: %s\n", argv[1]);
    	}
	return 0;
}
