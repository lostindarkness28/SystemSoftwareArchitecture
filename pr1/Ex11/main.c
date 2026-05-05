#include<stdio.h>
#include<string.h>

#define MAX_STUDENTS 100
#define STR_LEN 50

typedef struct{
	int day;
	int month;
	int year;
}Date;
typedef struct {
    int id;
    char name[STR_LEN];
    Date birth_date;
    char address[STR_LEN];
} Student;
Student db[MAX_STUDENTS];
int student_count=0;

void search(){
	char string[STR_LEN];
	int i;
	int found;

	printf("Введіть частину імені: ");
	scanf("%s",string);
	printf("\n--- Результати пошуку ---\n");
    	for (i = 0; i < student_count; i++) {
        	if (db[i].id != -1 && strstr(db[i].name, string) != NULL) {
            		printf("ID: %d | Ім'я: %s | Адреса: %s\n", 
                   		db[i].id, db[i].name, db[i].address);
            	found = 1;
        	}
    	}

    	if (!found) {
        	printf("Збігів не знайдено.\n");
    	}
}

void add_student(){
	if (student_count >= MAX_STUDENTS){
		printf("База переповнена\n");
		return;
	}
	Student* s = &db[student_count];
	s->id= student_count+1;
	printf("Ім'я: ");
    	scanf("%s", s->name);
    	printf("Дата народження (д м р): ");
	scanf("%d %d %d", &s->birth_date.day, &s->birth_date.month, &s->birth_date.year);
    	printf("Адреса: ");
    	scanf("%s", s->address);

    	student_count++;
    	printf("Студента додано з ID: %d\n", s->id);
}
void show_students() {
    	int i;
    	printf("\n--- Список студентів ---\n");
    	for (i = 0; i < student_count; i++) {
        	if (db[i].id != -1) {
            		printf("ID: %d | Ім'я: %s | Дата: %02d.%02d.%d | Адреса: %s\n",
                   	db[i].id, db[i].name, db[i].birth_date.day, 
                   	db[i].birth_date.month, db[i].birth_date.year, db[i].address);
        	}
    	}
}
void delete_student() {
    	int id, i;
    	printf("Введіть ID для видалення: ");
    	scanf("%d", &id);
    	for (i = 0; i < student_count; i++) {
        	if (db[i].id == id) {
			db[i].id = -1;
            	printf("Запис видалено.\n");
            	return;
        	}
    	}	
    	printf("Студента не знайдено.\n");
}
int main(){
	int choice;
	while (1){
		printf("\n1. Додати\n2. Показати\n3. Видалити\n4. Пошук\n5  Вихід\nВибір: ");
        	scanf("%d", &choice);

        	switch (choice) {
            		case 1: add_student(); break;
            		case 2: show_students(); break;
            		case 3: delete_student(); break;
			case 4: search();break;
            		case 5: return 0;
            		default: printf("Невірний вибір.\n");

		}
	}
	return 0;
}
