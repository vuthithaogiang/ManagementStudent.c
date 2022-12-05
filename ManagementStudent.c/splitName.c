
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>

void splitFullName(char* fullName, char* lastName, char* midName, char* firstName) {

	char** words = (char**)malloc(5 * sizeof(char*));
	for (int i = 0; i < 5; i++) {
		words[i] = (char*)malloc(20 * sizeof(char));
	}

	const char* delim = " ";
	char* p = strtok(fullName, delim);
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
		strcpy(midName,words[1]);
		strcpy(firstName, words[3]);

	}
}


int main() {

	char fullName[40];
	printf("\nEnter name: ");
	scanf("%39[^\n]", fullName);

	char lastName[10];
	char midName[20];
	char firstName[10];

	splitFullName(fullName, lastName, midName, firstName);

	printf("\n%s", lastName);
	printf("\n%s", midName);

	printf("\n%s", firstName);

}