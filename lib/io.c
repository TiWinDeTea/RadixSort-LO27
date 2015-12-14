#include "io.h"


// pure output
void Clear()
{
	printf("\033[2J");	// ANSI escape for clearing the screen
	SetCursorPos( 0, 0);
}

void CPrint(char* text, unsigned short y_pos)
{
	unsigned short char_length = (unsigned short)strlen(text);
	unsigned short console_width = ConsoleWidth();

	if (char_length <= console_width)
	{
		SetCursorPos((unsigned short)((console_width-char_length)/2), y_pos); // sets the x cursor's coordinate at the center minus half of the char length.
		printf("%s", text);
	}
}

void PrintList(BaseNIntegerList l)
{
	if (IsEmpty(l))
	{
		printf("The list is empty.\nNothing to display.\n");
		(void)InstantGetChar();
		return;
	}

	SetEcho( FALSE );
	ListElem* elem = l.head; // Value to display
	unsigned short term_height = ConsoleHeight();
	unsigned short term_width = ConsoleWidth();
	unsigned short j = 0;	// Counter for the number of elements currently on the screen
	unsigned short val_size = (unsigned short)strlen(elem->value); // all values should have the same size
	unsigned short nb_displayed = 0; // Counter for the total amount of elements displayed
	char user_input = 0;
	BOOL digit_was_displayed; // Used to remove the left '0' (on display)

	if (term_width < (val_size + 2))
	{
		printf("This screen is too small to display this list properly.\n");
		printf("Press Enter if you still want to do it.");
		term_height/=3;
		if (InstantGetChar() != '\n')
			return;
	}

	Clear();

	// keeping space for percentage display
	--term_height;

	char percentage[40]; // Contains percentage and usable inputs (for display purposes)

	while (elem != NULL && user_input != 'q')
	{
		// if we have some space in the terminal to display yet another list
		if (j < term_height)
		{
			++j;
			++nb_displayed;
			digit_was_displayed = FALSE;

			// Align : right
			CursorHorizontalMove( (unsigned short)( term_width - 2 - val_size) );

			// Printing the value of the pointed element
			printf("[");
			for (unsigned short i = val_size; i-- ;)	// We are in Little Endian
			{
				// We don't want to display the 0 on the left, but we want to display 0 if the actual value is 0
				if (!digit_was_displayed && elem->value[i] == '0' && i != 0)
					printf(" ");
				else
				{
					printf("%c", elem->value[i]);
					digit_was_displayed = TRUE;
				}
			}
			printf("]\n");
			
			elem = elem->next;
		}
		else
		{
			// Percentage of element displayed
			SetTextAttributes("+invert");
			if (term_width >= 40)
				sprintf(percentage, "-- %d%% -- [inputs : ' ', '\\n', 's', 'q']\r", 100 * nb_displayed / l.size);
			else
				sprintf(percentage, "-- %d%% --\r", 100 * nb_displayed / l.size);
			CPrint(percentage, term_height);
			SetTextAttributes("-invert");

			user_input = InstantGetChar();

			switch (user_input)
			{
				case ' ':
					// Printing a whole screen or all what's left
					if (term_height >= (l.size - nb_displayed))
						j = (unsigned short)( term_height - l.size + nb_displayed );
					else
						j = 0;
					break;

				case '\n':
					// Printing only the next value
					--j;
					break;

				case 's':
					//Printing a whole screen minus one, so you are sure to read all or all what's left
					if (term_height > (l.size - nb_displayed))
						j = (unsigned short)( term_height - l.size + nb_displayed );
					else j=1;

					//Adding a marker for readability purposes
					if (term_width > (val_size + 5))
					{
						CursorVerticalMove( -1 );
						if (term_width > (25 + val_size))
						{
							// Align : right
							CursorHorizontalMove( (unsigned short)(term_width - 25 - val_size) );
							printf("Last line was here -->\r");
						}
						else
						{
							CursorHorizontalMove( (unsigned short)(term_width - 5 - val_size) );
							printf("-->\r");
						}
						CursorVerticalMove( 1 );
					}

					break;
				default:
					// Printing only the next value
					--j;
					break;
			}

			// Clearing last line (percentage)
			if (user_input != 'q')
			{
				for( unsigned short i=0; i<term_width; ++i)
					printf(" ");
				printf("\r");
			}

		}
	}
	if (user_input != 'q')
	{
		SetTextAttributes("+invert");
		CPrint("-- END --", term_height);
		SetTextAttributes("-invert");
		InstantGetChar();
	}
	printf("\n");
	SetEcho( TRUE );
}
void SetTextAttributes(const char* attribute)
{
	switch (attribute[0])
	{
		case '+':
			++attribute;
			if (!strcmp(attribute, "bold"))               printf("\033[1m");/**ifbreak**/
			else if (!strcmp(attribute, "dim"))           printf("\033[2m");/**ifbreak**/
			else if (!strcmp(attribute, "underline"))     printf("\033[4m");/**ifbreak**/
			else if (!strcmp(attribute, "blink"))         printf("\033[5m");/**ifbreak**/
			else if (!strcmp(attribute, "invert"))        printf("\033[7m");/**ifbreak**/
			else if (!strcmp(attribute, "strike"))        printf("\033[8m");/**ifbreak**/
			--attribute;
			break;
		case '-':
			++attribute;
			if (!strcmp(attribute, "bold"))               printf("\033[21m");/**ifbreak**/
			else if (!strcmp(attribute, "dim"))           printf("\033[22m");/**ifbreak**/
			else if (!strcmp(attribute, "underline"))     printf("\033[24m");/**ifbreak**/
			else if (!strcmp(attribute, "blink"))         printf("\033[25m");/**ifbreak**/
			else if (!strcmp(attribute, "invert"))        printf("\033[27m");/**ifbreak**/
			else if (!strcmp(attribute, "strike"))        printf("\033[29m");/**ifbreak**/
			--attribute;
			break;
		default:
			if (!strcmp(attribute, "reset"))               printf("\033[0m");/**ifbreak**/
			break;
	}
}
void SetBgColor(const char* color)
{
	if (!strcmp(color, "black"))                                  printf("\033[40m");/**break**/
	else if (!strcmp(color, "red"))                               printf("\033[41m");/**break**/
	else if (!strcmp(color, "green"))                             printf("\033[42m");/**break**/
	else if (!strcmp(color, "yellow"))                            printf("\033[43m");/**break**/
	else if (!strcmp(color, "blue"))                              printf("\033[44m");/**break**/
	else if (!strcmp(color, "magenta"))                           printf("\033[45m");/**break**/
	else if (!strcmp(color, "cyan"))                              printf("\033[46m");/**break**/
	else if (!strcmp(color, "light grey"))                        printf("\033[47m");/**break**/
	else if (!strcmp(color, "grey"))                              printf("\033[100m");/**break**/
	else if (!strcmp(color, "light red"))                         printf("\033[101m");/**break**/
	else if (!strcmp(color, "light green"))                       printf("\033[102m");/**break**/
	else if (!strcmp(color, "light yellow"))                      printf("\033[103m");/**break**/
	else if (!strcmp(color, "light blue"))                        printf("\033[104m");/**break**/
	else if (!strcmp(color, "light magenta"))                     printf("\033[105m");/**break**/
	else if (!strcmp(color, "light cyan"))                        printf("\033[106m");/**break**/
	else if (!strcmp(color, "white"))                             printf("\033[107m");/**break**/
}

