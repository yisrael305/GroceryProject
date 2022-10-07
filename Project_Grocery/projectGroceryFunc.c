#include "projectGroceryHead.h"                                     // Israel Weiss 

/*function to alocate a client*/
struct client* createClient(){

	struct client* temp = (struct client*)calloc(1, sizeof(struct client));
	if (temp == NULL)
	{
		printf("allocation failed!");
	}
	return temp;
}

/*Function to remove any spaces before and after str*/
char* removeSpacesFromStr(char** string){
	
	while (**string == ' ')
	{
		(* string)++;
	}
	
	int len = (int)strlen(*string); //A veriable uses to place a pointer in the end of sring.
	char* ch = *string + len - 1;   //Placing the pointer before '\0' or '\n'. 

	while (*ch == ' ')
	{
		*ch = '\0';                 //Peplacing the value from ' ' to a '\0'.
		ch--;
	}	
	return *string;	
}

/*Function to check if there is a client with the same ID.
The function return the stuct with the identical ID and NULL if there isn't one */
struct client* checkForExistingID(struct list* listOfClient, char* ID) {

	struct client* temp = listOfClient->head; // Temp uses to run over the list.   

	while (temp != NULL)
	{
		if (strcmp(ID, temp->ID) != 0)
			temp = temp->next;
		else break;
	}
	return temp;
}

