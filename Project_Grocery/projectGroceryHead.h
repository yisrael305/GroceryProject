#pragma once                                                             // Israel Weiss 
#ifndef projectGroceryHead
#define projectGroceryHead

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CHUNK 10
#define LISTNAME "listOfDebts.csv"

typedef struct {
	unsigned int day : 5;   
	unsigned int month : 4;
	unsigned int year : 12;
}date;


struct client {
	char* firstName;
	char* lastName;
	char* ID;
	char* phone;
	float debt;
	date dateOfDebt;
	int errors[8];            // Array of 1 and 0 that symbolizes the validation of each field in the client in the order. the last index symbolizes error id and name not matching. 
	struct client* next;
};

struct list {
	struct client* head;
	struct client* tail;
	float maxDebt;
	struct list* next;
};

FILE* openFile(char** nameOfFile);
void openFileError();
void readFile(FILE* fp, struct list* listOfDebts);
char* readInput(FILE* fp);
struct client* createClient();
struct list* createList();
char* removeSpacesFromStr(char** string);
void addToHead(struct list* list, struct client* newClient);
void addToTail(struct list* list, struct client* newClient);
void addToExistingClient(struct list* listOfDebts, struct client* existingClient, struct client* newClient);
void addToSortedList(struct list* listOfDebts, struct client* newClient);
void popClientfromTheList(struct list* listOfDebts, struct client* existingClient);
void addToFile(char* input, FILE* fp, struct list* clientsList);
int validName(char** name);
int validID(char** ID);
int validPhone(char** phone);
int validNumber(char** number);
int validDate(char** date);
struct client* checkForExistingID(struct list* listOfClient, char* ID);
int checkForMatchName(struct client* ExistingClient, struct client* newClient);
int checkIfItsNew(date* excistingDate, date* newDate);
int matchNameAndID(char* ID, char* firstName, char* lastName, struct list* listOfDebts);
void printClient(struct client* Client);
void printList(struct list* listOfclient);
void printToFile(FILE* fp, struct client* record);
void printInstructions();
void erorrList(int type);
int getQuery(FILE* fp, struct list* clientsList);
void selectQuery(struct list* clientsList, char* param);
void freeClient(struct client* Client);
void freeList(struct list* List);
#endif