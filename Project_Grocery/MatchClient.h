#pragma once
#ifndef MatchClient
#define MatchClient
#include "projectGroceryHead.h"

struct client* checkForExistingID(struct list* listOfClient, char* ID);
int checkForMatchName(struct client* ExistingClient, struct client* newClient);
int checkIfItsNew(date* excistingDate, date* newDate);
int matchNameAndID(struct client* newClient, struct list* listOfDebts);
#endif

