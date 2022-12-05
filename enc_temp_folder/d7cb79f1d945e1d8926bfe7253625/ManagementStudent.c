// ManagementStudent.c.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define SIZE 100

typedef struct {
	int id;
	char fullName[40];
	char phoneNumber[15];
	float gradeMath;
	float gradePhysic;
	float gradeChemistry;
	float gpa;

} Student;


void findStudentByName(Student* students, const int size, Student* result, int* found, char* name);

int findStudentById(Student* students, const int size, int id);

void findStudentHasMaxGpa(Student* students, const int size,  Student* result, int* found);

float getMaxGpa(Student* students, int size);

void getStudentInfo(Student* s);

void showStudentInfo(Student s);

void showHeader();

void showStudents(Student* students, const int size);

void swap(Student* a, Student* b);

void sortListStudentsByName( Student* students, const int size);

void sortListStudentByGPA(Student* students, const int size);

void sortListStudentsByGPAAndName(Student* students, const int size);

void splitFullName(char* fullName, char* lastName, char* midName, char* firstName);

void trimTail(char* str);

void trimHead(char* str);

void trimMidle(char* str);

void removeSpaceInName(char* str);

void toSentenceCase(char* str);

int main() {
	int choice = 0;
	Student students[SIZE];
	int size = 0;
	do {
		printf("\n\t===================== Management Students ======================");
		printf("\n------------------------------------------------------------------");
		printf("\n1. Insert ew student in listed.");
		printf("\n2. Display all of students in listed.");
		printf("\n3. Find student have max GPA.");
		printf("\n4. Find student by ID.");
		printf("\n5. Find student by name.");
		printf("\n6. Sort listed student by ascending name a-z.");
		printf("\n7. Sort listed studenst by descending GPA.");
		printf("\n8. Sort listed students by descending GPA and ascending name a-z.");
		printf("\n0. Exit.");
		printf("\n------------------------------------------------------------------");

		printf("\nYour choice? ");
		scanf("%d", &choice);

		switch (choice) {
		case 0:
		{
			printf("\nThanks for using.");
			break;
		}
		case 1:
		{
			Student s; 
			getStudentInfo(&s);
			students[size++] = s;
			break;
		}
		case 2:
		{
			if (size > 0) {
				printf("\n\t=================> Information's Students <==================");

				showStudents(students, size);

			}
			else {
				printf("\nThe listed students is empty. Please create inforamtion's students first!");
			}
			break;
		}
		case 3:
		{
			if (size > 0) {

				int found = 0;

				Student result[SIZE];

				findStudentHasMaxGpa(students, size, result, &found);

				printf("\n%d", found);

				printf("\n\t========> Listed Students have  MAX GPA <===========");

				showStudents(result, found);

			}
			else {
				printf("\nThe listed students is empty. Please create inforamtion's students first!");
			}
			break;

		}
		case 4:
		{
			if (size > 0) {
				int id;
				printf("\nEnter ID's student that you want to search: ");
				scanf("%d", &id);

				int index = findStudentById(students, size, id);

				if (index == -1) {
					printf("\nDon't find students has ID: %d ins list. Please try again!", id);
				}
				else {
					printf("\nInformation's students has ID: %d", id);

					showHeader();

					showStudentInfo(students[index]);
				}
			}
			else {
				printf("\nThe listed students is empty. Please create inforamtion's students first!");
			}
			break;
		}
		case 5:
		{
			if (size > 0) {
				int found = 0;

				Student result[SIZE];

				char name[40];
				printf("\nEnter name's student that you want to search: ");
				scanf("%*c");
				scanf("%39[^\n]", name);

				removeSpaceInName(name);
				toSentenceCase(name);

				findStudentByName(students, size, result, &found, name);

				if (found == 0) {
					printf("\nDon't find students has name: %s", name);
					printf("\nPlease try again!");
				}
				else {
					printf("\n\t Information's students has name: %s", name);

					showStudents(result, found);
				}


			}
			else {
				printf("\nThe listed students is empty. Please create inforamtion's students first!");
			}
			break;
		}
		case 6:
		{
			if (size > 0) {
				sortListStudentsByName(students, size);
				printf("\n\t==========> Listed Students after sorted by ascending name a-z <=================");
				showStudents(students, size);
			}
			else {
				printf("\nThe listed students is empty. Please create inforamtion's students first!");
			}
			break;
		}
		case 7:
		{
			if (size > 0) {

				sortListStudentByGPA(students, size);

				printf("\n\t=============> Listed Students after sorted by descending GPA <===================");

				showStudents(students, size);

			}
			else {
				printf("\nThe listed students is empty. Please create inforamtion's students first!");
			}
			break;
		}
		case 8:
		{
			if (size > 0) {
				sortListStudentsByGPAAndName(students, size);

				printf("\n\t==============> Listed Students after sorted descending GPA and ascending name a-z <======================");

				showStudents(students, size);
			}
			else {
				printf("\nThe listed students is empty. Please create inforamtion's students first!");
			}
			break;
		}
		default:
		{
			printf("\nInvalid choice. Please try again!");
			break;
		}

		}


	} while (choice != 0);

	return 0;
}

