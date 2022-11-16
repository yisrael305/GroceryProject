#include "List.h"
#include "Validation.h"
#include "MatchClient.h"
#include "Client.h"
#include "GeneralFunc.h"
/*Function to read a csv file in and create a list of clients
the fubctin checks on any data if its valid and if not lighting the proper error on the errors array of the client.*/
void readFile(FILE* fp, struct list* listOfDebts)
{
	char ch; // Uses to check if we past the EOF symbol.

	int(*func[4])(char**) = { validName,validName,validID,validPhone };

	while ((ch = getc(fp)) != EOF)
	{
		char* line;
		int i = 0;

		fseek(fp, -1, SEEK_CUR);
		line = readInput(fp);

		struct client* newClient = createClient();
		char** Client_param[4] = { &newClient->firstName,&newClient->lastName,&newClient->ID,&newClient->phone };

		char* token = strtok(line, ",\n");
		while (i < 4)
		{
			if ((func[i](&token)))
			{
				newClient->errors |= 1 << i;
			}
			*(Client_param[i]) = _strdup(token);

			token = strtok(NULL, ",\n");
			i++;
		}
		if (validNumber(&token))
		{
			newClient->debt = (float)atof(token);
			newClient->errors |= 1 << 4;
		}
		else newClient->debt = 1;

		token = strtok(NULL, ",\n");

		if (validDate(&token))               // Extracting date of record
		{
			token = strtok(token, ",/\n");
			newClient->dateOfDebt.day = atoi(token);

			token = strtok(NULL, ",/\n");
			newClient->dateOfDebt.month = atoi(token);

			token = strtok(NULL, ",/\n");
			newClient->dateOfDebt.year = atoi(token);
			if ((newClient->dateOfDebt.year > 0) && (newClient->dateOfDebt.month > 0 && newClient->dateOfDebt.month <= 12) && (newClient->dateOfDebt.day >= 1 && newClient->dateOfDebt.day <= 31))
			{
				newClient->errors |= 1 << 5;
			}
		}
		else
		{
			newClient->errors |= 1 << 5;
		}

		newClient->errors |= 1 << 6;
		newClient->errors |= 1 << 7;

		free(line);

		struct client* temp = checkForExistingID(listOfDebts, newClient->ID);
		if (temp != NULL)
		{
			if (matchNameAndID(newClient, listOfDebts) == 0)
			{
				addToExistingClient(listOfDebts, temp, newClient);
				addToSortedList(listOfDebts, temp);
				freeClient(newClient);
			}
			else addToSortedList(listOfDebts, newClient);
		}
		else addToSortedList(listOfDebts, newClient);
	}
}

/*Function to add a client to the head of the list if its empty or has the bigger debt*/
void addToHead(struct list* list, struct client* newClient) 
{
	if (list->head == NULL) {

		newClient->next = NULL;
		list->head = list->tail = newClient;
		list->maxDebt = newClient->debt;
		return;
	}

	newClient->next = list->head;
	list->head = newClient;

	if (list->maxDebt < newClient->debt)
		list->maxDebt = newClient->debt;

}

/*Function to add a client to the tail of the list if its empty or has the smaller debt*/
void addToTail(struct list* list, struct client* newClient)
{
	list->tail->next = newClient;
	list->tail = newClient;
	list->tail->next = NULL;
}

/*Function to add to an exicisiting client, the function will update the tebt and if it's a newer record will update the phone*/
void addToExistingClient(struct list* listOfDebts, struct client* existingClient, struct client* newClient)
{
	existingClient->debt += newClient->debt;

	if (!checkIfItsNew(&existingClient->dateOfDebt, &newClient->dateOfDebt))
	{
		if (existingClient->debt > 0)
			existingClient->debt = 0;
	}
	else
	{
		existingClient->dateOfDebt = newClient->dateOfDebt;
		free(existingClient->phone);
		existingClient->phone = _strdup(newClient->phone);
		if (CHECK_BIT(newClient->errors, 3))
			existingClient->errors |= 1 << 3;

		if (existingClient->debt > 0)
			existingClient->debt = 0;
	}
	popClientfromTheList(listOfDebts, existingClient);
}

/*Function to sortly add a client to the list by his size of debt*/
void addToSortedList(struct list* listOfDebts, struct client* newClient) {

	if (listOfDebts->head == NULL)                                          // If the list is empty.
	{
		addToHead(listOfDebts, newClient);
		return;
	}

	if (newClient->debt > 0) newClient->debt = 0;                       // Client can't be with positive debt.

	if (newClient->debt <= listOfDebts->head->debt) {

		addToHead(listOfDebts, newClient);
		return;
	}
	else if (newClient->debt >= listOfDebts->tail->debt) {

		addToTail(listOfDebts, newClient);
		return;
	}
	else {
		struct client* prev = listOfDebts->head;                         // Prev will use to grab client on the list that the new client should come afte him. 

		while (prev->next != NULL && prev->next->debt < newClient->debt)
		{
			prev = prev->next;
		}
		newClient->next = prev->next;                                    // Placing the new client.
		prev->next = newClient;
	}
}

void popClientfromTheList(struct list* listOfDebts, struct client* existingClient) {

	if (existingClient == listOfDebts->head) {
		listOfDebts->head = listOfDebts->head->next;
		existingClient->next = NULL;
	}
	else {
		struct client* prev = listOfDebts->head;
		while (prev->next != existingClient) {
			prev = prev->next;
		}
		prev->next = existingClient->next;
		existingClient->next = NULL;
		if (existingClient == listOfDebts->tail)
		{
			listOfDebts->tail = prev;
		}
	}
}

/*function to alocate a list of clients*/
struct list* createList()
{
	struct list* temp = (struct list*)malloc(sizeof(struct list));

	while (temp == NULL)
	{
		printf("Allocation failed!");
		struct list* temp = (struct list*)malloc(sizeof(struct list));
	}
	if (temp) {
		temp->head = NULL;
		temp->tail = NULL;
		temp->next = NULL;
		temp->maxDebt = 0;
		temp->next = NULL;
	}
	return temp;
}
