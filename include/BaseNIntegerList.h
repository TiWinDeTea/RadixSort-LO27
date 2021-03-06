/***********************************************************************************************
 * C Library implementing BaseNIntegerList data type, with a doubly linked list representation *
 * Written by Maxime PINARD, maxime.pinard@utbm.fr, November 2015                              *
 ***********************************************************************************************/

/* 
 * Values(char*) are stored in reversed order (strongest weight at right)
 * 
 * This lib can be used for bases from 2 to 36 but be aware that some function description specify:
 * "/!\ Max value: 2 147 483 647"
 * It is the case if the function need to stock the number value or a part of the value in a unsigned int variable.
 * For bigger numbers don't use base-conversion functions, or modify the lib to use double or long double variable type.
 */

#ifndef BASENINTERGERLIST_H_INCLUDED
#define BASENINTERGERLIST_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <bool.h>

typedef struct elem{
	char* value;
	struct elem* next;
	struct elem* previous;
}ListElem;

typedef struct{
	ListElem* head;
	ListElem* tail;
	unsigned char base;
	unsigned short size;
}BaseNIntegerList;

/**
 * @brief Create an empty list
 * 
 * @param base: The base of the new list
 * @return The new list
 */
BaseNIntegerList CreateIntegerList(unsigned char base);

/**
 * @brief Check if a list is empty
 * 
 * @param l: The list to be checked
 * @return TRUE if the list is empty, FALSE else
 */
BOOL IsEmpty(BaseNIntegerList l);

/**
 * @brief Insert a new first element at the begening of the list
 * 
 * @param l: List to insert the new element
 * @param v: Value of the new element
 * @return The new list
 */
BaseNIntegerList InsertHead(BaseNIntegerList l, char* v);

/**
 * @brief Insert a new last element at the end of the list
 * 
 * @param l: List to insert the new element
 * @param v: Value of the new element
 * @return The new list
 */
BaseNIntegerList InsertTail(BaseNIntegerList l, char* v);

/**
 * @brief Remove the first element of the list and it values
 * @details If the list is empty do nothing
 * 
 * @param l: List to delete the first element
 * @return The new list
 */
BaseNIntegerList RemoveHead(BaseNIntegerList l);

/**
 * @brief Remove the last element of the list and it values
 * @details If the list is empty do nothing
 * 
 * @param l: List to delete the last element
 * @return The new list
 */
BaseNIntegerList RemoveTail(BaseNIntegerList l);

/**
 * @brief Delete the list
 * @details Delete all elements and values of the list
 * 
 * @param l: The list to delete
 */
void DeleteIntegerList(BaseNIntegerList* l);

/**
 * @brief Give the value of a character in base 36, can be used for smaller bases
 * @details ['0'...'9'] -> [0...9]
 *          ['A'...'Z'] -> [10...35], case sensitive
 *          [0...47] -> assign negative value to unsigned char  /!\
 *          [other char] -> [wrong values], not use in the lib
 * 
 * @param c: Character to convert 
 * @return Value of the character in base 36
 */
unsigned char GetValue(unsigned char c);

/**
 * @brief Compute the value of the number in the given base
 * @details There is no verification that v is in the given base in the function,
 * /!\ Max value: 2 147 483 647
 * 
 * @param v: Number to convert
 * @param base: Base of v
 * @return Value of v
 */
unsigned int BaseToInt(char* v, unsigned char base);

/**
 * @brief Convert the value in the given base
 * 
 * @param v: Value to convert
 * @param base: Base to convert
 * @return The value in the given base
 */
char* IntToBase(unsigned int v, unsigned char base);

/**
 * @brief Convert the number from a base to an other
 * @details /!\ Max value: 2 147 483 647
 * 
 * @param v: Number to convert
 * @param old_base: The base of v
 * @param new_base: The base to convert v
 * @return The number in the new base
 */
char* ConvertBaseToBase(char* v, unsigned char old_base, unsigned char new_base);

/**
 * @brief Convert the number from the given base to binary base
 * @details /!\ Max value: 2 147 483 647
 * 
 * @param v: Number to convert
 * @param base: Base of v
 * @return The number in the binary base
 */
char* ConvertBaseToBinary(char* v, unsigned char base);

/**
 * @brief Convert the number from binary base to the given base
 * @details /!\ Max value: 2 147 483 647
 * 
 * @param v: Number to convert
 * @param base: Base to convert
 * @return The number in the new base
 */
char* ConvertBinaryToBase(char* v, unsigned char base);

/**
 * @brief Summation of 2 numbers in binary base
 * 
 * @param a: First number
 * @param b: Second number
 * @return Sum of a and b in binary base
 */
char* SumBinary(char* a, char* b); /* infinitesimally faster than use SumBase with base = 2... ok this is useless */

/**
 * @brief Summation of 2 numbers in the given base
 * 
 * @param a: First number
 * @param b: Second number
 * @param base: Base of a and b
 * @return Sum of a and b in the given base
 */
char* SumBase(char* a, char* b, unsigned char base);

/**
 * @brief Compute the summation of all values in a list
 * 
 * @param l: The list to sum values
 * @return The sum in the base of the list
 */
char* SumIntegerList(BaseNIntegerList l);

/**
 * @brief Convert the list from its base to the given base
 * @details Convert all values of the list and change the base field of the list,
 * /!\ Max value: 2 147 483 647
 * 
 * @param l: The list to convert
 * @param base: Base to convert the list
 * @return The new list un the given base
 */
BaseNIntegerList ConvertListBase(BaseNIntegerList l, unsigned char base);

#endif /* BASENINTERGERLIST_H_INCLUDED */
