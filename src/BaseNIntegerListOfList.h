/*****************************************************************************************
 * C Library implementing BaseNIntegerListOfList data type and radix sort                *
 * Written by Lucas LAZARE  - lucas.lazare@utbm.fr                                       *
 *            Maxime PINARD - maxime.pinard@utbm.fr                                      *
 *            Dec 2015                                                                   *
 *****************************************************************************************/

#ifndef BOOL_DEFINED
#define BOOL_DEFINED

typedef enum{
	FALSE = 0,
	TRUE = 1
}BOOL;

#endif /*BOOL_DEFINED*/

#ifndef BASENINTERGERLISTOFLIST_H_INCLUDED
#define BASENINTERGERLISTOFLIST_H_INCLUDED

#include "BaseNIntegerList.h"

typedef struct{
	BaseNIntegerList* list;
	unsigned char base;
}BaseNIntegerListOfList;

/*
 * Creates a BaseNIntegerListOfList
 * @param N base of the list
 * @return  Returns the created list
 */
BaseNIntegerListOfList CreateBucketList(unsigned char N);

/*
 * Adds a new integer (inputted as char*) at the end a BaseNIntegerListOfList in the given bucket
 * @param list_of_list  BaseNIntegerListOfList where to add the number
 * @param v             Integer to add, given as a string
 * @param bucket_number Bucket where to insert the number, between 0 and the base of the list base (excluded)
 * @return              BaseNIntegerListOfList with the added integer
 */
BaseNIntegerListOfList AddIntegerIntoBucket(BaseNIntegerListOfList list_of_list, char* v, unsigned char bucket_number);

/*
 * Builds a new BaseNIntegerListOfList from a BaseNIntegerList, considering the specified digit (rightmost digit) to "bucketize" it
 * @param list      list to sort
 * @param digit_pos digit to take into consideration
 * @return          Returns the generated BaseNIntegerListOfList
 */
BaseNIntegerListOfList BuildBucketList(BaseNIntegerList list, unsigned int digit_pos);

/*
 * Builds a new BaseNIntegerList from a BaseNIntegerListOfList, respecting the ascending order on the buckets
 * @param list_of_list BaseNIntegerListOfList to build the list from
 * @return             Returns the generated BaseNIntegerList
 */
BaseNIntegerList BuildIntegerList(BaseNIntegerListOfList list_of_list);

/*
 * Clears and delete the specified BaseNIntegerListOfList
 * @param list_of_list BaseNIntegerListOfList to free
 */
void DeleteBucketList(BaseNIntegerListOfList* list_of_list);

/*
 * Sorts the specified BaseNIntegerList using LSD radixsort
 * @param list BaseNIntegerList to sort
 * @return     A sorted BaseNIntegerList
 */
BaseNIntegerList RadixSort(BaseNIntegerList list);

#endif /*BASENINTERGERLISTOFLIST_H_INCLUDED*/
