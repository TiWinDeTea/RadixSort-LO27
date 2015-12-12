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

BaseNIntegerListOfList CreateBucketList(unsigned int N);
BaseNIntegerListOfList AddIntegerIntoBucket(BaseNIntegerListOfList list_of_list, char* v, unsigned int bucket_number);
BaseNIntegerListOfList BuildBucketList(BaseNIntegerList list, unsigned int digit_pos);
BaseNIntegerList BuildIntegerList(BaseNIntegerListOfList list_of_list);
void DeleteBucketList(BaseNIntegerListOfList list_of_list);
BaseNIntegerList RadixSort(BaseNIntegerList list);

#endif /*BASENINTERGERLISTOFLIST_H_INCLUDED*/
