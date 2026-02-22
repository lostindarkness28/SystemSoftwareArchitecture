#include <stdio.h>

int main() {
    int base;
    int ch;
    double result = 0;
    int value;
    int is_fraction=0;
    double weight=1;	

    printf("Введіть основу: ");
    if(scanf("%d", &base) != 1) return 0;

    while((ch = getchar()) != EOF && ch != '\n') {
        value = -1;
	if (ch == '.') {
            is_fraction = 1;
            continue;
        }
        if(ch >= '0' && ch <= '9') {
             value = ch-'0';
        }
	else if (ch >= 'A' && ch <= 'Z') {
            value = ch - 'A' + 10;
        } else if (ch >= 'a' && ch <= 'z') {
            value = ch - 'a' + 10;
        }

        if(value >= 0 && value < base){
            if(!is_fraction){
		 result = result * base + value;
	    }
	    else{
		weight=weight/base;
		result = result + (value * weight);
	   }
        }
    }

    printf("Результат: %f\n", result);
    return 0;
}