void SetTextColor(const char* color)
{
	if (!strcmp(color, "black"))                                  printf("\033[8m");/**break**/
	else if (!strcmp(color, "grey"))                              printf("\033[30m");/**break**/
	else if (!strcmp(color, "red"))                               printf("\033[31m");/**break**/
	else if (!strcmp(color, "green"))                             printf("\033[32m");/**break**/
	else if (!strcmp(color, "yellow"))                            printf("\033[33m");/**break**/
	else if (!strcmp(color, "blue"))                              printf("\033[34m");/**break**/
	else if (!strcmp(color, "magenta"))                           printf("\033[35m");/**break**/
	else if (!strcmp(color, "cyan"))                              printf("\033[36m");/**break**/
	else if (!strcmp(color, "light grey"))                        printf("\033[37m");/**break**/
	else if (!strcmp(color, "light red"))                         printf("\033[91m");/**break**/
	else if (!strcmp(color, "light green"))                       printf("\033[92m");/**break**/
	else if (!strcmp(color, "light yellow"))                      printf("\033[93m");/**break**/
	else if (!strcmp(color, "light blue"))                        printf("\033[94m");/**break**/
	else if (!strcmp(color, "light magenta"))                     printf("\033[95m");/**break**/
	else if (!strcmp(color, "light cyan"))                        printf("\033[96m");/**break**/
	else if (!strcmp(color, "white"))                             printf("\033[97m");/**break**/
}

