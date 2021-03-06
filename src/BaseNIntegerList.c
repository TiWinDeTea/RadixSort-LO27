#include <BaseNIntegerList.h>

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
			free(l.head->value);
			free(l.head);
			l.head = NULL;
			l.tail = NULL;
			l.size = 0;
		}
		else
		{
			l.head = l.head->next;
			free(l.head->previous->value);
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
			free(l.head->value);
			free(l.head);
			l.head = l.tail = NULL;
			l.size = 0;
		}
		else
		{
			l.tail = l.tail->previous;
			free(l.tail->next->value);
			free(l.tail->next);
			l.tail->next = NULL;
			--(l.size);
		}
	}
	return l;
}

void DeleteIntegerList(BaseNIntegerList* l)
{
	while(!IsEmpty(*l))
	{
		*l = RemoveHead(*l);
	}
}

unsigned char GetValue(unsigned char c) /* make this inline */
{
	return (c - (c > '9') * ('A' - '9' - 1) - '0');
}

unsigned int BaseToInt(char* v, unsigned char base)
{
	unsigned int n = 0; /* value of v */
	unsigned int temp = 1;
	unsigned int size = strlen(v);
	unsigned int i = 1;

	if(size > 0)
	{
		/* temp = base^0 */
		n = GetValue(v[0]);

		for (; i < size ; ++i) {
			/* temp = base^i */
			temp *= base;
			n += GetValue(v[i])*temp;
		}
	}

	return n;
}

char* IntToBase(unsigned int v, unsigned char base)
{
	unsigned int k = 2; /* size of the number in the new base: at least '0' and '\0' */
	unsigned int i = base;
	char base_digits[36] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

	char* w = NULL;

	while(v >= i){

		++k;
		i *= base; /* i = base^(k-1) */
	}

	w = (char*)malloc(k * sizeof(char));
	w[0] = '0'; /* for v = 0 */
	w[k-1] = '\0';

	k = 0;
	while(v > 0)
	{
		w[k] = base_digits[v%base];
		++k;
		v /= base;
	}

	return w;
}

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

char* SumBinary(char* a, char* b)
{
	char* s = NULL; /* the sum */
	unsigned int i = 0; /* iteration variable for a */
	unsigned int a_len = strlen(a);
	unsigned int j = 0; /* iteration variable for b */
	unsigned int b_len = strlen(b);
	unsigned int k = 0; /* iteration variable for s */
	unsigned int sum_len;
	unsigned char remainder = 0;
	char binary_digits[2] = {'0', '1'};

	/* sum_len = Max(strlen(a), strlen(b)) + 1 (for '\0') */
	if(i > j)
		sum_len = strlen(a) + 1;
	else
		sum_len = strlen(b) + 1;

	s = (char*)calloc(sum_len, sizeof(char));

	/* sum each digit of a and b from left to right */
	while(i < a_len && j < b_len)
	{
		remainder += (a[i] == '1') + (b[j] == '1');
		s[k] = binary_digits[remainder % 2];
		remainder /= 2;
		++k;
		++i;
		++j;
	}

	/* if j reached the end of b */
	while(i < a_len)
	{
		remainder += (a[i] == '1');
		s[k] = binary_digits[remainder % 2];
		remainder /= 2;
		++k;
		++i;
	}

	/* if i reached the end of a */
	while(j < b_len)
	{
		remainder += (b[j] == '1');
		s[k] = binary_digits[remainder % 2];
		remainder /= 2;
		++k;
		++j;
	}

	/* if there is a reminder at the end of the sum */
	if(remainder != 0) /* remainder == 1 */
	{
		s = realloc(s, (sum_len + 1) * sizeof(char));
		s[k] = '1';
		++k;
	}

	/* Add '\0' at the end of s */
	s[k] = '\0';

	return s;
}

char* SumBase(char* a, char* b, unsigned char base)
{
	char* s = NULL; /* the sum */
	unsigned int i = 0; /* iteration variable for a */
	unsigned int a_len = (unsigned int)(strlen(a));
	unsigned int j = 0; /* iteration variable for b */
	unsigned int b_len = (unsigned int)(strlen(b));
	unsigned int k = 0; /* iteration variable for s */
	unsigned int sum_len;
	unsigned char remainder = 0;
	char base_digits[36] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

	/* sum_len = Max(strlen(a), strlen(b)) + 1 (for '\0') */
	if(a_len > b_len)
		sum_len = (unsigned int)(a_len + 1);
	else
		sum_len = (unsigned int)(b_len + 1);

	s = (char*)calloc(sum_len, sizeof(char));

	/* sum each digit of a and b from left to right */
	while(i < a_len && j < b_len)
	{
		remainder += GetValue(a[i]) + GetValue(b[j]);
		s[k] = base_digits[remainder % base];
		remainder /= base;
		++k;
		++i;
		++j;
	}

	/* if j reached the end of b */
	while(i < a_len)
	{
		remainder += GetValue(a[i]);
		s[k] = base_digits[remainder % base];
		remainder /= base;
		++k;
		++i;
	}

	/* if i reached the end of a */
	while(j < b_len)
	{
		remainder += GetValue(b[j]);
		s[k] = base_digits[remainder % base];
		remainder /= base;
		++k;
		++j;
	}

	/* if there is a reminder at the end of the sum */
	if(remainder != 0)
	{
		s = realloc(s, (sum_len + 1) * sizeof(char));
		s[k] = base_digits[remainder];
		++k;
	}

	/* Add '\0' at the end of s */
	s[k] = '\0';

	return s;
}

char* SumIntegerList(BaseNIntegerList l)
{
	if(!IsEmpty(l))
	{
		ListElem* element = l.head;
		char* s;
		if (l.size == 1) {
			s = (char*) malloc((strlen(element->value)+1)*sizeof(char));
			s = strcpy(s, element->value);
		}
		else {
			char* tmp = NULL;
			s = element->value;
			element = element->next;
			do
			{
				s = SumBase(s, element->value, l.base);
				free(tmp);
				tmp = s;
				element = element->next;
			}while(element != NULL);
		}
		return s;
	}
	return NULL;
}

BaseNIntegerList ConvertListBase(BaseNIntegerList l, unsigned char base)
{
	if(!IsEmpty(l))
	{
		ListElem* element = l.head;
		char* tmp;

		while(element != NULL)
		{
			tmp = element->value;
			element->value = ConvertBaseToBase(element->value, l.base, base);
			free(tmp);
			element = element->next;
		}
	}
	l.base = base;

	return l;
}
