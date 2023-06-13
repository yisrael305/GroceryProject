#pragma once
#ifndef Queries
#define Queries
#include "projectGroceryHead.h"


int getQuery(FILE* fp, struct list* clientsList);
void addToFile(char* input, FILE* fp, struct list* clientsList);
void selectQuery(struct list* clientsList, char* param);
int paramCompare(char* token, void* select, int compare(char*, void*));
int getQueryValue(char* token);
#endif