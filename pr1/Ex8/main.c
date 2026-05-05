#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
void find(int ROWS,int COLS,double matrix[ROWS][COLS],double value){
	int i,j;
	double epsilon = 0.1; 
        int found = 0;

	for (i = 0; i < ROWS; i++) {
		for(j=0; j<COLS;j++){
		        if (fabs(matrix[i][j] - value) < epsilon) {
				printf("Знайдено! Індекс: [%d] [%d] (Значення в масиві: %f)\n", i,j,matrix[i][j]);
            			found = 1;
       			}
    		}
	}
	if (!found) {
        	printf("Збігів із похибкою %f не знайдено.\n", epsilon);
    	}
}
int main(){
	int ROWS,COLS;

	printf("Print size of matrix ROWS:");
	scanf("%d",&ROWS);
	printf("COLS:");
	scanf("%d",&COLS);
	double matrix[ROWS][COLS];
        int i,j;
        double search_val;

        srand((int)time(NULL));
        for(i=0;i<ROWS;i++){
		for(j=0;j<COLS;j++){
                	matrix[i][j]=(1000000/(double)rand())*10000;
        	}
	}
        printf("\nМассив випадкових чисел:\n");
        for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++){ 
               		printf("matrix[%d][%d] = %f\n", i,j, matrix[i][j]);
        	}
		printf("\n");
	}
	printf("\nЯке число шукаємо? ");
	scanf("%lf", &search_val);
   	find( ROWS,COLS,matrix, search_val);
        return 0;
}