void swap(Student* a, Student* b) {
	Student tmp = *a;
	*a = *b;
	*b = tmp;
}

void sortListStudentsByName( Student* students, const int size) {

	for (int i = 0; i < size - 1; i++) {
		for (int j = size - 1; j > i; j--) {

			char lastNameFirst[10];
			char midNameFirst[20];
			char firstNameFirst[10];

			char lastNameSecond[10];
			char midNameSecond[20];
			char firstNameSecond[20];

			splitFullName(students[j - 1].fullName, lastNameFirst, midNameFirst, firstNameFirst);

			splitFullName(students[j].fullName, lastNameSecond, midNameSecond, firstNameSecond);

			if (strcmp(firstNameFirst, firstNameSecond) > 0) {

				swap(&students[j - 1], &students[j]);
			}
			else if (strcmp(firstNameFirst, firstNameSecond) == 0) {

				if (strcmp(midNameFirst, midNameSecond) > 0) {

					swap(&students[j - 1], &students[j]);

				}
				else if (strcmp(midNameFirst, midNameSecond) == 0) {

					if (strcmp(lastNameFirst, lastNameSecond) > 0)
					{
						swap(&students[j - 1], &students[j]);

					}
				}
			}


		}
	}

}

void sortListStudentByGPA(Student* students, const int size) {

	for (int i = 0; i < size - 1; i++) {

		for (int j = size; j > i; j--) {

			if (students[j - 1].gpa < students[j].gpa) {

				swap(&students[j - 1], &students[j]);
			}
		}
	}

}

void sortListStudentsByGPAAndName(Student* students, const int size) {

	for (int i = 0; i < size - 1; i++) {
		for (int j = size - 1; j > i; j++) {
			if (students[j - 1].gpa < students[j].gpa) {

				swap(&students[j - 1], &students[j]);
			}

			if (students[j - 1].gpa == students[j].gpa) {

				char lastNameFirst[10];
				char midNameFirst[20];
				char firstNameFirst[10];

				char lastNameSecond[10];
				char midNameSecond[20];
				char firstNameSecond[20];

				splitFullName(students[j - 1].fullName, lastNameFirst, midNameFirst, firstNameFirst);

				splitFullName(students[j].fullName, lastNameSecond, midNameSecond, firstNameSecond);
				

				int index1 = strcmp(firstNameFirst, firstNameSecond);

				int index2 = strcmp(midNameFirst, midNameSecond);

				int index3 = strcmp(lastNameFirst, lastNameSecond);

				if (index1 > 0) {
					swap(&students[j - 1], &students[j]);

				}
				else if (index1 == 0) {
					if (index2 > 0) {
						swap(&students[j - 1], &students[j]);

					}
					else if (index2 == 0) {
						if (index3 > 0) {
							swap(&students[j - 1], &students[j]);

						}
					}
				}
			} 
		}
	}

}




void splitFullName( char*  fullName, char* lastName, char* midName, char* firstName) {
	char name[40];
	strcpy(name, fullName);

	char** words = (char**)malloc(5 * sizeof(char*));
	for (int i = 0; i < 5; i++) {
		words[i] = (char*)malloc(20 * sizeof(char));
	}

	const char* delim = " ";
	char* p = strtok(name, delim);
	int count = 0;
	while (p != NULL) {
		strcpy(words[count], p);
		count++;
		p = strtok(NULL, delim);
	}

	if (count == 2) {
		strcpy(lastName, words[0]);
		const char* space = " ";
		strcpy(midName, space);
		strcpy(firstName, words[1]);
	}
	else if (count == 3) {
		strcpy(lastName, words[0]);
		strcpy(midName, words[1]);
		strcpy(firstName, words[2]);


	}
	else if (count == 4) {
		strcpy(lastName, words[0]);
		const char* space = " ";

		strcat(words[1], space);

		strcat(words[1], words[2]);
		strcpy(midName, words[1]);
		strcpy(firstName, words[3]);

	}

	for (int i = 0; i < count; i++) {
		free(words[i]);
	}
	free(words);
}