// input & output
unsigned char Menu(const char* choices, unsigned char nb_choices, char* text_color, char* bg_color, unsigned char choice)
{
	const char** text = malloc(nb_choices*sizeof(char*)); // Array of pointers that will point on each choice

	unsigned short max_length=0; // Maximum size of a choice
	unsigned short length[nb_choices]; // Array containing each text's length.

	unsigned short j = 0;
	for (unsigned char i = 0; i < nb_choices; ++i)
	{
		text[i] = choices+j; // Points right after the last '\0' encountered

		length[i] = (unsigned short)strlen(text[i]);
		if (length[i] > max_length)
		{
			max_length = length[i];
		}

		for (; choices[++j] != '\0';); // increment until reaching a '\0'
		++j; // the next string starts right after that
	}

	unsigned short term_width = ConsoleWidth();
	unsigned short term_height = ConsoleHeight();

	if (term_height < (nb_choices + 3) || term_width < (max_length + 3))
	{
		printf("Your screen is too small to have a nice display.\n");
		return 255;
	}//else

	unsigned short x_text[nb_choices]; // x coordinate of each choice to print
	unsigned short y_text[nb_choices]; // same with y coo
	unsigned short x_box = (unsigned short)(term_width - max_length - 2) / 2; // x coordinate of the menu's box
	unsigned short y_box = (unsigned short)((term_height - nb_choices - 2) / 2); // same with y coo

	// External grey layout
	SetCursorPos( x_box, (unsigned short)(y_box-1));
	SetBgColor("light grey");
	for (unsigned short i=0; i<max_length + 3; ++i)
		printf(" ");

	for (unsigned short i=0; i<nb_choices + 2; ++i)
	{
		SetCursorPos( (unsigned short)(x_box + max_length + 2) , (unsigned short)(i + y_box) );
		printf(" ");
	}
	SetBgColor(bg_color);
	SetTextColor(text_color);

	// The inside of the box
	for (unsigned short i=0; i < nb_choices + 2; ++i)
	{
		SetCursorPos( x_box, (unsigned short)(y_box + i));
		for (j=0; j < max_length + 2; ++j)
		{
			printf(" ");
		}
	}

	// Computation of each text coordinate and display
	for (unsigned short i=0; i < nb_choices; ++i)
	{
		//x_text[i] = (unsigned short) ((max_length + 2 - length[i]) / 2 + x_box); //For a centered display
		//x_text[i] = (unsigned short) (x_box + max_length + 1 - length[i]); // For a right aligned display
		x_text[i] = (unsigned short) (x_box + 1); //For a left aligned display
		y_text[i] = (unsigned short) (y_box + i + 1);
		SetCursorPos(x_text[i], y_text[i]);
		printf("%s", text[i]);
	}

	// Printing default selection
	SetTextAttributes("+invert");
	SetCursorPos(x_text[choice], y_text[choice]);
	printf("%s", text[choice]);
	SetTextAttributes("-invert");
	SetCursorPos(x_text[choice], y_text[choice]);

	// We don't want arrow keys to display their weird stuff on the screen
	SetEcho( FALSE );

	// j is used to store the current selected text
	char key_pressed;

	do
	{
		if (term_height != ConsoleHeight() || term_width != ConsoleWidth())
		{
			SetCursorPos(0, 0);
			printf("Changing console size now is discouraged");
		}

		key_pressed = InstantGetChar();
		if (key_pressed == SPECIAL) // pressing an arrow inputs both SPECIAL and a normal letter
		{
			// deselecting text
			key_pressed = InstantGetChar();
			SetCursorPos(x_text[choice], y_text[choice]);
			printf("%s", text[choice]);

			switch (key_pressed)
			{
				case 'A':	//Key up
					if (choice == 0)
						choice = (unsigned char)(nb_choices - 1);
					else --choice;
					break;

				case 'B':	//Key down
					if (choice == nb_choices - 1)
						choice = 0;
					else ++choice;
					break;

				default:
					break;
			}

			// selecting text
			SetCursorPos(x_text[choice], y_text[choice]);
			SetTextAttributes("+invert");
			printf("%s", text[choice]);
			SetTextAttributes("-invert");
			SetCursorPos(x_text[choice], y_text[choice]);
		}
	// loop until the user press Enter
	}while( key_pressed != '\n' );

	// echo back to normal
	SetEcho( TRUE );
	free(text);
	return choice;
}

