#pragma once                                                             // Israel Weiss 
#ifndef projectGroceryHead
#define projectGroceryHead

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define CHUNK 20
#define LISTNAME "list.csv"
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

typedef struct
{
	unsigned int day : 5;   
	unsigned int month : 4;
	unsigned int year : 12;
}date;

struct client
{
	char* firstName;
	char* lastName;
	char* ID;
	char* phone;
	float debt;
	date dateOfDebt;
	char errors;            // Array of 1 and 0 that symbolizes the validation of each field in the client in the order. the last index symbolizes error id and name not matching. 
	struct client* next;
};

struct list 
{
	struct client* head;
	struct client* tail;
	float maxDebt;
	struct list* next;
};

int myFloatCompare(char* a, void* b);
int myStrCompare(char* a, void* b);
int dateCompare(char* token, void* selected);
#endif

//  select last name = gilo
//  select  first name < Pri
//	select   first name != Moshe
//	select debt<-200.5
//	select debt>-200.5
//	select date > 11/10/2020
//	select date = 11/10/2020
//	select date != 11/10/2020
//	select first name = Mo
//	select first name = Mo3
//	select date > 11/10/202e
//
//	set first name = Mri el, last name = gilo, id = 147369852, phone=, date = 11/9/2022, debt = -300
//	set first name = Mri el, last name = gilo, id = 14769852, phone = 0548754256, date = 11/9/2022, debt = -300
//	set first name = Mri el, last name = gilo, id = 1473693852, phone = 0548754256, date = 11/9/2022, debt = -300
//	set first name = Mri el, last name = gilo@, id = 147369852, phone = 0548754256, date = 11/9/2022, debt = -300
//	set first name = Mri el, last name = gilo, id = 147369852, phone = 0548754256, date = 11/9\2022, debt = -300
//	set first name = Mri el, last name = gilo, id = 147369852, phone = 0548754256, date = 11/9/2022, debt = -30e0
//	set first name = Mri el, last name = gilo, id = 147369852, phone = 0548754256, date = 11/9/2022, debt = -300.52
//	set first name = MrI El, last name = gilo, id = 147369852, phone = 0541111111, date = 11/9/2022, debt = -300