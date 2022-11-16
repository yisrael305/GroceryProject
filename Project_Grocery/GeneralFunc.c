#include "GeneralFunc.h"


FILE* openFile(char** nameOfFile) 
{
	FILE* fp;

	while ((fp = fopen(*nameOfFile, "r+t")) == NULL) {
		printf("Faild to open the file with this name: %s\n", *nameOfFile);
		free(*nameOfFile);
		printf("Please enter a new name:");
		*nameOfFile = readInput(stdin);
	}
	return fp;
}

void openFileError()
{
	printf("Can't open file\n");
}

/*Function to read any input, from the file or user, using the exact amount of memory that needed*/
char* readInput(FILE* fp)
{
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

/*Function to remove any spaces before and after str*/
char* removeSpacesFromStr(char** string) 
{
	char* ptr = *string;
	char* newStr = *string;
	int len = (int)strlen(*string); //A veriable uses to place a pointer in the end of sring.
	char* ch = *string + len - 1;   //Placing the pointer before '\0' or '\n'. 

	if (**string == ' ')
	{
		while (*ptr == ' ')
		{
			ptr++;
		}
		while (*ptr != '\0')
		{
			*newStr = *ptr;
			ptr++;
			newStr++;
		}
		*newStr = '\0';
	}

	while (*ch == ' ')
	{
		*ch = '\0';                 //Peplacing the value from ' ' to a '\0'.
		ch--;
	}
	return *string;
}


