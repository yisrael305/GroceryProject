#pragma once
#ifndef List
#define List
#include "projectGroceryHead.h"


void readFile(FILE* fp, struct list* listOfDebts);
void addToHead(struct list* list, struct client* newClient);
void addToTail(struct list* list, struct client* newClient);
void addToExistingClient(struct list* listOfDebts, struct client* existingClient, struct client* newClient);
void addToSortedList(struct list* listOfDebts, struct client* newClient);
void popClientfromTheList(struct list* listOfDebts, struct client* existingClient);
struct list* createList();
#endif
