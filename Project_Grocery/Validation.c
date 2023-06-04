#include "Validation.h"
#include "GeneralFunc.h"

/*Function to check that the names contains letters only*/
int validName(void* name_)
{
	char** name = (char**)name_;
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
int validID(void* ID_)
{
	char** ID = (char**)ID_;
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
int validPhone(void* phone_)
{
	char** phone = (char**)phone_;
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
int validNumber(void* number_)
{
	char** number = (char**) number_;
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
int validDate(void* date_) {

	char** date = (char**)date_;
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

int validDateStruct(void* dateToCheck_)
{
	date* dateToCheck = (date*)dateToCheck_;
	if ((dateToCheck->year > 0) && (dateToCheck->month > 0
		&& dateToCheck->month <= 12) && (dateToCheck->day >= 1 && dateToCheck->day <= 31))
		return 1;
	return 0;
}
void isValidClient(struct client* clientToCheck)
{
	void* Client_param[] = { &clientToCheck->firstName, &clientToCheck->lastName, &clientToCheck->ID,
		&clientToCheck->phone, &clientToCheck->debt, &clientToCheck->dateOfDebt };
	int(*validFunc[6])(void*) = { validName,validName,validID,validPhone,validNumber,validDateStruct };
	int flag = 0;
	int i = 0;
	char retChar = '0';
	while (i < 6)
	{
		if (i == 4)
		{

			/*float* castDebtPtr = (float*)Client_param[i];
			float castDebt = *castDebtPtr;
			printf("%f\n", *((float*)Client_param[i]));
			char floatToStr[20];
			int numWritten = sprintf_s(floatToStr, sizeof(floatToStr), "%f", castDebt);*/
			/*char* date = NULL;
			retChar = strcat(date, clientToCheck->dateOfDebt.day + '/');
			retChar = strcat(date, clientToCheck->dateOfDebt.month + '/');
			retChar = strcat(date, clientToCheck->dateOfDebt.year);
			if (flag = validFunc[i]((char*)Client_param[i]))*/
			if (validFunc[i](Client_param[i]))
				clientToCheck->errors |= 1 << i;
		}
		else
		{
			(validFunc[i](Client_param[i]));
			clientToCheck->errors |= 1 << i;
		}
		i++;
	}
	clientToCheck->errors |= 1 << 6;
	clientToCheck->errors |= 1 << 7;
}

