#include "BaseNIntegerList.h"

BaseNIntegerList CreateIntegerList(unsigned char base)
{
	BaseNIntegerList l;
	l.head = NULL;
	l.tail = NULL;
	l.base = base;
	l.size = 0;
	return l;
}

BOOL IsEmpty(BaseNIntegerList l)
{
	return (l.size == 0);
}

BaseNIntegerList InsertHead(BaseNIntegerList l, char* v)
{
	ListElem* newel = (ListElem*)malloc(sizeof(ListElem));
	newel->value = v;
	newel->next = l.head;
	newel->previous = NULL;

	if (!IsEmpty(l))
	{
		l.head->previous = newel;
	}
	else
	{
		l.tail = newel;
	}
	l.head = newel;
	++(l.size);

	return l;
}

BaseNIntegerList InsertTail(BaseNIntegerList l, char* v)
{
	ListElem* newel = (ListElem*)malloc(sizeof(ListElem));
	newel->value = v;
	newel->next = NULL;
	newel->previous = l.tail;

	if (!IsEmpty(l))
	{
		l.tail->next = newel;
	}
	else
	{
		l.head = newel;
	}
	l.tail = newel;
	++(l.size);

	return l;
}

BaseNIntegerList RemoveHead(BaseNIntegerList l)
{
	if(!IsEmpty(l))
	{
		if(l.size == 1)
		{
			free(l.head);
			l.head = l.tail = NULL;
			l.size = 0;
		}
		else
		{
			l.head = l.head->next;
			free(l.head->previous);
			l.head->previous = NULL;
			--(l.size);
		}
	}
	return l;
}

BaseNIntegerList RemoveTail(BaseNIntegerList l)
{
	if(!IsEmpty(l))
	{		
		if(l.size == 1)
		{			
			free(l.head);
			l.head = l.tail = NULL;
			l.size = 0;
		}
		else
		{			
			l.tail = l.tail->previous;
			free(l.tail->next);
			l.tail->next = NULL;
			--(l.size);
		}
	}
	return l;
}

void DeleteIntegerList(BaseNIntegerList l)
{
	while(!IsEmpty(l))
	{
		RemoveHead(l);
	}
}

unsigned char GetValue(unsigned char c) // make this inline
{
	return (c - (c > '9') * ('A' - '9') - '0');
}

unsigned int BaseToInt(char* v, unsigned char base)
{
	unsigned int n = 0; // value of v
	unsigned int temp;
	unsigned int size = 0;
	unsigned int k = 0;
	int i = 0;

	size = strlen(v);
	i = size - 1; // now i is the index of the last element of v

	while(i >= 0) // from the before last element of v to the first
	{
		temp = 1;

		for(k = 0; k < (size - i - 1); ++k)
			temp *= base;
		// temp = base^(size - i - 1)

		n += GetValue(v[i]) * temp;

		--i;
	}

	return n;
}

char* IntToBase(unsigned int v, unsigned char base)
{
	unsigned int size = 0;
	unsigned int k = 0;
	char ctemp;
	int i = 0;
	char base_digits[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

	char* w = NULL;
	k = 0;
	while(v > 0)
	{
		++k;
		w = realloc(w, k * sizeof(char));
		w[k-1] = base_digits[v%base];
		v /= base;
	}

	++k;
	w = realloc(w, k * sizeof(char));
	w[k-1] = '\0';

	size = k - 1; // now size is the size of w
	k = size / 2;
	for(i = 0; i < k; ++i) // invert w (strongest weight at right -> strongest weight at left)
	{
		ctemp = w[i];
		w[i] = w[size - i - 1];
		w[size - i - 1] = ctemp;
	}

	return w;
}

/*char* ConvertBaseToBinary(char* v, unsigned char base) // old version
{
	unsigned int n; // value of v
	unsigned int temp;
	unsigned int size = 0;
	unsigned int k = 0;
	char ctemp;
	int i = 0;
	char binary_digits[2] = {'0', '1'};

	// compute n, value of v
	size = strlen(v);
	i = size - 1; // now i is the index of the last element of v

	while(i >= 0) // from the before last element of v to the first
	{
		temp = 1;

		for(k = 0; k < (size - i - 1); ++k)
			temp *= base;
		// temp = base^(size - i - 1)

		n += GetValue(v[i]) * temp;

		--i;
	}

	// compute w, binary value of n *
	char* w = NULL;	// = (char*)malloc(sizeof(char));
	k = 0;
	while(n > 0)
	{
		++k;
		w = realloc(w, k * sizeof(char));
		w[k-1] = binary_digits[n%2];
		n /= 2;
	}

	++k;
	w = realloc(w, k * sizeof(char));
	w[k-1] = '\0';

	size = k - 1; // now size is the size of w
	k = size / 2;
	for(i = 0; i < k; ++i) // invert w (strongest weight at right -> strongest weight at left)
	{
		ctemp = w[i];
		w[i] = w[size - i - 1];
		w[size - i - 1] = ctemp;
	}

	return w;
}*/

char* ConvertBaseToBase(char* v, unsigned char old_base, unsigned char new_base)
{
	return (IntToBase(BaseToInt(v,old_base),new_base));
}

char* ConvertBaseToBinary(char* v, unsigned char base)
{
	return ConvertBaseToBase(v,base,2);
}

char* ConvertBinaryToBase(char* v, unsigned char base)
{
	return ConvertBaseToBase(v,2,base);
}

char* SumIntegerList(BaseNIntegerList l)
{
	ListElem* element = l.head;
	unsigned int s = 0;
	while(element != NULL)
	{
		s += BaseToInt(element->value,l.base);
		element = element->next;
	}
	return IntToBase(s,l.base);
}