/*Function to add a client to the head of the list if its empty or has the bigger debt*/
void addToHead(struct list* list, struct client* newClient) {

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
void addToTail(struct list* list, struct client* newClient) {

	list->tail->next = newClient;
	list->tail = newClient;
	list->tail->next = NULL;
}

/*Function to read any input, from the file or user, using the exact amount of memory that needed*/
char* readInput(FILE* fp) {


	char* input = NULL, * temp;    //Input will store the final sring' temp usea to make sure itws not NULL.
	char tempbuf[CHUNK];           //tempbuf is 10 charactors string that will add to the input string every time.
	int inputlen = 0, templen = 0; //Veriables uses to ralocate the input.
	do
	{
		do {
			fgets(tempbuf, CHUNK, fp);
			templen = (int)strlen(tempbuf);
			if ((temp = (char*)realloc(input, inputlen + templen + 1)) == NULL)
				printf("Failed to allocate memory!\n");
			input = temp;
		} while (!input);
		strcpy(input + inputlen, tempbuf);
		inputlen += templen;
	} while (templen == CHUNK - 1 && tempbuf[CHUNK - 2] != '\n');

	input[strlen(input) - 1] = '\0';
	return input;
}

/*function to alocate a list of clients*/
struct list* createList() {

	struct list* temp = (struct list*)malloc(sizeof(struct list));

	while (temp==NULL)
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

/*Function to check that the names contains letters only*/
int validName(char** name) {

	*name = removeSpacesFromStr(name);  // Remove spaces before and after the name.

	char* ch = *name;

	while (*ch)
	{
		*ch = tolower(*ch);             // Replacing capital letters.
		if (*ch >= 'a' && *ch <= 'z' || *ch == ' ')
			ch++;
		else return 0;
	}
	return 1;
}

/*Function to check that the ID's contains 9 digits only*/
int validID(char** ID) {

	*ID = removeSpacesFromStr(ID);

	char* ch = *ID;
	int count = 0;

	while (*ch)
	{
		if (isdigit(*ch)) {
			ch++;
			count++;
		}
		else return 0;
	}

	if (count != 9)
	{
		return 0;
	}
	else return 1;
}

/*Function to check that the Phone number contains 10 digits only and starts with 0*/
int validPhone(char** phone) {

	*phone = removeSpacesFromStr(phone);

	char* ch = *phone;
	int count = 0;

	while (*ch)
	{
		if (count == 0 && *ch != '0')
		{
			return 0;
		}
		if (isdigit(*ch)) {
			ch++;
			count++;
		}
		else return 0;
	}

	if (count != 10)
	{
		return 0;
	}
	else return 1;
}

/*Function to check that the debt contains digits only*/
int validNumber(char** number) {

	*number = removeSpacesFromStr(number);

	char* ch = *number;
	int i = 0;
	while (*ch) {
		if (i == 0) {
			if (*ch == '-' || isdigit(*ch)) {
				ch++;
				i++;
			}
			else return 0;
		}
		else if (isdigit(*ch) || *ch == '.') {
			ch++;
			i++;
		}
		else return 0;
	}
	return 1;
}

/*Function to check that the date is in the right format*/
int validDate(char** date) {

	*date = removeSpacesFromStr(date);

	char* ch = *date;
	int i = 0;

	while (*ch) {

		if (isdigit(*ch)) {
			i++;
			ch++;
		}
		else if (i > 0 || i < 5) {
			if (*ch == '/') {
				ch++;
				i++;
			}
			else return 0;
		}
	}
	return 1;
}

void openFileError() {

	printf("Can't open file\n");

}

/*Functio to Check if the name of the client in the list and the name of matching ID's */
int checkForMatchName(struct client* ExistingClient, struct client* newClient) {

	if (strcmp(ExistingClient->firstName, newClient->firstName))
		newClient->errors[6] = 1;             // Symolize an error in the suitable index.
	if (strcmp(ExistingClient->lastName, newClient->lastName))
		newClient->errors[6] = 1;
	if (newClient->errors[6] == 1 || newClient->errors[1] == 1)
		return 0;
	return 1;
}

/*Function to check wich date is newer, return 1 if it does, 0 if not and -1 if its even*/
int checkIfItsNew(date* excistingDate, date* newDate) {

	if (excistingDate->year > newDate->year)
		return 0;

	if (excistingDate->year < newDate->year)
		return 1;

	if (excistingDate->year == newDate->year) {
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

/*Function to add to an exicisiting client, the function will update the tebt and if it's a newer record will update the phone*/
void addToExistingClient(struct list* listOfDebts, struct client* existingClient, struct client* newClient) {

	existingClient->debt += newClient->debt;

	if (!checkIfItsNew(&existingClient->dateOfDebt, &newClient->dateOfDebt)) {
		if (existingClient->debt > 0)
			existingClient->debt = 0;
	}
	else {
		existingClient->dateOfDebt = newClient->dateOfDebt;
		free(existingClient->phone);
		existingClient->phone = _strdup(newClient->phone);
		if (existingClient->debt > 0)
			existingClient->debt = 0;
	}
	popClientfromTheList(listOfDebts, existingClient);
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

/*Function to free memory from specific client*/
void freeClient(struct client* Client) {                                      

	free(Client->firstName);
	free(Client->lastName);
	free(Client->ID);
	free(Client->phone);
	free(Client);

	Client = NULL;                    // The pointer of client refering now to a NULL.
}

/*Function to free memory from all the list*/
void freeList(struct list* List) {

	struct client* Client;

	while (Client = List->head)
	{
		List->head = List->head->next;
		freeClient(Client);
	}
	free(List);
	List = NULL;
}

/*Function to print a specific client*/
void printClient(struct client* Client) {

	printf("%-12s  |", Client->firstName);
	printf("%-12s  |", Client->lastName);
	printf("%-11s  |", Client->ID);
	printf("%-12s  |", Client->phone);
	printf("%8.2lf  |", Client->debt);
	printf("%02d/%02d/%-4d\n", Client->dateOfDebt.day, Client->dateOfDebt.month, Client->dateOfDebt.year);
	printf("------------------------------------------------------------------------------------\n");
}

/*Function to print a title for the error list acording the index of errors */
void erorrList(int type) {

	switch (type)
	{
	case 0:
		printf("The clients with invalid first name:\n\n");
		break;
	case 1:
		printf("The clients with invalid last name:\n\n");
		break;
	case 2:
		printf("The clients with invalid ID:\n\n");
		break;
	case 3:
		printf("The clients with invalid phone:\n\n");
		break;
	case 4:
		printf("The clients with invalid debt:\n\n");
		break;
	case 5:
		printf("The clients with invalid date:\n\n");
		break;
	case 6:
		printf("The clients id and frist name does'nt match:\n\n");
		break;
	case 7:
		printf("The clients id and last name does'nt match:\n\n");
		break;
	default:
		break;
	}


}

/*Function to print all list, valid clients first*/
void printList(struct list* listOfclient) {

	printf("\t\tlist of debts\n\n");
	printf("First Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");

	struct client* temp = listOfclient->head;   
	int validClient;                              // Uses to determine if temp is valid client before printing him.

	while (temp != NULL)                          // Runing over the list using temp.
	{
		for (int i = 0; i < 8; i++) {             // Checking if there is an error on the client.
			if (!temp->errors[i])
			{
				validClient = 1;
			}
			else {
				validClient = 0;
				break;
			}
		}
		if (validClient)                       // Printing all valid clients.
		{
			printClient(temp);
		}
		temp = temp->next;

	}
	printf("\n");

	temp = listOfclient->head;                   

	for (int i = 0; i < 8; i++) {              // Printing the clients with an errors by index of errors.

		temp = listOfclient->head;

		while (temp != NULL) {

			if (temp->errors[i])
			{
				printf("\n");
				erorrList(i);
				while (temp != NULL) {

					if (temp->errors[i]) {
						printClient(temp);
						temp = temp->next;
					}
					else temp = temp->next;
				}
				break;
			}
			temp = temp->next;
		}
	}
	printf("\n");
}

/*Function to print some instructions to the user*/
void printInstructions() {

	printf("Instructions:\n\n");
	printf("In order to add a new record to the list please enter set,\nthan enter the details according to the template:\n");
	printf("first name:Israel, last name: Israely, ID:123456789, Phone Number:0501234567, Debt:-78.26, Date:25/08/2021\n\n");
	printf("In order to print a specific data from the list please enter select,\nthan enter the the query:\n");
	printf("you can ask for specific data using the <>!= notations.\n\n");
	printf("In order to print all the list simpely enter print.\n\n");
	printf("for exit press enter quit.\n");

}

/*Function to check if the client on the list that has the same ID, has also the same name,
returns 0 if it's match, 1 if the first name does'nt, 2 if the last name does'nt and 3 if both are'nt fiting.*/
int matchNameAndID(char* ID, char* firstName, char* lastName, struct list* listOfDebts) {

	struct client* temp = checkForExistingID(listOfDebts, ID);   

	int matchIndex = 0;

	if (temp != NULL) {
		if (strcmp(temp->firstName, firstName))
			matchIndex = 1;
		if (strcmp(temp->lastName, lastName))
			matchIndex += 2;
	}
	return matchIndex;
}

/*Fnction to build a new client from input and add him to the list and file*/
void addToFile(char* input, FILE* fp, struct list* clientsList) {

	char* line = input;
	char* ex;

	while (*line) {
		*line = tolower(*line);            // Replacig the upper case letters to make it easy to work with.
		line++;
	}
	line = _strdup(input);

	struct client* temp = createClient();  // Asiggin memory for the new client.

	char* token;                           // Uses to extract specific date from the line that scaned.  

	//Extract the first name.
	ex = strstr(line, "first name");
	if (!ex) {
		printf("looks like you forgot to type first name, enter first name:\n");
		temp->firstName = (readInput(stdin));
	}
	else {
		token = strtok(ex, ":=");
		token = strtok(NULL, ",");
		temp->firstName = _strdup(token);
	}

	while (!validName(&temp->firstName)) {

		free(temp->firstName);
		printf("Invalid first name, please enter first name again\n");
		temp->firstName = (readInput(stdin));
		if (!strcmp(temp->firstName, "quit")) {
			free(temp->firstName);
			free(temp);
			return;
		}
	}

	free(line);
	line = _strdup(input);

	//Extract the last name.
	ex = strstr(line, "last name");
	if (!ex) {
		printf("looks like you forgot to type last name, enter last name:\n");
		temp->lastName = (readInput(stdin));
	}
	else {
		token = strtok(ex, ":=");
		token = strtok(NULL, ",");
		temp->lastName = _strdup(token);
	}

	while (!validName(&temp->lastName)) {
		free(temp->lastName);
		printf("Invalid last name, please enter last name again\n");
		temp->lastName = (readInput(stdin));
		if (!strcmp(temp->lastName, "quit")) {
			free(temp->firstName);
			free(temp->lastName);
			free(temp);
			return;
		}
	}
	free(line);
	line = _strdup(input);

	//Extract the ID.
	ex = strstr(line, "id");
	if (!ex) {
		printf("looks like you forgot to type any ID, enter ID:\n");
		temp->ID = (readInput(stdin));
	}
	else {
		token = strtok(ex, ":=");
		token = strtok(NULL, ",");
		temp->ID = _strdup(token);
	}

	while (!validID(&temp->ID)) {
		free(temp->ID);
		printf("Invalid ID, please enter ID again\n");
		temp->ID = (readInput(stdin));
		if (!strcmp(temp->ID, "quit")) {
			free(temp->firstName);
			free(temp->lastName);
			free(temp->ID);
			free(temp);
			return;
		}
	}

	int matchIndex;
	while (matchIndex = matchNameAndID(temp->ID, temp->firstName, temp->lastName, clientsList))  // The user must to enter matching detailes for excisting ID.  
	{
		switch (matchIndex)
		{
		case 1:
		{
			free(temp->firstName);
			printf("the firse name does not match an excisting ID, please enter first name:\n");
			temp->firstName = (readInput(stdin));
			if (!strcmp(temp->firstName, "quit")) {
				free(temp->firstName);
				free(temp->lastName);
				free(temp->ID);
				free(temp);
				return;
			}
			break;
		}
		case 2:
		{
			free(temp->lastName);
			printf("the last name does not match an excisting ID, please enter last name:\n");
			temp->lastName = (readInput(stdin));
			if (!strcmp(temp->lastName, "quit")) {
				free(temp->firstName);
				free(temp->lastName);
				free(temp->ID);
				free(temp);
				return;
			}
			break;
		}
		case 3:
		{
			free(temp->firstName);
			free(temp->firstName);
			printf("the firse and last name does not match an excisting ID, please enter again:\n");
			temp->firstName = (readInput(stdin));
			if (!strcmp(temp->firstName, "quit")) {
				free(temp->firstName);
				free(temp->ID);
				free(temp);
				return;
			}

			temp->lastName = (readInput(stdin));
			if (!strcmp(temp->lastName, "quit")) {
				free(temp->firstName);
				free(temp->lastName);
				free(temp->ID);
				free(temp);
				return;
			}
			break;
		}
		default:
			break;
		}
	}

	free(line);
	line = _strdup(input);

	//Extract the phone.
	ex = strstr(line, "phone");
	if (!ex) {
		printf("looks like you forgot to type any phone, enter phone number:\n");
		temp->phone = (readInput(stdin));
	}
	else {
		token = strtok(ex, ":=");
		token = strtok(NULL, ",");
		temp->phone = _strdup(token);
	}
	while (!validPhone(&temp->phone)) {
		free(temp->phone);
		printf("Invalid phone, please enter phone again\n");
		temp->phone = (readInput(stdin));
		if (!strcmp(temp->phone, "quit")) {
			free(temp->firstName);
			free(temp->lastName);
			free(temp->ID);
			free(temp->phone);
			free(temp);
			return;
		}
	}
	

	free(line);
	line = _strdup(input);

	//Extract the debt.
	ex = strstr(line, "debt");
	if (!ex) {
		printf("looks like you forgot to type any debt, please enter debt:\n");
		token = (readInput(stdin));
	}
	else {
		token = strtok(ex, ":=");
		token = strtok(NULL, ",");
		token = _strdup(token);
	}


	while (!validNumber(&token)) {
		printf("Invalid debt, please enter debt again\n");
		free(token);
		token = (readInput(stdin));
		if (!strcmp(token, "quit")) {
			free(token);
			free(temp->firstName);
			free(temp->lastName);
			free(temp->ID);
			free(temp->phone);
			free(temp);
			return;
		}
	}
	temp->debt += (float)atof(token);
	free(token);

	free(line);
	line = _strdup(input);

	//Extract the date.
	ex = strstr(line, "date");
	if (!ex) {
		printf("looks like you forgot to type any date, please enter date:\n");
		token = (readInput(stdin));
	}
	else {
		token = strtok(ex, ":=");
		token = strtok(NULL, ",");
	}

	int date = 0;        // Uses to store the parts of the date
	int flag = 1;        // Simbolize if there is a problem with date format  
	do {
		if (!flag)
		{
			printf("Invalid date, please enter date again\n");
			token = (readInput(stdin));
			if (!strcmp(token, "quit")) {
				free(token);
				free(temp->firstName);
				free(temp->lastName);
				free(temp->ID);
				free(temp->phone);
				free(temp);
				return;
			}
		}
		while (!validDate(&token)) {
			printf("Invalid date, please enter date again\n");
			token = (readInput(stdin));
			if (!strcmp(token, "quit")) {
				free(token);
				free(temp->firstName);
				free(temp->lastName);
				free(temp->ID);
				free(temp->phone);
				free(temp);
				return;
			}
		}
		token = strtok(token, "/");
		token = _strdup(token);
		date = atoi(token);
		free(token);

		if (date <= 31 && date > 0)
			temp->dateOfDebt.day = date;
		else flag = 0;

		token = strtok(NULL, "/");
		token = _strdup(token);
		date = atoi(token);
		free(token);

		if (date <= 12 && date > 0)
			temp->dateOfDebt.month = date;
		else flag = 0;

		token = strtok(NULL, "\n");
		token = _strdup(token);
		date = atoi(token);
		free(token);

		if (date <= 2500 && date > 1000)
			temp->dateOfDebt.year = date;
		else flag = 0;
	} while (temp->dateOfDebt.day == 0 || temp->dateOfDebt.month == 0 || temp->dateOfDebt.year == 0);

	free(line);
	printToFile(fp, temp);                  // Print the record to the file.
	printf("Record added succsesfuly\n");
	addToSortedList(clientsList, temp);    // Add the new client to sorted list
}

/*Function to allow the user to print a specific data from the list 
using the clients parameters and !=<> notations*/
void selectQuery(struct list* clientsList, char* param) {

	char* line = param;

	while (*line) {
		*line = tolower(*line);
		line++;
	}

	struct client* selectedClient = clientsList->head; // Using to rum over the list and compare the data that has been asked.
	line = NULL;                                       // Using to grab the parameter.
	char* op = NULL;                                   // Using to grab the notation.
	int count = 0;

	if ((line = strstr(param, "first name")) != NULL) {

		if ((op = strstr(param, "!=")) != NULL)
		{
			char* token = strtok(param, "=");
			token = strtok(NULL, "\n");

			token = removeSpacesFromStr(&token);

			if (!validName(&token))	printf("\nInvalid first name, please try again\n");
			else {
				while (selectedClient != NULL)
				{
					if (strcmp(token, selectedClient->firstName) != 0)
					{
						count++;
						if (count == 1)
							printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
						printClient(selectedClient);
						selectedClient = selectedClient->next;
					}
					else selectedClient = selectedClient->next;
				}
				if (count == 0) printf("\nNo client was found\n");
			}
		}
		else if ((op = strstr(param, "=")) > NULL) {

			char* token = strtok(param, "=");
			token = strtok(NULL, "\n");

			token = removeSpacesFromStr(&token);

			if (!validName(&token))	printf("\nInvalid first name, please try again\n");
			else {
				while (selectedClient != NULL)
				{
					if (!strcmp(token, selectedClient->firstName))
					{
						count++;
						if (count == 1)
							printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
						printClient(selectedClient);
						selectedClient = selectedClient->next;
					}
					else selectedClient = selectedClient->next;
				}
				if (count == 0) printf("\nNo client was found\n");
			}
		}
		else if (strstr(param, ">") > NULL) {

			char* token = strtok(param, ">");
			token = strtok(NULL, "\n");

			token = removeSpacesFromStr(&token);

			if (!validName(&token))	printf("\nInvalid first name, please try again\n");
			else {
				while (selectedClient != NULL)
				{
					if (strcmp(selectedClient->firstName, token) > 0)
					{
						count++;
						if (count == 1)
							printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
						printClient(selectedClient);
						selectedClient = selectedClient->next;
					}
					else selectedClient = selectedClient->next;
				}
				if (count == 0) printf("\nNo client was found\n");
			}
		}
		else if (strstr(param, "<") > NULL) {

			char* token = strtok(param, "<");
			token = strtok(NULL, "\n");

			token = removeSpacesFromStr(&token);

			if (!validName(&token))	printf("\nInvalid first name, please try again\n");
			else {
				while (selectedClient != NULL)
				{
					if (strcmp(selectedClient->firstName, token) < 0)
					{
						count++;
						if (count == 1)
							printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
						printClient(selectedClient);
						selectedClient = selectedClient->next;
					}
					else selectedClient = selectedClient->next;
				}
				if (count == 0) printf("\nNo client was found\n");
			}
		}
		else printf("\nThe operator that entered is invalid for this parameter, please try again!\n");
	}
	else if ((line = strstr(param, "last name")) != NULL) {

		if (strstr(param, "!=") > NULL)
		{
			char* token = strtok(param, "=");
			token = strtok(NULL, "\n");

			token = removeSpacesFromStr(&token);

			if (!validName(&token))	printf("\nInvalid last name, please try again\n");
			else {
				while (selectedClient != NULL)
				{
					if (!strcmp(token, selectedClient->lastName))
					{
						count++;
						if (count == 1)
							printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
						printClient(selectedClient);
						selectedClient = selectedClient->next;
					}
					else selectedClient = selectedClient->next;
				}
				if (count == 0) printf("\nNo client was found\n");
			}
		}
		else if (strstr(param, "=") > NULL) {

			char* token = strtok(param, "=");
			token = strtok(NULL, "\n");

			token = removeSpacesFromStr(&token);

			if (!validName(&token))	printf("\nInvalid last name, please try again\n");
			else {
				while (selectedClient != NULL)
				{
					if (strcmp(token, selectedClient->lastName) == 0)
					{
						count++;
						if (count == 1)
							printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
						printClient(selectedClient);
						selectedClient = selectedClient->next;
					}
					else selectedClient = selectedClient->next;
				}
				if (count == 0) printf("\nNo client was found\n");
			}
		}
		else if (strstr(param, ">") > NULL) {

			char* token = strtok(param, ">");
			token = strtok(NULL, "\n");

			token = removeSpacesFromStr(&token);

			if (!validName(&token))	printf("\nInvalid last name, please try again\n");
			else {
				while (selectedClient != NULL)
				{
					if (strcmp(selectedClient->lastName, token) > 0)
					{
						count++;
						if (count == 1)
							printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
						printClient(selectedClient);
						selectedClient = selectedClient->next;
					}
					else selectedClient = selectedClient->next;
				}
				if (count == 0) printf("\nNo client was found\n");
			}
		}
		else if (strstr(param, "<") > NULL) {

			char* token = strtok(param, "<");
			token = strtok(NULL, "\n");

			token = removeSpacesFromStr(&token);

			if (!validName(&token))	printf("\nInvalid last name, please try again\n");
			else {
				while (selectedClient != NULL)
				{
					if (strcmp(selectedClient->lastName, token) < 0)
					{
						count++;
						if (count == 1)
							printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
						printClient(selectedClient);
						selectedClient = selectedClient->next;
					}
					else selectedClient = selectedClient->next;
				}
				if (count == 0) printf("\nNo client was found\n");
			}
		}
		else printf("\nThe operator that entered is invalid for this parameter, please try again!");
	}
	else if (strstr(param, "id") != NULL) {

		if (strstr(param, "!=") > NULL)
		{
			char* token = strtok(param, "=");
			token = strtok(NULL, "\n");

			token = removeSpacesFromStr(&token);

			if (!validID(&token))	printf("\nInvalid ID, please try again\n");
			else {
				while (selectedClient != NULL)
				{
					if (strcmp(token, selectedClient->ID))
					{
						count++;
						if (count == 1)
							printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
						printClient(selectedClient);
						selectedClient = selectedClient->next;
					}
					else selectedClient = selectedClient->next;
				}
				if (count == 0) printf("\nNo client was found\n");
			}
		}
		else if ((op = strstr(param, "=")) > NULL) {

			char* token = strtok(param, "=");
			token = strtok(NULL, "\n");

			token = removeSpacesFromStr(&token);

			if (!validID(&token))	printf("\nInvalid ID, please try again\n");
			else {
				while (selectedClient != NULL)
				{
					if (strcmp(token, selectedClient->ID) == 0)
					{
						count++;
						if (count == 1)
							printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
						printClient(selectedClient);
						selectedClient = selectedClient->next;
					}
					else selectedClient = selectedClient->next;
				}
				if (count == 0) printf("\nNo client was found\n");
			}
		}
		else if ((op = strstr(param, ">")) > NULL) {

			char* token = strtok(param, ">");
			token = strtok(NULL, "\n");

			token = removeSpacesFromStr(&token);

			if (!validID(&token))	printf("\nInvalid ID, please try again\n");
			else {
				while (selectedClient != NULL)
				{
					if (strcmp(selectedClient->ID, token) > 0)
					{
						count++;
						if (count == 1)
							printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
						printClient(selectedClient);
						selectedClient = selectedClient->next;
					}
					else selectedClient = selectedClient->next;
				}
				if (count == 0) printf("\nNo client was found\n");
			}
		}
		else if (strstr(param, "<") > NULL) {

			char* token = strtok(param, "<");
			token = strtok(NULL, "\n");

			token = removeSpacesFromStr(&token);

			if (!validID(&token))	printf("\nInvalid ID, please try again\n");
			else {
				while (selectedClient != NULL)
				{
					if (strcmp(selectedClient->ID, token) < 0)
					{
						count++;
						if (count == 1)
							printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
						printClient(selectedClient);
						selectedClient = selectedClient->next;
					}
					else selectedClient = selectedClient->next;
				}
				if (count == 0) printf("\nNo client was found\n");
			}
		}
		else printf("\nThe operator that entered is invalid for this parameter, please try again!");
	}
	else if ((line = strstr(param, "phone")) != NULL) {

		if (strstr(param, "!=") > NULL)
		{
			char* token = strtok(param, "=");
			token = strtok(NULL, "\n");

			token = removeSpacesFromStr(&token);

			if (!validID(&token))	printf("\nInvalid phone, please try again\n");
			else {
				while (selectedClient != NULL)
				{
					if (!strcmp(token, selectedClient->phone))
					{
						count++;
						if (count == 1)
							printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
						printClient(selectedClient);
						selectedClient = selectedClient->next;
					}
					else selectedClient = selectedClient->next;
				}
				if (count == 0) printf("\nNo client was found\n");
			}
		}
		else if (strstr(param, "=") > NULL) {

			char* token = strtok(param, "=");
			token = strtok(NULL, "\n");

			token = removeSpacesFromStr(&token);

			if (!validID(&token))	printf("\nInvalid phone, please try again\n");
			else {
				while (selectedClient != NULL)
				{
					if (strcmp(token, selectedClient->phone) != 0)
					{
						count++;
						if (count == 1)
							printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
						printClient(selectedClient);
						selectedClient = selectedClient->next;
					}
					else selectedClient = selectedClient->next;
				}
				if (count == 0) printf("\nNo client was found\n");
			}
		}
		else if (strstr(param, ">") > NULL) {

			char* token = strtok(param, ">");
			token = strtok(NULL, "\n");

			token = removeSpacesFromStr(&token);

			if (!validID(&token))	printf("\nInvalid phone, please try again\n");
			else {
				while (selectedClient != NULL)
				{
					if (strcmp(selectedClient->phone, token) > 0)
					{
						count++;
						if (count == 1)
							printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
						printClient(selectedClient);
						selectedClient = selectedClient->next;
					}
					else selectedClient = selectedClient->next;
				}
				if (count == 0) printf("\nNo client was found\n");
			}
		}
		else if (strstr(param, "<") > NULL) {

			char* token = strtok(param, "<");
			token = strtok(NULL, "\n");

			token = removeSpacesFromStr(&token);

			if (!validID(&token))	printf("\nInvalid phone, please try again\n");
			else {
				while (selectedClient != NULL)
				{
					if (strcmp(selectedClient->phone, token) < 0)
					{
						count++;
						if (count == 1)
							printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
						printClient(selectedClient);
						selectedClient = selectedClient->next;
					}
					else selectedClient = selectedClient->next;
				}
				if (count == 0) printf("\nNo client was found\n");
			}
		}
		else printf("\nThe operator that entered is invalid for this parameter, please try again!");
	}
	else if (strstr(param, "debt") != NULL) {

		if (strstr(param, "!=") > NULL)
		{
			char* token = strtok(param, "=");
			token = strtok(NULL, "\n");

			token = removeSpacesFromStr(&token);
			if (!validNumber(&token))	printf("\nInvalid debt, please try again\n");
			else {
				double comparedDebt = atof(token);

				while (selectedClient != NULL)
				{
					if (selectedClient->debt != comparedDebt)
					{
						count++;
						if (count == 1)
							printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
						printClient(selectedClient);
						selectedClient = selectedClient->next;
					}
					else selectedClient = selectedClient->next;
				}
				if (count == 0) printf("\nNo client was found\n");
			}
		}
		else if (strstr(param, "=") > NULL) {

			char* token = strtok(param, "=");
			token = strtok(NULL, "\n");

			token = removeSpacesFromStr(&token);

			if (!validNumber(&token))	printf("\nInvalid debt, please try again\n");
			else {
				float comparedDebt = (float)atof(token);

				while (selectedClient != NULL)
				{
					if (selectedClient->debt == comparedDebt)
					{
						count++;
						if (count == 1)
							printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
						printClient(selectedClient);
						selectedClient = selectedClient->next;
					}
					else selectedClient = selectedClient->next;
				}
				if (count == 0) printf("\nNo client was found\n");
			}
		}
		else if (strstr(param, ">") > NULL) {

			char* token = strtok(param, ">");
			token = strtok(NULL, "\n");

			token = removeSpacesFromStr(&token);

			if (!validNumber(&token))	printf("\nInvalid debt, please try again\n");
			else {
				float comparedDebt = (float)atof(token);

				while (selectedClient != NULL)
				{
					if (selectedClient->debt > comparedDebt)
					{
						count++;
						if (count == 1)
							printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
						printClient(selectedClient);
						selectedClient = selectedClient->next;
					}
					else selectedClient = selectedClient->next;
				}
				if (count == 0) printf("\nNo client was found\n");
			}
		}
		else if (strstr(param, "<") > NULL) {

			char* token = strtok(param, "<");
			token = strtok(NULL, "\n");

			token = removeSpacesFromStr(&token);

			if (!validNumber(&token))	printf("\nInvalid debt, please try again\n");
			else {
				float comparedDebt = (float)atof(token);

				while (selectedClient != NULL)
				{
					if (selectedClient->debt < comparedDebt)
					{
						count++;
						if (count == 1)
							printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
						printClient(selectedClient);
						selectedClient = selectedClient->next;
					}
					else selectedClient = selectedClient->next;
				}
				if (count == 0) printf("\nNo client was found\n");
			}
		}
		else printf("\nThe operator that entered is invalid for this parameter, please try again!");
	}
	else if (strstr(param, "date") != NULL) {

		date* temp = (date*)malloc(sizeof(date));

		if (strstr(param, "!=") > NULL)
		{
			char* token = strtok(param, "=");
			token = strtok(NULL, "\n");			

			if (!validDate(&token))
			{
				printf("\nInvalid date, please try again.\n");
				
			}
			else {

				token = strtok(token, "/");
				temp->day = atoi(token);

				token = strtok(NULL, "/");
				temp->month = atoi(token);

				token = strtok(NULL, "\n");
				temp->year = atoi(token);

				while (selectedClient != NULL)
				{
					if (checkIfItsNew(&selectedClient->dateOfDebt, temp) != -1)
					{
						count++;
						if (count == 1)
							printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
						printClient(selectedClient);
						selectedClient = selectedClient->next;
					}
					else selectedClient = selectedClient->next;
				}
				if (count == 0) printf("\nNo client was found\n");
			}
		}
		else if (strstr(param, "=") > NULL) {

			char* token = strtok(param, "=");
			token = strtok(NULL, "\n");

			//token = removeSpacesFromStr(&token);
			if (!validDate(&token))
			{
				printf("\nInvalid date, please try again.\n");
				
			}
			else {

				token = strtok(token, "/");
				temp->day = atoi(token);

				token = strtok(NULL, "/");
				temp->month = atoi(token);

				token = strtok(NULL, "\n");
				temp->year = atoi(token);

				while (selectedClient != NULL)
				{
					if (checkIfItsNew(&selectedClient->dateOfDebt, temp) == -1)
					{
						count++;
						if (count == 1)
							printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
						printClient(selectedClient);
						selectedClient = selectedClient->next;
					}
					else selectedClient = selectedClient->next;
				}
				if (count == 0) printf("\nNo client was found\n");
			}
		}
		else if (strstr(param, ">") > NULL) {

			char* token = strtok(param, ">");
			token = strtok(NULL, "\n");

			//token = removeSpacesFromStr(&token);
			if (!validDate(&token))
			{
				printf("\nInvalid date, please try again.\n");
			}
			else {

				token = strtok(token, "/");
				temp->day = atoi(token);

				token = strtok(NULL, "/");
				temp->month = atoi(token);

				token = strtok(NULL, "\n");
				temp->year = atoi(token);

				float comparedDebt = (float)atof(token);

				while (selectedClient != NULL)
				{
					if (checkIfItsNew(temp, & selectedClient->dateOfDebt) == 1)
					{
						count++;
						if (count == 1)
							printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
						printClient(selectedClient);
						selectedClient = selectedClient->next;
					}
					else selectedClient = selectedClient->next;
				}
				if (count == 0) printf("\nNo client was found\n");
			}
		}
		else if (strstr(param, "<") > NULL) {

			char* token = strtok(param, "<");
			token = strtok(NULL, "\n");

			//token = removeSpacesFromStr(&token);
			if (!validDate(&token))
			{
				printf("\nInvalid date, please try again.\n");
			}
			else {

				token = strtok(token, "/");
				temp->day = atoi(token);

				token = strtok(NULL, "/");
				temp->month = atoi(token);

				token = strtok(NULL, "\n");
				temp->year = atoi(token);

				float comparedDebt = (float)atof(token);

				while (selectedClient != NULL)
				{
					if (checkIfItsNew(temp, &selectedClient->dateOfDebt) == 0)
					{
						count++;
						if (count == 1)
							printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
						printClient(selectedClient);
						selectedClient = selectedClient->next;
					}
					else selectedClient = selectedClient->next;
				}
				if (count == 0) printf("\nNo client was found\n");
			}
		}
		else printf("\nThe operator that entered is invalid for this parameter, please try again!");
	}
	else printf("\nThere is'nt parameter like that, please try again!");
}

/*Function to get a query from user, and execute the proper action*/
int getQuery(FILE* fp, struct list* clientsList) {

	char* query;
	do
	{
		printf("\n-->");
		query = readInput(stdin);

	} while (*query == '\n' || !(*query));
	char* token = strtok(query, " ");

	if (!strcmp(token, "set")) {

		addToFile(query + 4, fp, clientsList);
		free(query);
		return 1;
	}
	else if (!strcmp(token, "select"))
	{
		selectQuery(clientsList, query + 7);
		free(query);
		return 1;
	}
	else if (!strcmp(token, "print"))
	{
		printList(clientsList);
		free(query);
		return 1;
	}
	else if (!strcmp(token, "quit"))
	{
		printf("BYE BYE!!\n");
		free(query);
		return 0;
	}
	else
	{
		printf("Invalid query. Please try again\n");
		free(query);
		return 1;
	}
}

/*Function to read a csv file in and create a list of clients
the fubctin checks on any data if its valid and if not lighting the proper error on the errors array of the client.*/
void readFile(FILE* fp, struct list* listOfDebts) {

	char ch;        // Uses to check if we past the EOF symbol.

	while ((ch = getc(fp)) != EOF) {
		char* line;

		fseek(fp, -1, SEEK_CUR);
		line = readInput(fp);

		struct client* newClient = createClient();
		char* token;

		token = strtok(line, ",\n");       // Extracting first name
		if (!validName(&token))
			newClient->errors[0] = 1;

		newClient->firstName = _strdup(token);

		token = strtok(NULL, ",\n");

		if (!validName(&token))            // Extracting last name
			newClient->errors[1] = 1;

		newClient->lastName = _strdup(token);

		token = strtok(NULL, ",\n");       // Extracting ID   
		newClient->ID = _strdup(token);

		if (!validID(&token))
			newClient->errors[2] = 1;

		token = strtok(NULL, ",\n");        // Extracting phone number 
		newClient->phone = _strdup(token);

		if (!validPhone(&token))
			newClient->errors[3] = 1;

		token = strtok(NULL, ",\n");

		if (validNumber(&token)) {
			newClient->debt = (float)atof(token);
		}
		else {
			newClient->errors[4] = 0;
			newClient->debt = 1;
		}

		token = strtok(NULL, ",\n");

		if (validDate(&token))               // Extracting date of record
		{
			token = strtok(token, ",/\n");
			newClient->dateOfDebt.day = atoi(token);

			token = strtok(NULL, ",/\n");
			newClient->dateOfDebt.month = atoi(token);

			token = strtok(NULL, ",/\n");
			newClient->dateOfDebt.year = atoi(token);
			if ((newClient->dateOfDebt.year >= 1) && (newClient->dateOfDebt.month >= 1 && newClient->dateOfDebt.month <= 12) && (newClient->dateOfDebt.day >= 1 && newClient->dateOfDebt.day <= 31))
			{
				newClient->errors[5] = 0;
			}
			else newClient->errors[5] = 1;
		}
		else {
			newClient->errors[5] = 1;
		}

		free(line);

		struct client* temp = checkForExistingID(listOfDebts, newClient->ID);
		if (temp != NULL) {
			if (strcmp(temp->firstName, newClient->firstName)) {
				newClient->errors[6] = 1;

				if (strcmp(temp->lastName, newClient->lastName)) {
					newClient->errors[7] = 1;
				}
				addToSortedList(listOfDebts, newClient);
			}
			else{
				addToExistingClient(listOfDebts, temp, newClient);
				addToSortedList(listOfDebts, temp);
				freeClient(newClient);
			}
		}
		else{ 
			addToSortedList(listOfDebts, newClient);
		}
		
	}
	
}

FILE* openFile(char** nameOfFile) {

	FILE* fp;
	
	while ((fp = fopen(*nameOfFile, "r+t")) == NULL) {
		printf("Faild to open the file with this name: %s\n", *nameOfFile);
		free(*nameOfFile);
		printf("Please enter a new name:");
		*nameOfFile = readInput(stdin);
	}	
	return fp;
}

void printToFile(FILE* fp, struct client* record) {

	fprintf(fp, "%s,", record->firstName);
	fprintf(fp, "%s,", record->lastName);
	fprintf(fp, "%s,", record->ID);
	fprintf(fp, "%s,", record->phone);
	fprintf(fp, "%f,", record->debt);
	fprintf(fp, "%d/%d/%d\n", record->dateOfDebt.day, record->dateOfDebt.month, record->dateOfDebt.year);
}