// pure input

char* GetNumber(unsigned char i_base, BOOL with_brackets)
{
	if (i_base > 10)
		i_base = (unsigned char)(i_base + 'A' - 10); //i_base is now the min char you may not input
	else
		i_base = (unsigned char)(i_base + '0');

	SetEcho( FALSE );
	unsigned short x_cursor_pos = 0;
	if (with_brackets)
	{
		++x_cursor_pos;
		printf("[ ]");
		CursorHorizontalMove( -2 );
	}

	char user_input;
	char* output = NULL; // char* to be returned by this function

	do
	{
		user_input = InstantGetChar();
		user_input = (char)toupper(user_input);

		// Clearing any error message from the previous loop
		printf("\n                              \r");

		// Back to printing position
		CursorVerticalMove( -1 );
		CursorHorizontalMove(x_cursor_pos);

		if (user_input != '\n' && (user_input < '0' || (user_input > '9' && user_input < 'A') || user_input > 'Z'))
		{
			//if input == backspace
			if (user_input == 127)
			{
				if ((x_cursor_pos > 1) || (!with_brackets && x_cursor_pos > 0)) // If there is something to delete
				{
					if (with_brackets)
						printf("\b ] \b\b\b"); // '\b' has a similar effect to Cursorhorizontalmove( -1 )
					else
						printf("\b \b");
					--x_cursor_pos;

					output = (char*) realloc(output, (unsigned)(x_cursor_pos - (with_brackets ? 1 : 0))*sizeof(char)); // Desallocating 1 char
				}
			}
			else
			{
				printf("\n/!\\ %c : Not a Number\r", user_input);
				CursorVerticalMove( -1 );
				CursorHorizontalMove(x_cursor_pos);
			}

		}
		else
		{
			if (user_input != '\n')
			{
				if (user_input >= i_base)
				{
					printf("\n/!\\ %c : NaN in base %d\r", user_input, i_base >= 'A' ? i_base - 'A' + 10  : i_base - '0'); // Display the base in decimal
					CursorVerticalMove( -1 );
					CursorHorizontalMove(x_cursor_pos);
				}
				else
				{
					if (with_brackets)
						printf("%c ]\b\b", user_input);
					else
						printf("%c", user_input);
					++x_cursor_pos;
					output = (char*) realloc(output, (unsigned)(x_cursor_pos - (with_brackets ? 1 : 0))*sizeof(char)); // Allocating 1 extra char
					output[x_cursor_pos - 1 - (with_brackets ? 1 : 0)] = user_input; // Adding 'user_input' at the end of the array
				}
				user_input = 0;
			}
		}
	}while( user_input != '\n' );
	if (with_brackets)
		printf("] ");
	printf("\n");

	SetEcho( TRUE );

	if (x_cursor_pos > 1 || (x_cursor_pos > 0 && !with_brackets)) // if the char* is not empty
	{
		output = (char*) realloc(output, (unsigned)(x_cursor_pos + 1 - (with_brackets ? 1 : 0))*sizeof(char));
		output[x_cursor_pos - (with_brackets ? 1 : 0)] = '\0';
		return output;
	}
	else
	{
		free (output); // Probably useless
		return NULL;
	}
}

