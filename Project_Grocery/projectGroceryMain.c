#include "projectGroceryHead.h"              // Israel Weiss 

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	char* nameOfFile = (char*)malloc((1+strlen(LISTNAME))*sizeof(char));
	strcpy(nameOfFile,LISTNAME);
	strcat(nameOfFile, "\0");
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
