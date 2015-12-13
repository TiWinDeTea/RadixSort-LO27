#include "BaseNIntegerList.h"
#include "BaseNIntegerListOfList.h"
#include "io.h"
#include <stdio.h>

typedef struct{
	unsigned char size;
	BaseNIntegerList* lists;
}ArrayOfList;

void listsMenu(/*ArrayOfList list_array*/void);
void conversionsMenu(void);
void listOfListsMenu(/*ArrayOfList list_array*/void);
void extraMenu(/*ArrayOfList list_array*/void);
int main(void);

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
			++list_array.size;
			list_array.lists = (BaseNIntegerList*) realloc(list_array.lists, list_array.size*sizeof(BaseNIntegerList));
			list_array.lists[list_array.size - 1] = GetList();
			printf("List saved as list %d\n", list_array.size - 1);
			break;
		case 1:
			listsMenu(/*list_array*/);
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

void listsMenu(/*ArrayOfList list_array*/)
{
	unsigned char user_choice = 0;
	do {
		Clear();
		SetTextAttributes("+bold");
		user_choice = Menu("- IsEmpty()\0- InsertHead()\0- InsertTail()\0- RemoveHead()\0- RemoveTail()\0- DeleteIntegerList()\0- SumIntegerList\0Back\0", 8, "white", "blue", user_choice);
		SetTextAttributes("reset");

		switch (user_choice) {
		case 0:
			/* TODO isempty */
			break;
		case 1:
			/* TODO inserthead */
			break;
		case 2:
			/* TODO inserttail */
			break;
		case 3:
			/* TODO rmhead */
			break;
		case 4:
			/* TODO rmtail */
			break;
		case 5:
			/* TODO deleteintegerlist */
			break;
		case 6:
			/* TODO sumintegerlist */
			break;
		default:
			break;
		}
	}while (user_choice != 7);
}

void conversionsMenu()
{
	unsigned char user_choice = 0;
	do {
		Clear();
		SetTextAttributes("+bold");
		user_choice = Menu("- ConvertBaseToBinary()\0- ConvertBinaryToBase()\0Back\0", 3, "white", "blue", user_choice);
		SetTextAttributes("reset");

		switch (user_choice) {
		case 0:
			/* TODO Convertbasetobinary */
			break;
		case 1:
			/* TODO Convertbinarytobase */
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
		user_choice = Menu("- CreateBucketList()\0- BuildBucketList()\0- BuildIntegerList()\0- AddIntegerToBucket()\0- DeleteBucketList()\0- RadixSort()\0Back", 7, "white", "blue", user_choice);
		SetTextAttributes("reset");

		switch (user_choice) {
		case 0:
			/* TODO Createbucketlist */
			break;
		case 1:
			/* TODO Buildbucketlist */
			break;
		case 2:
			/* TODO Buildintegerlist */
			break;
		case 3:
			/* TODO Addintegerlisttobucket */
			break;
		case 4:
			/* TODO Deletebucketlist */
			break;
		case 5:
			/* TODO RadixSort */
			break;
		default:
			break;
		}
	}while (user_choice != 6);
	
}

void extraMenu(/*ArrayOfList list_array*/)
{
	unsigned char user_choice = 0;
	do {
		Clear();
		SetTextAttributes("+bold");
		user_choice = Menu("- ConvertBaseToBase()\0- PrintList()\0- ConvertListBase()\0Back\0", 4, "white", "blue", user_choice);
		SetTextAttributes("reset");

		switch (user_choice) {
		case 0:
			/* TODO ConvertBaseToBase */
			break;
		case 1:
			/* TODO PrintList */
			break;
		case 2:
			/* TODO ConvertListBase */
			break;
		default:
			break;
		}
	}while (user_choice != 3);
	
}
















