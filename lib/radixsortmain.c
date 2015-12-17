#include "BaseNIntegerList.h"
#include "BaseNIntegerListOfList.h"
#include "io.h"
#include <stdio.h>

typedef struct{
	unsigned char size;
	BaseNIntegerList* lists;
}ArrayOfList;

typedef struct{
	unsigned char size;
	BaseNIntegerListOfList* buckets;
}ArrayOfBuckets;

int main(void);
ArrayOfList listsMenu(ArrayOfList list_array);
void conversionsMenu(void);
ArrayOfBuckets listOfListsMenu(ArrayOfBuckets bucket_array, ArrayOfList* list_array);
ArrayOfList extraMenu(ArrayOfList list_array);
ArrayOfList ifListArrayEmptyAskInput(ArrayOfList list_array);
ArrayOfBuckets ifBucketArrayEmptyAskInput(ArrayOfBuckets bucket_array);
ArrayOfBuckets addBucket(ArrayOfBuckets bucket_array);
ArrayOfList addList(ArrayOfList list_array);
unsigned char selector(unsigned char arraySize, const char* type);
void waitForUser(void);

void TrollMenu(void);

int main()
{
	unsigned char user_choice = 0;
	ArrayOfList list_array;
	ArrayOfBuckets bucket_array;

	list_array.size = bucket_array.size = 0;
	list_array.lists = NULL;
	bucket_array.buckets = NULL;

	do {
		Clear();
		SetTextAttributes("+bold");
		user_choice = Menu("- Input a list\0- Lists related functions\0- Conversion functions\0- List of lists related functions(!!)\0- Extra functions\0- How are you gentlemen ?\0Exit\0", 7, "yellow", "blue", user_choice);
		SetTextAttributes("reset");

		switch (user_choice) {
		case 0:
			list_array = addList(list_array);
			break;
		case 1:
			list_array = listsMenu(list_array);
			break;
		case 2:
			conversionsMenu();
			break;
		case 3:
			bucket_array = listOfListsMenu(bucket_array, &list_array);
			break;
		case 4:
			list_array = extraMenu(list_array);
			break;
		case 5:
			TrollMenu();
			break;
		default:
			break;
		}
	}while (user_choice != 6);

	Clear();
	return EXIT_SUCCESS;
}

ArrayOfList listsMenu(ArrayOfList list_array)
{
	unsigned char user_choice = 0;
	do {
		Clear();
		SetTextAttributes("+bold");
		user_choice = Menu("- IsEmpty\0- InsertHead\0- InsertTail\0- RemoveHead\0- RemoveTail\0- DeleteIntegerList\0- SumIntegerList\0- PrintList\0Back\0", 9, "yellow", "blue", user_choice);
		SetTextAttributes("reset");
		Clear();
		if (user_choice != 8)
			list_array = ifListArrayEmptyAskInput(list_array);

		switch (user_choice) {
		case 0:
			if (list_array.size != 0) {
				unsigned char selected_list;
				selected_list = selector(list_array.size, "list");

				if (IsEmpty(list_array.lists[selected_list])) {
					printf("List%u is empty.\n", selected_list);
				}
				else {
					printf("List%u isn't empty.\n", selected_list);
				}
				waitForUser();
			}
			break;

		case 1:
		case 2:
			if (list_array.size != 0) {
				char* val;
				unsigned char selected_list;
				selected_list = selector(list_array.size, "list");

				printf("Enter the value you want to add below : (base %d)\n", list_array.lists[selected_list].base);
				do {
					val = GetNumber(list_array.lists[selected_list].base, TRUE);
					if (val==NULL) {
						CursorVerticalMove(-1);
						printf("\r   \r");
					}
				}while (val == NULL);

				Reverse(val, (unsigned int)strlen(val));

				if (!IsEmpty(list_array.lists[selected_list]))
				{
					size_t val_size = strlen(val);
					size_t list_vals_size = strlen(list_array.lists[selected_list].head->value);
					size_t i;

					if (val_size <= list_vals_size) {
						val = realloc(val, list_vals_size*sizeof(char));
						for (i = val_size ; i < list_vals_size ; ++i) {
							val[i] = '0';
						}
						val[list_vals_size] = '\0';

					}
					else {
						ListElem* elem = list_array.lists[selected_list].head;
						while(elem != NULL) {
							elem->value = realloc(elem->value, val_size*sizeof(char));
							for (i = list_vals_size ; i < val_size ; ++i) {
								elem->value[i] = '0';
							}
							elem->value[val_size] = '\0';
							elem = elem->next;
						}
					}
				}
				if (val != NULL) {
					if (user_choice == 1)
						list_array.lists[selected_list] = InsertHead(list_array.lists[selected_list], val);
					else
						list_array.lists[selected_list] = InsertTail(list_array.lists[selected_list], val);
					printf("Value added to list%u\n", list_array.size - 1);
				}
				else {
					printf("Nothing to be done...\n");
				}
				waitForUser();
			}
			break;
		case 3:
		case 4:
			if (list_array.size != 0){
				unsigned char selected_list;
				selected_list = selector(list_array.size, "list");
				if (user_choice == 3)
					list_array.lists[selected_list] = RemoveHead(list_array.lists[selected_list]);
				else
					list_array.lists[selected_list] = RemoveTail(list_array.lists[selected_list]);
				printf("Done\n");
				waitForUser();
			}
			break;
		case 5:
			if (list_array.size != 0) {
				unsigned char selected_list;
				selected_list = selector(list_array.size, "list");
				DeleteIntegerList(&list_array.lists[selected_list]);
				printf("Done.\nList%u will remain as an empty list.\n", selected_list);
				waitForUser();
			}
			break;
		case 6:
			if (list_array.size != 0) {
				unsigned char selected_list;
				char* s;
				selected_list = selector(list_array.size, "list");
				s = SumIntegerList(list_array.lists[selected_list]);
				if (s == NULL) {
					printf("Well, this list seems to be empty...\n");
				}
				else {
					Reverse(s, (unsigned int)strlen(s));
					printf("All what's in list%u makes %s (result given in base %u)\n", selected_list, s, list_array.lists[selected_list].base);
					free (s);
				}
				waitForUser();
			}
			break;
		case 7:
			if (list_array.size != 0) {
				unsigned char selected_list;
				selected_list = selector(list_array.size, "list");
				PrintList(list_array.lists[selected_list]);
			}
			break;
		default:
			break;
		}
	}while (user_choice != 8);
	return list_array;
}

