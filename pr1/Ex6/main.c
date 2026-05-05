#include <stdio.h>

int main(){
	int total_seconds;
	int days,hours,minutes,seconds;
	int remainer;
	int is_past;
	
	is_past=0;

	printf("Enter number of seconds: ");
	scanf("%d",&total_seconds);

	if(total_seconds<0){
		is_past=1;
		total_seconds=-total_seconds;
	}

	days = total_seconds/86400;
	remainer = total_seconds%86400;

	hours = remainer/3600;
	remainer = remainer%3600;

	minutes = remainer/60;
        seconds = remainer%60;

	printf("%d seconds its %d days %d hours %d minutes %d seconds",total_seconds,days,hours,minutes,seconds);
	if(is_past==1){
		printf(" ago(in the past).\n");
	}else{
		printf(".\n");
	}
	return 0;

}
