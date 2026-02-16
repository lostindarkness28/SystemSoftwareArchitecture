#include <math.h>
#include <stdio.h>

int main() {
    int choice;
    double z;
    printf("Enter Z-score: ");
    if (scanf("%lf", &z) != 1) {
        fprintf(stderr, "Invalid input!\n");
        return 1;
    }
    double result = erf(z * sqrt(1/2.));
    if(isnan(result)){
        printf("Помилка: неможливо обчислити значення інтеграла!\n");
        return 1;
    }
    else{
        printf("The integral of a Normal (0,1) distribution "
        "between -Z and Z i’s: %g\n",result);
    }
    double ci90 = 1.64485;
    double ci95 = 1.95996;
    double ci99 = 2.57583;

    printf("Choose confidence integral:\n");
    printf("1 - 90%% Confidence Interval\n");
    printf("2 - 95%% Confidence Interval\n");
    printf("3 - 99%% Confidence Interval\n");;
    printf("Your choice: ");

    if (scanf("%d", &choice) != 1) {
        printf("Invalid input!\n");
        return 1;
    }
    if(choice == 1){
        printf("90%% CI: %g\n", erf(ci90 * sqrt(1/2.)));
    }
    if(choice == 2){
        printf("50%% CI: %g\n", erf(ci95 * sqrt(1/2.)));
    }
    if(choice == 3){
        printf("99%% CI: %g\n", erf(ci99 * sqrt(1/2.)));
    }
    else{
	printf("Incorrect choice \n");
    }
    return 0;
}















