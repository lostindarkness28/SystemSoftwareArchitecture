#include <stdio.h>
enum Month{
                JAN=1,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC
};
enum CalendarType {
    GREGORIAN = 1, JULIAN = 2
};
struct Date{
	int day;
	enum Month month;
	int year;
	enum CalendarType type;
};
int days_in_month(enum Month m, int year,enum CalendarType type) {
	switch (m) {
        	case APR: case JUN: case SEP: case NOV:
            		return 30;
        	case FEB:
			if (type == JULIAN) {
                		return (year % 4 == 0) ? 29 : 28;
            	} else {
                	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
                    		return 29;
                	else
                    		return 28;
            		}
        	default:
            		return 31;
    		}
}
int main(){
	struct Date today,tomorrow;
	int choice;
	printf("Оберіть календар (1 - Григоріанський, 2 - Юліанський): ");
    	scanf("%d", &choice);
    	today.type = (enum CalendarType)choice;
	printf("Введіть поточну дату (приклад 31 12 2025): ");
	scanf("%d %u %d",&today.day,(unsigned int*)&today.month,&today.year);
	if (today.month < JAN || today.month > DEC || today.day < 1 || today.day > days_in_month(today.month, today.year,today.type)) {
       		printf("Такої дати не існує!\n");
        	return 1;
    	}
	tomorrow=today;
	tomorrow.day++;
	if(tomorrow.day>days_in_month(today.month,today.year,today.type)){
		tomorrow.day=1;
		tomorrow.month++;
		if (tomorrow.month > DEC) {
         		tomorrow.month = JAN;
            		tomorrow.year++;
        	}
	}
	printf("\nЗа обраним календарем (%s):\n", (today.type == GREGORIAN ? "Григоріанський" : "Юліанський"));
	printf("Завтра буде: %02d.%02d.%d\n", tomorrow.day,(unsigned int)tomorrow.month, tomorrow.year);
	return 0;
}

