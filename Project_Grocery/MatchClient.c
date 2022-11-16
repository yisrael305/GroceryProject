#include "MatchClient.h"

/*Function to check if there is a client with the same ID.
The function return the stuct with the identical ID and NULL if there isn't one */
struct client* checkForExistingID(struct list* listOfClient, char* ID)
{
	struct client* temp = listOfClient->head; // Temp uses to run over the list.   

	while (temp != NULL)
	{
		if (strcmp(ID, temp->ID) != 0)
			temp = temp->next;
		else break;
	}
	return temp;
}

/*Functio Check if the name of the client in the list and the name of matching ID */
int checkForMatchName(struct client* ExistingClient, struct client* newClient) {

	if (strcmp(ExistingClient->firstName, newClient->firstName))
		newClient->errors |= 1 << 6;             // Symolize an error in the suitable index.
	if (strcmp(ExistingClient->lastName, newClient->lastName))
		newClient->errors |= 1 << 6;
	if (CHECK_BIT(newClient->errors, 6) || CHECK_BIT(newClient->errors, 1))
		return 0;
	return 1;
}

/*Function to check wich date is newer, return 1 if it does, 0 if not and -1 if its even*/
int checkIfItsNew(date* excistingDate, date* newDate) 
{
	if (excistingDate->year > newDate->year)
		return 0;

	if (excistingDate->year < newDate->year)
		return 1;

	if (excistingDate->year == newDate->year)
	{
		if (excistingDate->month > newDate->month)
			return 0;
		if (excistingDate->month < newDate->month)
			return 1;
		if (excistingDate->month == newDate->month)
			if (excistingDate->day < newDate->day)
				return 1;
		if (excistingDate->day > newDate->day)
			return 0;
	}
	return -1;
}

/*Function to check if the client on the list that has the same ID, has also the same name,
returns 0 if it's match, 1 if the first name does'nt, 2 if the last name does'nt and 3 if both are'nt fiting.*/
int matchNameAndID(struct client* newClient, struct list* listOfDebts)
{
	struct client* temp = checkForExistingID(listOfDebts, newClient->ID);

	int matchIndex = 0;

	if (temp != NULL) {
		if (strcmp(temp->firstName, newClient->firstName)) {
			matchIndex = 1;
			newClient->errors |= 0 << 6;
		}
		if (strcmp(temp->lastName, newClient->lastName)) {
			matchIndex += 2;
			newClient->errors |= 0 << 7;
		}
	}
	return matchIndex;
}


