#include "projectGroceryHead.h"    // Israel Weiss
#include "List.h"
#include "PrintFunc.h"
#include "MatchClient.h" 
#include "GeneralFunc.h"
#include "Queries.h"
#include "Client.h"
int myFloatCompare(char* a, void* b)
{
	if (((atof(a)) - *(float*)b) > 0)
		return 1;
	if (((atof(a)) - *(float*)b) < 0)
		return -1;
	else
		return 0;
}

int myStrCompare(char* a, void* b)
{
	return strcmp(a, (char*)b);
}

int dateCompare(char* token, void* selected)
{
	char* part = _strdup(token);
	char* str = part;
	date tokenDate={0};
	part = strtok(part, "/\n");

	tokenDate.day = atoi(part);
	part = strtok(NULL, "/\n");
	tokenDate.month = atoi(part);
	part = strtok(NULL, "/\n");
	tokenDate.year = atoi(part);

	int itsNew = checkIfItsNew((date*)selected, &tokenDate);
	switch (itsNew)
	{
	case -1: {
		free(str);
		return 0;
		break;
	}
	case 1: {
		free(str);
		return 1;
		break;
	}
	case 0: {
		free(str);
		return -1;
		break;
	}
	default:
		free(str);
		break;
	}
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	char* nameOfFile = (char*)malloc((1+strlen(LISTNAME))*sizeof(char));
	strcpy(nameOfFile,LISTNAME);
	struct list* listOfDebts = createList(); // Assigned memory for the list.
	
	FILE* fp = openFile(&nameOfFile); // Open file. if the file does not exist the user will asked to enter a different name of the file
	
	readFile(fp, listOfDebts);
	
	printf("\n");
	printList(listOfDebts);
	printInstructions();

	int flag; // Uses to signel when the user wnts to end the program.

	while (flag = getQuery(fp, listOfDebts));  // Get queries from the user.
	
	fclose(fp);               // Saving file

	freeList(listOfDebts);    // free mempry.
	free(nameOfFile);
	
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	return 0;
}
