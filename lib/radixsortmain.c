#include "BaseNIntegerList.h"
#include "BaseNIntegerListOfList.h"
#include "io.h"
#include <stdio.h>

typedef struct{
	unsigned char size;
	BaseNIntegerList* lists;
}ArrayOfList;

int main(void);
void listsMenu(ArrayOfList list_array);
void conversionsMenu(void);
void listOfListsMenu(/*ArrayOfList list_array*/void);
void extraMenu(/*ArrayOfList list_array*/void);
ArrayOfList IAIEAFI(ArrayOfList list_array);
ArrayOfList addList(ArrayOfList list_array);
unsigned char listSelector(unsigned char arraySize);
void waitForUser(void);

int main()
{
	unsigned char user_choice = 0;
	ArrayOfList list_array;

	list_array.size = 0;
	list_array.lists = NULL;

	do {
		Clear();
		SetTextAttributes("+bold");
		user_choice = Menu("- Input a list\0- Lists related functions\0- Conversion functions\0- List of lists related functions\0- Extra functions\0Exit\0", 6, "white", "blue", user_choice);
		SetTextAttributes("reset");

		switch (user_choice) {
		case 0:
			list_array = addList(list_array);
			break;
		case 1:
			listsMenu(list_array);
			break;
		case 2:
			conversionsMenu();
			break;
		case 3:
			listOfListsMenu(/*list_array*/);
			break;
		case 4:
			extraMenu(/*list_array*/);
			break;
		default:
			break;
		}
	}while (user_choice != 5);

	Clear();
	return EXIT_SUCCESS;
}

void listsMenu(ArrayOfList list_array)
{
	unsigned char user_choice = 0;
	do {
		Clear();
		SetTextAttributes("+bold");
		user_choice = Menu("- IsEmpty()\0- InsertHead()\0- InsertTail()\0- RemoveHead()\0- RemoveTail()\0- DeleteIntegerList()\0- SumIntegerList()\0- PrintList()\0Back\0", 9, "white", "blue", user_choice);
		SetTextAttributes("reset");
		Clear();
		if (user_choice != 8)
			list_array = IAIEAFI(list_array);

		switch (user_choice) {
		case 0:
			if (list_array.size != 0) {
				unsigned char selected_list;
				selected_list = listSelector(list_array.size);

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
				selected_list = listSelector(list_array.size);

				printf("Enter the value you want to add below : (base %d)\n", list_array.lists[selected_list].base);
				val = GetNumber(list_array.lists[selected_list].base, FALSE);
				
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
				selected_list = listSelector(list_array.size);
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
				selected_list = listSelector(list_array.size);
				DeleteIntegerList(list_array.lists[selected_list]);
				printf("Done.\nList%u will remain as an empty list.\n", selected_list);
				waitForUser();
			}
			break;
		case 6:
			if (list_array.size != 0) {
				unsigned char selected_list;
				char* s;
				selected_list = listSelector(list_array.size);
				s = SumIntegerList(list_array.lists[selected_list]);
				Reverse(s, (unsigned int)strlen(s));
				printf("All what's in list%u makes %s (result given in base %u)\n", selected_list, s, list_array.lists[selected_list].base);
				free (s);
				waitForUser();
			}
			break;
		case 7:
			if (list_array.size != 0) {
				unsigned char selected_list;
				selected_list = listSelector(list_array.size);
				PrintList(list_array.lists[selected_list]);
			}
			break;
		default:
			break;
		}
	}while (user_choice != 8);
}