void conversionsMenu()
{
	unsigned char user_choice = 0;
	do {
		char* user_input = NULL;
		char* conv_result;
		Clear();
		SetTextAttributes("+bold");
		user_choice = Menu("- ConvertBaseToBinary\0- ConvertBinaryToBase\0Back\0", 3, "yellow", "blue", user_choice);
		SetTextAttributes("reset");
		Clear();

		switch (user_choice) {
		case 0:
			printf("Input base ? [2~36]\n");
			user_choice = (unsigned char)GetNumberWithinRange(2, 36);

			printf("Number to convert ? (max 2 147 483 647)\n");
			do{
				printf("                                                             \r");
				free(user_input);
				user_input = GetNumber(user_choice, FALSE);
			}while (!isWithinRange(user_input, 0, 2147483647, user_choice));

			Reverse(user_input, (unsigned int)strlen(user_input));
			conv_result = ConvertBaseToBinary(user_input, user_choice);
			Reverse(user_input, (unsigned int)strlen(user_input));
			Reverse(conv_result, (unsigned int)strlen(conv_result));
			printf("%s in base %u is %s in binary\n", user_input, user_choice, conv_result );
			free(conv_result);
			free(user_input);

			user_choice = 0;
			waitForUser();
			break;

		case 1:
			printf("Output base ? [2~36]\n");
			user_choice = (unsigned char)GetNumberWithinRange(2, 36);

			printf("Number to convert ? (max 2 147 483 647)\n");
			do{
				printf("\r                                                           \r");
				free(user_input);
				user_input = GetNumber(2, FALSE);
			}while (!isWithinRange(user_input, 0, 2147483647, 2));

			Reverse(user_input, (unsigned int)strlen(user_input));
			conv_result = ConvertBinaryToBase(user_input, user_choice);
			Reverse(user_input, (unsigned int)strlen(user_input));
			Reverse(conv_result, (unsigned int)strlen(conv_result));
			printf("%s in binary is %s in base %u\n", user_input, conv_result, user_choice);
			free(conv_result);
			free(user_input);

			user_choice = 1;
			waitForUser();
			break;
		default:
			break;
		}
	}while (user_choice != 2);
}

