#include "Validation.h"
#include "GeneralFunc.h"

/*Function to check that the names contains letters only*/
int validName(char** name)
{
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
int validID(char** ID)
{
	*ID = removeSpacesFromStr(ID);

	char* ch = *ID;
	int count = 0;

	while (*ch)
	{
		if (isdigit(*ch))
		{
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
int validPhone(char** phone)
{
	*phone = removeSpacesFromStr(phone);

	char* ch = *phone;
	int count = 0;

	while (*ch)
	{
		if (count == 0 && *ch != '0')
		{
			return 0;
		}
		if (isdigit(*ch))
		{
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
int validNumber(char** number)
{
	*number = removeSpacesFromStr(number);

	char* ch = *number;
	int i = 0;
	while (*ch)
	{
		if (i == 0)
		{
			if (*ch == '-' || isdigit(*ch)) {
				ch++;
				i++;
			}
			else return 0;
		}
		else if (isdigit(*ch) || *ch == '.')
		{
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

	while (*ch)
	{

		if (isdigit(*ch))
		{
			i++;
			ch++;
		}
		else if (i > 0 || i < 5)
		{
			if (*ch == '/')
			{
				ch++;
				i++;
			}
			else return 0;
		}
	}
	return 1;
}