void conversionsMenu()
{
	unsigned char user_choice = 0;
	do {
		char* user_input = NULL;
		char* conv_result;
		Clear();
		SetTextAttributes("+bold");
		user_choice = Menu("- ConvertBaseToBinary()\0- ConvertBinaryToBase()\0Back\0", 3, "white", "blue", user_choice);
		SetTextAttributes("reset");
		Clear();

		switch (user_choice) {
		case 0:
			printf("Input base ? [2~35]\n");
			do {
				user_input = GetNumber(10, FALSE);
				if (isWithinRange(user_input, 2, 35, 10)) {
					user_choice = (unsigned char)strtol(user_input, NULL, 10);
				}
				free(user_input);
			}while (user_choice == 0);

			user_input = NULL;

			printf("Number to convert ? (max 2 147 483 647)\n");
			do{
				printf("\r                                                           \r");
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
			printf("Output base ? [2~35]\n");
			do {
				user_input = GetNumber(10, FALSE);
				if (isWithinRange(user_input, 2, 35, 10)) {
					user_choice = (unsigned char)strtol(user_input, NULL, 10);
				}
				free(user_input);
			}while (user_choice == 0);
			
			user_input = NULL;

			printf("Number to convert ? (max 2 147 483 647)\n");
			do{
				printf("\r                                                            \r");
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

			user_choice = 0;
			waitForUser();
			break;
		default:
			break;
		}
	}while (user_choice != 2);
}

void listOfListsMenu(/*ArrayOfList list_array*/)
{
	unsigned char user_choice = 0;
	do {
		Clear();
		SetTextAttributes("+bold");
		user_choice = Menu("- CreateBucketList()\0- BuildBucketList()\0- BuildIntegerList()\0- AddIntegerToBucket()\0- DeleteBucketList()\0- RadixSort()\0PrintList()\0Back", 8, "white", "blue", user_choice);
		SetTextAttributes("reset");
		Clear();

		switch (user_choice) {
		case 0:
			SetTextAttributes("+bold");
			SetTextColor("red");
			SetTextAttributes("+underline");
			printf("Not Yet Implemented\n");
			SetTextAttributes("reset");
			waitForUser();
			/* TODO Createbucketlist */
			break;
		case 1:
			SetTextAttributes("+bold");
			SetTextColor("red");
			SetTextAttributes("+underline");
			printf("Not Yet Implemented\n");
			SetTextAttributes("reset");
			waitForUser();
			/* TODO Buildbucketlist */
			break;
		case 2:
			SetTextAttributes("+bold");
			SetTextColor("red");
			SetTextAttributes("+underline");
			printf("Not Yet Implemented\n");
			SetTextAttributes("reset");
			waitForUser();
			/* TODO Buildintegerlist */
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
			SetTextAttributes("+bold");
			SetTextColor("red");
			SetTextAttributes("+underline");
			printf("Not Yet Implemented\n");
			SetTextAttributes("reset");
			waitForUser();
			/* TODO PrintList */
			break;
		default:
			break;
		}
	}while (user_choice != 7);
}

void extraMenu(/*ArrayOfList list_array*/)
{
	unsigned char user_choice = 0;
	do {
		Clear();
		SetTextAttributes("+bold");
		user_choice = Menu("- ConvertBaseToBase()\0- ConvertListBase()\0- Sumbase()\0Back\0", 4, "white", "blue", user_choice);
		SetTextAttributes("reset");
		Clear();

		switch (user_choice) {
		case 0:
			SetTextAttributes("+bold");
			SetTextColor("red");
			SetTextAttributes("+underline");
			printf("Not Yet Implemented\n");
			SetTextAttributes("reset");
			waitForUser();
			/* TODO ConvertBaseToBase */
			break;
		case 1:
			SetTextAttributes("+bold");
			SetTextColor("red");
			SetTextAttributes("+underline");
			printf("Not Yet Implemented\n");
			SetTextAttributes("reset");
			waitForUser();
			/* TODO ConvertListBase */
			break;
		case 2:
			SetTextAttributes("+bold");
			SetTextColor("red");
			SetTextAttributes("+underline");
			printf("Not Yet Implemented\n");
			SetTextAttributes("reset");
			waitForUser();
			/* TODO SumBase */
			break;
		default:
			break;
		}
	}while (user_choice != 3);
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

ArrayOfList IAIEAFI(ArrayOfList list_array)
{
	if (list_array.size == 0) {
		char ui;
		printf("You don't have any list !\nDo you want to input one ? [Y/n]");
		ui = InstantGetChar();
		if (ui != 'n' && ui != 'N') {
			list_array = addList(list_array);
		}
	}	
	return list_array;
}

unsigned char listSelector(unsigned char arraySize)
{
	char* user_in;
	unsigned char selected_list;
	if (arraySize == 1) {
		printf("Using list0 [this is the only one you have]\n");
		selected_list = 0;
		waitForUser();
	}
	else {
		printf("Which list do you want to use ? [list0 to list%u]\n", arraySize - 1);
		do {
			user_in = GetNumber(10, FALSE);
			if (isWithinRange(user_in, 0, (unsigned char)(arraySize - 1), 10)) {
				selected_list = (unsigned char)strtol(user_in, NULL, 10);
			}
			else {
				printf("\r                                          \r");
				free(user_in);
				user_in = NULL;
			}
		}while (user_in == NULL);
		printf("\n");
		free(user_in);
	}
	return selected_list;
}

void waitForUser()
{
	printf("(press any key)");
	SetEcho(FALSE);
	(void)InstantGetChar();
	SetEcho(TRUE);
	printf("\r               \r");
}