ArrayOfBuckets listOfListsMenu(ArrayOfBuckets bucket_array, ArrayOfList* list_array)
{
	unsigned char user_choice = 0;
	unsigned char selection;
	unsigned char digit;
	do {
		Clear();
		SetTextAttributes("+bold");
		user_choice = Menu("- CreateBucketList\0- BuildBucketList\0- BuildIntegerList\0- AddIntegerToBucket (!!)\0- DeleteBucketList (!!)\0- RadixSort (!!)\0- PrintBucket\0Back", 8, "yellow", "blue", user_choice);
		SetTextAttributes("reset");
		Clear();

		switch (user_choice) {
		case 0:
			bucket_array = addBucket(bucket_array);
			break;
		case 1:
			*list_array = ifListArrayEmptyAskInput(*list_array);

			if (list_array->size != 0) {
				selection = selector(list_array->size, "list");

				printf("Which digit do you want to take into consideration for building the bucket (rightmost ; the rightess digit is digit 1) ? [1~255]\n");
				digit = (unsigned char)GetNumberWithinRange(1, 255);
				bucket_array.size++;
				bucket_array.buckets = (BaseNIntegerListOfList*) realloc(bucket_array.buckets, bucket_array.size*sizeof(BaseNIntegerListOfList));
				bucket_array.buckets[bucket_array.size-1] = BuildBucketList(list_array->lists[selection], (unsigned)(digit - 1));
				printf("Bucket saved as ");
				SetTextAttributes("+bold");
				printf("bucket%d\n", bucket_array.size - 1);
				SetTextAttributes("reset");
				waitForUser();
			}
			break;
		case 2:
			bucket_array = ifBucketArrayEmptyAskInput(bucket_array);
			selection = selector(bucket_array.size, "bucket");

			list_array->size++;
			list_array->lists = (BaseNIntegerList*) realloc(list_array->lists, list_array->size*sizeof(BaseNIntegerList));
			list_array->lists[list_array->size-1] = BuildIntegerList(bucket_array.buckets[selection]);
			printf("List generated as ");
			SetTextAttributes("+bold");
			printf("list%d\n", list_array->size - 1);
			SetTextAttributes("reset");
			waitForUser();

			if (yes("Do you want to print the list ?", 1)) {
				PrintList(list_array->lists[list_array->size-1]);
			}
			break;
		case 3:
			SetTextAttributes("+bold");
			SetTextColor("red");
			SetTextAttributes("+underline");
			printf("Not Yet Implemented\n");
			SetTextAttributes("reset");
			waitForUser();
			/* TODO Addintegerlisttobucket */
			break;
		case 4:
			SetTextAttributes("+bold");
			SetTextColor("red");
			SetTextAttributes("+underline");
			printf("Not Yet Implemented\n");
			SetTextAttributes("reset");
			waitForUser();
			/* TODO Deletebucketlist */
			break;
		case 5:
			SetTextAttributes("+bold");
			SetTextColor("red");
			SetTextAttributes("+underline");
			printf("Not Yet Implemented\n");
			SetTextAttributes("reset");
			waitForUser();
			/* TODO RadixSort */
			break;
		case 6:
			bucket_array = ifBucketArrayEmptyAskInput(bucket_array);

			if (bucket_array.size != 0) {
				unsigned char i = 0;
				selection = selector(bucket_array.size, "bucket");

				for (; i < bucket_array.buckets[selection].base ; ++i) {
					Clear();
					printf("Printing the list related to the digit %c\n", i > 9 ? i + 'A' - 10 : i + '0');
					waitForUser();
					PrintList(bucket_array.buckets[selection].list[i]);
				}
			}
			break;
		default:
			break;
		}
	}while (user_choice != 7);
	return bucket_array;
}

