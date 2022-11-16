#pragma once
#ifndef GeneralFunc
#define GeneralFunc
#include "projectGroceryHead.h"

FILE* openFile(char** nameOfFile);
void openFileError();
char* readInput(FILE* fp);
char* removeSpacesFromStr(char** string);
#endif // !1

