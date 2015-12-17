#include "BaseNIntegerListOfList.h"

BaseNIntegerListOfList CreateBucketList(unsigned char N)
{
	BaseNIntegerListOfList l;
	unsigned int i;

	l.base = N;
	l.list = (BaseNIntegerList*)calloc(N, sizeof(BaseNIntegerList));
	for(i = 0; i < N; ++i)
	{
		l.list[i] = CreateIntegerList(N);
	}
	return l;
}

BaseNIntegerListOfList AddIntegerIntoBucket(BaseNIntegerListOfList list_of_list, char* v, unsigned char bucket_number)
{
	list_of_list.list[bucket_number] = InsertTail(list_of_list.list[bucket_number], v);
	return list_of_list;
}

BaseNIntegerListOfList BuildBucketList(BaseNIntegerList list, unsigned int digit_pos)
{
	BaseNIntegerListOfList list_of_list = CreateBucketList(list.base);
	unsigned short size;
	char* number;
	unsigned int j;

	if(!IsEmpty(list))
	{
		ListElem* list_element = list.head;

		size = strlen(list_element->value);
		number = (char*)malloc((size + 1)*sizeof(char));
		for (j = 0; j <= size; ++j)
			number[j] = list_element->value[j];

		if(strlen(number) > digit_pos)
			list_of_list = AddIntegerIntoBucket(list_of_list, number, GetValue(number[digit_pos]));
		else
			list_of_list = AddIntegerIntoBucket(list_of_list, number, 0);

		while(list_element->next != NULL)
		{
			list_element = list_element->next;
			size = strlen(list_element->value);
			number = (char*) malloc((size + 1)*sizeof(char));
			for (j = 0; j <= size; ++j)
				number[j] = list_element->value[j];

			if(strlen(number) > digit_pos)
				list_of_list = AddIntegerIntoBucket(list_of_list, number, GetValue(number[digit_pos]));
			else
				list_of_list = AddIntegerIntoBucket(list_of_list, number, 0);
		}
	}

	return list_of_list;
}

BaseNIntegerList BuildIntegerList(BaseNIntegerListOfList list_of_list)
{
	BaseNIntegerList output = CreateIntegerList( list_of_list.base ); /* Will be returned */
	unsigned short size;
	unsigned char i, j;
	char* number;

	for (i = 0; i < list_of_list.base; ++i) {

		ListElem* inserted_elem = list_of_list.list[i].head;

		while (inserted_elem != NULL) {

			size = (unsigned short)strlen(inserted_elem->value);
			number = (char*) malloc((unsigned)(size + 1)*sizeof(char));
			for (j = 0; j <= size; ++j)
				number[j] = inserted_elem->value[j];
			output = InsertTail(output, number);
			inserted_elem = inserted_elem->next;
		}
	}

	return output;
}

void DeleteBucketList(BaseNIntegerListOfList* list_of_list)
{
	unsigned char i;
	for (i = 0; i < list_of_list->base; ++i)
		DeleteIntegerList(&(list_of_list->list[i]));
	free(list_of_list->list);
	list_of_list->list = NULL;
}

BaseNIntegerList RadixSort(BaseNIntegerList list)
{
	unsigned short max_size = strlen(list.head->value);
	unsigned short tmp_size;
	ListElem* elem = list.head;
	unsigned short i;
	BaseNIntegerListOfList list_of_list;
	BaseNIntegerList sorted_list;

	/*find the size of the biggest element of list*/
	while(elem->next != NULL)
	{
		elem = elem->next;
		tmp_size = strlen(elem->value);

		if(tmp_size > max_size)
			max_size = tmp_size;
	}

	/*build list_of_list from list by the first digit, and then sorted_list from list_of_list*/
	list_of_list = BuildBucketList(list,0);
	sorted_list = BuildIntegerList(list_of_list);
	DeleteBucketList(&list_of_list);

	/*build list_of_list from sorted_list by the i digit, and then sorted_list from list_of_list*/
	/*repeat until sorted_list is sorted*/
	for(i = 1; i < max_size; ++i)
	{
		list_of_list = BuildBucketList(sorted_list,i);
		DeleteIntegerList(&sorted_list);
		sorted_list = BuildIntegerList(list_of_list);
		DeleteBucketList(&list_of_list);
	}

	return sorted_list;
}