ArrayOfList extraMenu(ArrayOfList list_array)
{
	unsigned char user_choice = 0;

	char* input = NULL;
	char* output= NULL;
	unsigned char input_base;
	unsigned char output_base;
	do {
		Clear();
		SetTextAttributes("+bold");
		user_choice = Menu("- ConvertBaseToBase()\0- ConvertListBase()\0Back\0", 3, "yellow", "blue", user_choice);
		SetTextAttributes("reset");
		Clear();

		switch (user_choice) {
		case 0:
			printf("Input base ? [2~36]\n");
			input_base = (unsigned char)GetNumberWithinRange(2,36);

			printf("Output base ? [2~36]\n");
			output_base = (unsigned char)GetNumberWithinRange(2,36);

			printf("Number to convert ? [0~2 147 483 647]\n");
			do{
				input = GetNumber(input_base, FALSE);
				if (input == NULL) {
					CursorVerticalMove(-1);
				}
				else {
					if (!isWithinRange(input, 0, 2147483647, input_base)) {
						printf("\r                                 \r");
						free(input);
						input = NULL;
					}
				}
			}while (input == NULL);

			Reverse(input, (unsigned int)strlen(input));
			output = ConvertBaseToBase(input, input_base, output_base);
			Reverse(output, (unsigned int)strlen(output));
			Reverse(input, (unsigned int)strlen(input));
			printf("%s in base %u is %s in base %u\n", input, input_base, output, output_base);

			free(input);
			free(output);

			waitForUser();
			break;
		case 1:
			printf("Note that this function won't work if any number is above 2 147 483 647 (base 10)\n");
			list_array = ifListArrayEmptyAskInput(list_array);
			if (list_array.size != 0) {
				unsigned char selected_list;
				unsigned char base;
				selected_list = selector(list_array.size, "type");
				printf("Output base ? [2~36]\n");
				base = (unsigned char)GetNumberWithinRange(2, 36);
				list_array.lists[selected_list] = ConvertListBase(list_array.lists[selected_list], base);
				waitForUser();
			}
			break;
		default:
			break;
		}
	}while (user_choice != 2);
	return list_array;
}

ArrayOfBuckets addBucket(ArrayOfBuckets bucket_array)
{
	unsigned char ui;
	printf("Bucket base ? [2~36]\n");
	ui = (unsigned char)GetNumberWithinRange(2, 36);
	++bucket_array.size;
	bucket_array.buckets = (BaseNIntegerListOfList*) realloc(bucket_array.buckets, bucket_array.size * sizeof(BaseNIntegerListOfList));
	bucket_array.buckets[bucket_array.size - 1] = CreateBucketList(ui);
	printf("Bucket saved as ");
	SetTextAttributes("+bold");
	printf("bucket%d\n", bucket_array.size - 1);
	SetTextAttributes("reset");
	waitForUser();
	return bucket_array;
}

ArrayOfList addList(ArrayOfList list_array)
{
	++list_array.size;
	list_array.lists = (BaseNIntegerList*) realloc(list_array.lists, list_array.size*sizeof(BaseNIntegerList));
	list_array.lists[list_array.size - 1] = GetList();
	printf("List saved as ");
	SetTextAttributes("+bold");
	printf("list%d\n", list_array.size - 1);
	SetTextAttributes("reset");
	waitForUser();
	return list_array;
}

ArrayOfList ifListArrayEmptyAskInput(ArrayOfList list_array)
{
	if (list_array.size == 0 && yes("You don't have any list !\nDo you want to input one ?", 1)) {
		list_array = addList(list_array);
	}
	return list_array;
}

unsigned char selector(unsigned char arraySize, const char* type)
{
	unsigned char selection;
	if (arraySize == 1) {
		printf("Using %s0 [this is the only one you have]\n", type);
		selection = 0;
		waitForUser();
	}
	else {
		printf("Which list do you want to use ? [%s0 to %s%u]\n", type, type, arraySize - 1);
		selection = (unsigned char)GetNumberWithinRange(0, (unsigned)arraySize - 1);
		printf("\n");
	}
	return selection;
}

void waitForUser()
{
	printf("(press any key)");
	SetEcho(FALSE);
	(void)InstantGetChar();
	SetEcho(TRUE);
	printf("\r               \r");
}

ArrayOfBuckets ifBucketArrayEmptyAskInput(ArrayOfBuckets bucket_array)
{
	if (bucket_array.size == 0 && yes("You don't have any bucket !\nDo you want to create one ?", 1)) {
		bucket_array = addBucket(bucket_array);
	}
	return bucket_array;
}

void TrollMenu()
{
	unsigned char trolling = 0;
	do
	{
		Clear();
		SetTextAttributes("+bold");
		trolling = Menu("ALL YOUR BASE ARE BELONG TO US !\0!!\0", 2, "light red", "light green", trolling);
		SetTextAttributes("reset");
		Clear();

		if (!trolling) {
			printf("YOU HAVE NO CHANCE TO SURVIVE TAKE YOUR TIME\n");
			InstantGetChar();
		} else {
			do{
				printf("HA HA HA");
				InstantGetChar();
				Clear();
				SetTextAttributes("+bold");
				Menu(" T-T\0", 1, "ligt cyan", "light yellow",0);
				SetTextAttributes("reset");
				Clear();
			}while (TRUE);
		}

	}while (trolling != 10);
}
