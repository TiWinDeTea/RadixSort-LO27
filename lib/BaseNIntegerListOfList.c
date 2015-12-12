#include "BaseNIntegerList.h"

BaseNIntegerListOfList CreateBucketList(unsigned int N)
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

BaseNIntegerListOfList AddIntegerIntoBucket(BaseNIntegerListOfList list_of_list, char* v, unsigned int bucket_number)
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
		if(strlen(v) < digit_pos)
			list_of_list = AddIntegerIntoBucket(list_of_list, list_element.value, GetValue(list_element.value[digit_pos]));
		else
			list_of_list = AddIntegerIntoBucket(list_of_list, list_element.value, 0);

		while(list_element.next != NULL)
		{
			
			list_element = list_element.next;
			if(strlen(v) < digit_pos)
				list_of_list = AddIntegerIntoBucket(list_of_list, list_element.value, GetValue(list_element.value[digit_pos]));
			else
				list_of_list = AddIntegerIntoBucket(list_of_list, list_element.value, 0);
		}
		return list_of_list;
	}
}

BaseNIntegerList BuildIntegerList(BaseNIntegerListOfList l)
{

}