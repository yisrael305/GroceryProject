#include "PrintFunc.h"

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

/*Function to print all list, valid clients first*/
void printList(struct list* listOfclient) {

	printf("\t\tlist of debts\n\n");
	printf("First Name\tLast Name\tID\t\tPhone\t    Debt  \tDate\n\n");

	struct client* temp = listOfclient->head;

	while (temp != NULL)                          // Runing over the list using temp.
	{
		int validClient = 1;                              // Uses to determine if temp is valid client before printing him.
		for (int i = 0; i < 8; i++) // Checking if there is an error on the client.
		{
			if (!CHECK_BIT(temp->errors, i))
			{
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

			if (!CHECK_BIT(temp->errors, i))
			{
				printf("\n");
				erorrList(i);
				while (temp != NULL) {

					if (!CHECK_BIT(temp->errors, i))
					{
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

void printToFile(FILE* fp, struct client* record)
{
	fprintf(fp, "%s,", record->firstName);
	fprintf(fp, "%s,", record->lastName);
	fprintf(fp, "%s,", record->ID);
	fprintf(fp, "%s,", record->phone);
	fprintf(fp, "%f,", record->debt);
	fprintf(fp, "%d/%d/%d\n", record->dateOfDebt.day, record->dateOfDebt.month, record->dateOfDebt.year);
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
