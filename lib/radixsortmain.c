#include "BaseNIntegerList.h"
#include "BaseNIntegerListOfList.h"
#include "io.h"
#include <stdio.h>

typedef struct{
	unsigned char size;
	BaseNIntegerList* lists;
}ArrayOfList;

void listsMenu(ArrayOfList list_array);
void conversionsMenu(void);
void listOfListsMenu(ArrayOfList list_array);
void extraMenu(ArrayOfList list_array);

int main(int argc, char *argv[])
{
	ArrayOfList list_array;
	list_array.size = 0;
	list_array.lists = NULL;
	unsigned char user_choice = 0;

	do {
		Clear();
		SetTextAttributes("+bold");
		user_choice = Menu("- Input a list\0- Lists related functions\0- Conversion functions\0- List of lists related functions\0- Extra functions\0- Exit\0", 6, "white", "blue", user_choice);
		SetTextAttributes("reset");

		switch (user_choice) {
		case 0:
			++list_array.size;
			list_array.lists = (BaseNIntegerList*) realloc(list_array.lists, list_array.size*sizeof(BaseNIntegerList));
			list_array.lists[list_array.size - 1] = GetList();
			printf("List save as list %d\n", list_array.size - 1);
			break;
		case 1:
			listsMenu(list_array);			
			break;
		case 2:
			conversionsMenu();
			break;
		case 3:
			listOfListsMenu(list_array);
			break;
		case 4:
			extraMenu(list_array);
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
	
	Clear();
}

void conversionsMenu()
{

	Clear();
}

void listOfListsMenu(ArrayOfList list_array)
{

	Clear();
}

void extraMenu(ArrayOfList list_array)
{
	
	Clear();
}
