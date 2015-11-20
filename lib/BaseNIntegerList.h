#ifndef BOOL_DEFINED
#define BOOL_DEFINED
typedef enum{
	FALSE = 0,
	TRUE = 1
}BOOL;
#endif

#ifndef BASENINTERGERLIST_H_INCLUDED
#define BASENINTERGERLIST_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h> // temporary, for tests with getch()

typedef struct elem{
	char* value;
	struct elem* next;
	struct elem* previous;
}ListElem;

typedef struct{
	ListElem* head;
	ListElem* tail;
	unsigned char base;
	unsigned char size;
}BaseNIntegerList;

BaseNIntegerList CreateIntegerList(unsigned char base);
BOOL IsEmpty(BaseNIntegerList l);
BaseNIntegerList InsertHead(BaseNIntegerList l, char* v);
BaseNIntegerList InsertTail(BaseNIntegerList l, char* v);
BaseNIntegerList RemoveHead(BaseNIntegerList l);
BaseNIntegerList RemoveTail(BaseNIntegerList l);
void DeleteIntegerList(BaseNIntegerList l);

unsigned char GetValue(unsigned char c);
unsigned int BaseToInt(char* v, unsigned char base);
char* IntToBase(unsigned int v, unsigned char base);
char* ConvertBaseToBase(char* v, unsigned char old_base, unsigned char new_base);
char* ConvertBaseToBinary(char* v, unsigned char base);
char* ConvertBinaryToBase(char* v, unsigned char base);
char* SumBinary(char* a, char* b); // infinitesimally faster than use SumBase with base = 2... ok this is useless
char* SumBase(char* a, char* b, unsigned char base);
char* SumIntegerList(BaseNIntegerList l);

#endif