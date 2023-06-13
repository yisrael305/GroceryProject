#include "Queries.h"
#include "PrintFunc.h"
#include "GeneralFunc.h"
#include "Client.h"
#include "Validation.h"
#include "MatchClient.h"
#include "List.h"

typedef enum {
	SET = 1,
	SELECT,
	PRINT,
	QUIT
}queris;

char* param[6] = { "first name","last name","id","phone","debt","date" };
int(*validFunc[6])(void*) = { validName,validName,validID,validPhone,validNumber,validDate };

int getQueryValue(char* token)
{
	token = removeSpacesFromStr(&token);
	if (!strcmp(token, "set"))
		return 1;
	else if (!strcmp(token, "select"))
		return 2;
	else if (!strcmp(token, "print"))
		return 3;
	else if (!strcmp(token, "quit"))
		return 4;
}

int getQuery(FILE* fp, struct list* clientsList) 
{
	char* query=NULL;
	do
	{
		printf("\n-->");
		query = readInput(stdin);
		//char* queryChange = _strdup(query);
		if ((*query == '\0'))
		{
			free(query);
			//free(queryChange);
		}
		else
		{
			char* token = strtok(query, " ");

			int queryValue = getQueryValue(token);

			switch (queryValue)
			{
			case SET:

				addToFile(query + 4, fp, clientsList);
				break;

			case SELECT:

				selectQuery(clientsList, query + 7);
				break;

			case PRINT:

				printList(clientsList);
				break;
			case QUIT:

				printf("BYE BYE!!\n");
				free(query);
				//free(queryChange);
				return 0;
				break;

			default:
				printf("Invalid query. Please try again\n");
				
				break;
			}
			
			/*if (!strcmp(token, "set")) {

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
			}*/
		}
		printf("%s\n", query);
		//printf("%s\n", queryChange);

		free(query);
		//free(queryChange);
		return 1;
	} while ((*query) != "\0");
}

void addDateToClient(date* dateOfClient, char* dateToAdd)
{
	char* token = strtok(dateToAdd, "/");
	dateOfClient->day = atoi(token);
	
	token = strtok(NULL, "/");	
	dateOfClient->month=atoi(token);

	token = strtok(NULL, "/");
	dateOfClient->year = atoi(token);
}

/*Fnction to build a new client from input and add him to the list and file*/
void addToFile(char* input, FILE* fp, struct list* clientsList)
{
	char* line = input;
	char* ex = NULL;
						      
	while (*line)
	{
		*line = tolower(*line);            // Replacig the upper case letters to make it easy to work with.
		line++;
	}
	line = _strdup(input);
	char* linePtr = line;
	struct client* temp = createClient();  // Asiggin memory for the new client.
	void* Client_param[] = { &temp->firstName, &temp->lastName, &temp->ID, &temp->phone, &temp->debt, &temp->dateOfDebt };

	char* token;                           // Uses to extract specific data from the line that scaned.  

	int checkParam = 0;
	char* paramPointer = NULL;
	int validParam = 0;
	int freeParam = 0;

	//Extract the first name.
	while (checkParam < 6)
	{
		paramPointer = strstr(line, param[checkParam]);

		if (checkParam == 0)
		{
			token = strtok(paramPointer, ":=");
			token = strtok(NULL, ",");
		}
		else
		{
			token = strtok(NULL, ":=");
			token = strtok(NULL, ",");
		}

		while (!(validParam = validFunc[checkParam](&token)))
		{
			if (token == "quit")
			{
				while (freeParam < checkParam)
				{
					free(Client_param[checkParam]);
					freeParam++;
				}
			}
				
			else {
				printf("The %s that you entered is not valid, Please try again", param[checkParam]);
				token = readInput(stdin);
			}
		}

		if (checkParam == 4)
			temp->debt = (float)atof(token);
		else if (checkParam == 5)
			addDateToClient(&temp->dateOfDebt, token);
		else memcpy(Client_param[checkParam], &token, sizeof(token));
		
		//line = _strdup(input);
		checkParam++;
	}

	free(linePtr);
	printToFile(fp, temp);

	struct client* search = checkForExistingID(clientsList, temp->ID);
	if (search != NULL)
	{
		if (matchNameAndID(temp, clientsList) == 0)
		{
			addToExistingClient(clientsList, search, temp);
			addToSortedList(clientsList, search);
			//freeClient(temp);
		}
		else addToSortedList(clientsList, temp);
	}
	printf("Record added succsesfuly\n");
	
}

/*Function to allow the user to print a specific data from the list
using the clients parameters and !=<> notations*/
void selectQuery(struct list* clientsList, char* input)
{
	struct client* selectedClient = clientsList->head; // Using to rum over the list and compare the data that has been asked.
	char* line = input;
	
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


