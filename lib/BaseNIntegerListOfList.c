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
	list_of_list.list[bucket_number] = InsertHead(list_of_list.list[bucket_number], v);
	return list_of_list;
}

BaseNIntegerListOfList BuildBucketList(BaseNIntegerList list, unsigned int digit_pos)
{
	BaseNIntegerListOfList list_of_list = CreateBucketList(list.base);

	if(!IsEmpty(list))
	{
		ListElem* list_element = list.head;
		if(strlen(list_element->value) < digit_pos)
			list_of_list = AddIntegerIntoBucket(list_of_list, list_element->value, GetValue((unsigned char)(list_element->value[digit_pos])));
		else
			list_of_list = AddIntegerIntoBucket(list_of_list, list_element->value, 0);

		while(list_element->next != NULL)
		{
			
			list_element = list_element->next;
			if(strlen(list_element->value) < digit_pos)
				list_of_list = AddIntegerIntoBucket(list_of_list, list_element->value, GetValue((unsigned char)(list_element->value[digit_pos])));
			else
				list_of_list = AddIntegerIntoBucket(list_of_list, list_element->value, 0);
		}
	}
	return list_of_list;
}

BaseNIntegerList BuildIntegerList(BaseNIntegerListOfList l)
{
	BaseNIntegerList output = CreateIntegerList( l.base ); /* Will be returned */
	unsigned short size;

	unsigned char i, j;
	for (i = 0; i < l.base; ++i) {

		ListElem* inserted_elem = l.list[i].head;

		while (inserted_elem != NULL) {

			size = (unsigned short)strlen(inserted_elem->value);
			char* number = (char*) malloc((unsigned)(size + 1)*sizeof(char));
			for (j = 0; j < size; ++j)
				number[j] = inserted_elem->value[j];
			output = InsertTail(output, number);
			inserted_elem = inserted_elem->next;
		}
	}

	return output;
}

void DeleteBucketList(BaseNIntegerListOfList list_of_list)
{
	unsigned char i;
	for (i = 0; i < list_of_list.base; ++i)
		DeleteIntegerList(list_of_list.list[i]);
	free (list_of_list.list);
}

BaseNIntegerList RadixSort(BaseNIntegerList list)
{
	BaseNIntegerList output;
	return output;
}
