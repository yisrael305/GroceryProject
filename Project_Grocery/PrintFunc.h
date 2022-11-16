#pragma once
#ifndef PrintFunc
#define PrintFunc
#include "projectGroceryHead.h"

void printClient(struct client* Client);
void printList(struct list* listOfclient);
void printToFile(FILE* fp, struct client* record);
void printInstructions();
void erorrList(int type);

#endif