BaseNIntegerList GetList()
{
	Clear();
	char user_input;
	unsigned char base=129;

	printf("What is the base of your new list [2~36] ?\n");
	base = (unsigned char)GetNumberWithinRange(2,36);

	// putting a new list in the array list
	BaseNIntegerList l = CreateIntegerList( base );

	printf("Generate a random list ? [Y/n]");
	user_input = InstantGetChar();
	
	if (user_input != 'n' && user_input != 'N')
	{
		unsigned short nb_element = 0;
		unsigned char element_size = 0;
		if (user_input != '\n')
			printf("\n");

		printf("Number of elements in the list ? (min 1, max 65025)\n");	//65025 : ushort
		nb_element = (unsigned short)GetNumberWithinRange(1, 65025);

		printf("Number of maximum digits for each element of the list ? (3 to 15 adviced ; [1~250])\n");
		element_size = (unsigned char)GetNumberWithinRange(1, 250);
		
		printf("Generating list\n");
		srand((unsigned int)time(0));

		// Generating numbers in base 'base' with 10 digits
		for (unsigned short i = 0; i<nb_element; ++i)
		{
			char* number = (char*)malloc((unsigned)(element_size + 1)*sizeof(char));
			number[element_size] = '\0';
			for (unsigned char j = 0 ; j<element_size ; ++j)
			{
				number[j] = (char)(rand()%base);
				number[j] = (char)(number[j] + (number[j] > 9 ? 'A' - 10 : '0'));
			}
			l = InsertTail( l, number); 
		}

		return l;
	}//else

	printf("\nEnter your values in base %d", base);
	printf("\nPress 'enter' on an empty value to end the input\n");

	unsigned int max_length = 0; // maximum number of digits encountered
	unsigned int length; // number of digit of the last inputed number
	char** array_of_values = NULL; // array of char* pointing on the inputed numbers
	unsigned int nb_of_values = 0; // number of numbers inputed

	do
	{
		++nb_of_values;
		array_of_values = (char**) realloc(array_of_values, nb_of_values * sizeof(char*)); // allocating an extra char*
		array_of_values[nb_of_values-1] = GetNumber( base, TRUE );

		if (array_of_values[nb_of_values-1] != NULL)
		{
			length=(unsigned int)strlen(array_of_values[nb_of_values - 1]);

			// deleting eventual left 0 (big endian)
			// note : to be optimised
			while(array_of_values[nb_of_values - 1][0] == '0' && array_of_values[nb_of_values - 1][1] != '\0')
			{
				for (unsigned int j = 0 ; j < length - 1 ; ++j)
					array_of_values[nb_of_values - 1][j] = array_of_values[nb_of_values - 1][j+1]; // shifting to the left
				array_of_values[nb_of_values - 1] = (char*) realloc( array_of_values[nb_of_values - 1], (length - 1)* sizeof(char)); // desallocating a char
				--length;
			}

			if (length > max_length)
				max_length = length;

			// we are using little endian
			Reverse(array_of_values[nb_of_values - 1], length);
		}
	}while (array_of_values[nb_of_values - 1] != NULL);
	// last input was a nullptr
	--nb_of_values;

	// adding right 0 (little endian) so that all chars* have the same size and adding them to the list
	for (unsigned int i = 0 ; i<nb_of_values ; ++i)
	{
		array_of_values[i] = (char*) realloc(array_of_values[i], max_length * sizeof(char));
		for (unsigned int j = (unsigned int)strlen(array_of_values[i]) ; j < max_length ; ++j)
			array_of_values[i][j] = '0';

		l = InsertTail( l, array_of_values[i]);
	}

	free (array_of_values);
	return l;
}

