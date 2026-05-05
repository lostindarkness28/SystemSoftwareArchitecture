#include "erf_module.h"
#include <stdio.h>

int main() {
    int choice,df;
    double z;
    printf("Enter Z-score: ");
    if (scanf("%lf", &z) != 1) {
        fprintf(stderr, "Invalid input!\n");
        return 1;
    }
    printf("Enter degrees of freedom (df): ");
    if (scanf("%d", &df) != 1||df<=0) {
        fprintf(stderr, "Invalid input!\n");
        return 1;
    }
    double res_n = calculate_normal(z);
    double res_s = calculate_student(z, df);

    if(isnan(res_n)||isnan(res_s)){
        printf("Помилка: неможливо обчислити значення інтеграла!\n");
        return 1;
    }
    else{
        printf("The integral of a Normal (0,1) distribution "
        "between -Z and Z i’s: %g\n",res_n);
	printf("The integral of a Student distribution: %g (df=%d)\n", res_s, df);
    }
    printf("\nResults for input %g:\n", z);
    printf("Normal Distribution:  %g\n", res_n);
    printf("Student Distribution: %g (df=%d)\n", res_s, df);

    printf("\nCheck standard confidence intervals (Normal):\n");
    printf("1 - 90%%\n");
    printf("2 - 95%%\n");
    printf("3 - 99%%\n");
    printf("Your choice: ");
    if (scanf("%d", &choice) == 1) {
        if (choice == 1) printf("90%% Result: %g\n", calculate_normal(CI90));
        else if (choice == 2) printf("95%% Result: %g\n", calculate_normal(CI95));
        else if (choice == 3) printf("99%% Result: %g\n", calculate_normal(CI99));
        else printf("Incorrect choice\n");
    }
    return 0;
}















