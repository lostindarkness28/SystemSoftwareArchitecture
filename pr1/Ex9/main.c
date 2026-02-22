#include <stdio.h>
int replace(char *str,char new_sym){
	int count=0;
	while(*str!='\0'){
		if(*str==' '){
			*str=new_sym;
			count++;
		}
		str++;
	}
	return count;
}
int main(){
	char text[100];
	char user_sym;
	int replaced_count;
	printf("Введіть рядок з пробілами:\n");
	fgets(text,sizeof(text),stdin);
	printf("Введіть символ, на який замінити пробіли: ");
    	scanf("%c", &user_sym);
	replaced_count=replace(text,user_sym);
	printf("%s\n",text);
	printf("Кількість змінених символів:%d\n",replaced_count);
	return 0;
}