char InstantGetChar()
{
	struct termios original_settings;
	tcgetattr(0, &original_settings);       //retrieve the terminal settings

	struct termios new_settings = original_settings;
	
	new_settings.c_lflag &= ~ICANON;        // Allow getchar() to return without waiting '\n'
	new_settings.c_cc[VMIN] = 1;            // getchar() should read only 1 character
	new_settings.c_cc[VTIME] = 0;           // getchar() should wait for an input, forever.
	tcsetattr(0, TCSANOW, &new_settings);   // applies the new settings
	
	char key = (char)getchar();
	
	tcsetattr(0, TCSANOW, &original_settings);// Back to original settings
	return key;
}

unsigned long int GetNumberWithinRange(unsigned long int min, unsigned long int max)
{
	char* input = NULL;
	unsigned long int output;

	do {
		input = GetNumber(10, FALSE);
		if (!isWithinRange(input, min, max, 10)) {
			printf("                                                     \r");
			free(input);
			input = NULL;
		}
	}while (input == 0);

	output = strtoul(input, NULL, 10);
	free(input);
	return output;
}
// inner functions

unsigned short ConsoleHeight()
{
	struct winsize ws = { 0, 0, 0, 0 };
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
		return 0;

	return ws.ws_row;
}

unsigned short ConsoleWidth()
{
	struct winsize ws = { 0, 0, 0, 0 };
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
		return 0;

	return ws.ws_col;
}

void SetCursorPos(unsigned short x, unsigned short y)
{
	printf("\033[%d;%dH", (int)(y+1), (int)(x+1));
}

void CursorHorizontalMove(int x)
{
	if (x < 0)
		printf("\033[%dD", -x);
	else
		printf("\033[%dC", x);
	if (x == 0)
		printf("\b");

}

void CursorVerticalMove(int y)
{
	if (y < 0)
		printf("\033[%dA", -y);
	else
		printf("\033[%dB", y);
}

void SetEcho(BOOL on)
{
	struct termios tty;
	tcgetattr(STDIN_FILENO, &tty);
	if (on)
		tty.c_lflag |= ECHO;
	else
		tty.c_lflag &= ~ECHO;

	tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

int power( int number, unsigned int power )
{
	int res=1;
	for (unsigned int i=0; i<power; ++i)
		res*=number;
	return res;
}

BOOL isWithinRange(char* val, unsigned long int min, unsigned long int max, unsigned char base)
{
	if (val == NULL)
	{
		printf("You should input a number");
		SetEcho(FALSE);
		InstantGetChar();
		SetEcho(TRUE);
		printf("\r                         \r");
		CursorVerticalMove( -1 );
		return FALSE;
	}

	unsigned long long int value = strtoull( val, NULL, base );

	if (value < min)
	{
		printf("/!\\ Should be at least %lu", min);
		SetEcho(FALSE);
		InstantGetChar();
		SetEcho(TRUE);
		printf("\r                             \r");
		CursorVerticalMove( -1 );
		return FALSE;
	}

	if (value > max)
	{
		printf("/!\\ Should be at most %lu", max);
		SetEcho(FALSE);
		InstantGetChar();
		SetEcho(TRUE);
		printf("\r                                \r");
		CursorVerticalMove( -1 );
		return FALSE;
	}

	return TRUE;
}

void Reverse(char array[], unsigned int size)
{
	char tmp;
	unsigned int max = size/2;
	--size;
	for (unsigned int i = 0 ; i < max ; ++i)
	{
		tmp = array[i];
		array[i] = array[size - i];
		array[size - i] = tmp;
	}
}
