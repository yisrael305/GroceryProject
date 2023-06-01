#pragma once
#ifndef Validation
#define Validation
#include <stdio.h>
#include <ctype.h>


void isValidClient(struct client* clientToCheck);
int validName(void* name_);
int validID(void* ID_);
int validPhone(void* phone_);
int validNumber(void* number_);
int validDate(void* date_);
int validDateStruct(void* dateToCheck_);

#endif