void findStudentByName(Student* students, const int size, Student* result, int* found, char* name) {

	for (int i = 0; i < size; i++) {
		if (strcmp(students[i].fullName, name) == 0) {
			result[(*found)++] = students[i];
		}
	}
}


int findStudentById(Student* students, const int size, int id) {
	for (int i = 0; i < size; i++) {
		if (students[i].id == id) {
			return i;
		}
	}
	return -1;
}


void findStudentHasMaxGpa(Student* students, const int size, Student* result, int* found) {
	float maxGPA = getMaxGpa(students, size);

	for (int i = 0; i < size; i++) {
		if (students[i].gpa == maxGPA) {
			result[ (*found)++] = students[i];
		}
	}
}


float getMaxGpa(Student* students, int size) {
	float max = students[0].gpa;

	for (int i = 1; i < size; i++) {
		if (students[i].gpa > max) {
			max = students[i].gpa;
		}
	}

	return max;
}


void showStudents(Student* students, const int size) {
	showHeader();
	for (int i = 0; i < size; i++) {
		showStudentInfo(students[i]);
	}
}

void getStudentInfo(Student* s) {

	printf("\nEnter ID: ");
	scanf("%d", &s->id);

	printf("\nEnter full name: ");
	scanf("%*c");
	scanf("%39[^\n]", s->fullName);

	removeSpaceInName(s->fullName);
	toSentenceCase(s->fullName);

	printf("\nEnter phone number: ");
	scanf("%*c");
	scanf("%14[^\n]", s->phoneNumber);

	printf("\nEnter grade subject Math: ");
	scanf("%f", &s->gradeMath);

	printf("\nEnter grade subject Physic: ");
	scanf("%f", &s->gradePhysic);

	printf("\nEnter garde subject Chemistry: ");
	scanf("%f", &s->gradeChemistry);

	s->gpa = (s->gradeMath + s->gradePhysic + s->gradeChemistry) / 3;


}

void showStudentInfo(Student s) {
	printf("\n%-10d%-40s%-15s%-10.2f%-10.2f%-10.2f%-10.2f\n", s.id, s.fullName, s.phoneNumber,
		s.gradeMath, s.gradePhysic, s.gradeChemistry, s.gpa);
}

void showHeader() {
	printf("\n%-10s%-40s%-15s%-10s%-10s%-10s%-10s\n", "ID", "Full Name", "Phone", "M", "P", "C", "GPA");
}


void trimTail(char* str) {
	int n = strlen(str);
	int count = 0; 
	int i = n - 1;
	while (isspace(str[i])) {
		count++;
		i--;
	}

	str[n - count] = '\0';

}
void trimHead(char* str) {
	int n = strlen(str);
	int count = 0; 
	int i = 0;

	while (isspace(str[i])) {
		count++;
		i++;
	}

	for (int i = 0; i < n - count; i++) {
		str[i] = str[i + count];
	}

	str[n - count] = '\0';

}
void trimMidle(char* str) {
	int n = strlen(str);

	for (int i = 0; i < n - 1; i++) {
		if (isspace(str[i]) && isspace(str[i + 1])) {

			for (int j = i; j < n - 1; j++) {
				str[j] = str[j + 1];
			}
			str[n - 1] = '\0';
			n--; 
			i--;
		}
	}
}
void removeSpaceInName(char* str) {
	trimHead(str);
	trimTail(str);
	trimMidle(str);

}
void toSentenceCase(char* str) {
	int n = strlen(str);

	str[0] = toupper(str[0]);
	for (int i = 0; i < n - 1; i++) {
		if (i < n - 1 && isspace(str[i]) && !isspace(str[i + 1])) {
			str[i + 1] = toupper(str[i + 1]);
		}
	}
}