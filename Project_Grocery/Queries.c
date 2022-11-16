#include "Queries.h"
#include "PrintFunc.h"
#include "GeneralFunc.h"
#include "Client.h"
#include "Validation.h"
#include "MatchClient.h"
#include "List.h"

/*Function to get a query from user, and execute the proper action*/
int getQuery(FILE* fp, struct list* clientsList) 
{
	char* query;
	do
	{
		printf("\n-->");
		query = readInput(stdin);
		if ((*query == '\0'))
		{
			free(query);
		}
		else
		{
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

	} while (!(*query));
}

/*Fnction to build a new client from input and add him to the list and file*/
void addToFile(char* input, FILE* fp, struct list* clientsList)
{
	char* line = input;
	char* ex;

	while (*line)
	{
		*line = tolower(*line);            // Replacig the upper case letters to make it easy to work with.
		line++;
	}
	line = _strdup(input);

	struct client* temp = createClient();  // Asiggin memory for the new client.

	char* token;                           // Uses to extract specific date from the line that scaned.  

	//Extract the first name.
	ex = strstr(line, "first name");
	if (!ex)
	{
		printf("looks like you forgot to type first name, enter first name:\n");
		temp->firstName = (readInput(stdin));
	}
	else
	{
		token = strtok(ex, ":=");
		token = strtok(NULL, ",");
		temp->firstName = _strdup(token);
	}

	while (!validName(&temp->firstName))
	{
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
	if (!ex) 
	{
		printf("looks like you forgot to type last name, enter last name:\n");
		temp->lastName = (readInput(stdin));
	}
	else 
	{
		token = strtok(ex, ":=");
		token = strtok(NULL, ",");
		temp->lastName = _strdup(token);
	}

	while (!validName(&temp->lastName)) 
	{
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
	if (!ex)
	{
		printf("looks like you forgot to type any ID, enter ID:\n");
		temp->ID = (readInput(stdin));
	}
	else 
	{
		token = strtok(ex, ":=");
		token = strtok(NULL, ",");
		temp->ID = _strdup(token);
	}

	while (!validID(&temp->ID)) 
	{
		free(temp->ID);
		printf("Invalid ID, please enter ID again\n");
		temp->ID = (readInput(stdin));
		if (!strcmp(temp->ID, "quit"))
		{
			free(temp->firstName);
			free(temp->lastName);
			free(temp->ID);
			free(temp);
			return;
		}
	}

	int matchIndex;
	while (matchIndex = matchNameAndID(temp, clientsList))  // The user must to enter matching detailes for excisting ID.  
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
			if (!strcmp(temp->lastName, "quit"))
			{
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
			free(temp->ID);
			printf("the firse and last name does not match an excisting ID, please enter ID again:\n");
			temp->ID = (readInput(stdin));
			if (!strcmp(temp->ID, "quit")) {
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
	if (!ex)
	{
		printf("looks like you forgot to type any phone, enter phone number:\n");
		temp->phone = (readInput(stdin));
	}
	else 
	{
		token = strtok(ex, ":=");
		token = strtok(NULL, ",");
		temp->phone = _strdup(token);
	}
	while (!validPhone(&temp->phone))
	{
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
	else
	{
		token = strtok(ex, ":=");
		token = strtok(NULL, ",");
		token = _strdup(token);
	}


	while (!validNumber(&token)) 
	{
		printf("Invalid debt, please enter debt again\n");
		free(token);
		token = (readInput(stdin));
		if (!strcmp(token, "quit"))
		{
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
	if (!ex) 
	{
		printf("looks like you forgot to type any date, please enter date:\n");
		token = (readInput(stdin));
	}
	else 
	{
		token = strtok(ex, ":=");
		token = strtok(NULL, ",");
	}

	int date = 0;        // Uses to store the parts of the date
	int flag = 1;        // Simbolize if there is a problem with date format  
	do
	{
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
void selectQuery(struct list* clientsList, char* input)
{
	struct client* selectedClient = clientsList->head; // Using to rum over the list and compare the data that has been asked.
	char* line = input;
	char* param[6] = { "first name","last name","id","phone","debt","date" };
	int(*validFunc[6])(char**) = { validName,validName,validID,validPhone,validNumber,validDate };
	int(*compFunc[6]) = { myStrCompare,myStrCompare ,myStrCompare ,myStrCompare, myFloatCompare ,dateCompare };
	char* oper[4] = { "<",">","!=","=" };
	int i = 0, j = 0;

	while (*line) {
		*line = tolower(*line);
		line++;
	}

	char* token = line;

	while (i <= 6)
	{
		line = NULL;
		if ((line = strstr(input, param[i])) != NULL)
		{
			char* op = NULL;

			while (j < 4)
			{
				if ((op = strstr(line, oper[j])) != NULL)
				{
					char saveOp = *op;
					token = strtok(line, oper[j]);
					token = strtok(NULL, "\n");
					if (j == 2)
						token++;
					token = removeSpacesFromStr(&token);

					if (!validFunc[i](&token)) {
						printf("\nInvalid %s, please try again\n", param[i]);
						break;
					}
					int count = 0;

					while (selectedClient != NULL)
					{
						void* select[6] = { selectedClient->firstName,selectedClient->lastName,selectedClient->ID,selectedClient->phone,&selectedClient->debt ,&selectedClient->dateOfDebt };
						int x = (paramCompare(token, select[i], compFunc[i]));

						if (x == 0 && saveOp == '=') {
							count++;
							if (count == 1)
								printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
							printClient(selectedClient);
						}
						else if ((x > 0) && (saveOp == '<' || saveOp == '!')) {
							count++;
							if (count == 1)
								printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
							printClient(selectedClient);
						}
						else if (x < 0 && (saveOp == '>' || saveOp == '!')) {
							count++;
							if (count == 1)
								printf("\nFirst Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");
							printClient(selectedClient);
						}
						selectedClient = selectedClient->next;
					}
					if (count == 0) printf("\nNo client was found\n");
				}
				j++;
			}
			break;
		}
		i++;
	}
}

int paramCompare(char* token, void* select, int compare(char*, void*))
{
	return (compare(token, select));
}


