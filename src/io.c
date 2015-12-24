#include <io.h>

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
	unsigned short b = 3; // To display numbers by group of 3
	unsigned short term_height = ConsoleHeight();
	unsigned short term_width = ConsoleWidth();
	unsigned short j = 0;	// Counter for the number of elements currently on the screen
	unsigned short max_val_size = 0;
	unsigned short nb_displayed = 0; // Counter for the total amount of elements displayed
	char user_input = 0;
	BOOL digit_was_displayed; // Used to remove the left '0' (on display)
	unsigned short tmp;

	while (elem != NULL) {
		tmp = (unsigned short)strlen(elem->value);
		if (tmp > max_val_size) {
			max_val_size = tmp;
		}
		elem = elem->next;
	}
	elem = l.head;

	if (l.base == 2 || l.base == 16) {
		b = 4;
	}

	//we want to display a space every b numbers plus the '[' ']' around them
	if (term_width < ((b+1) * max_val_size / b + (max_val_size%b!=0) + 1))
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

	char percentage[45]; // Contains percentage and usable inputs (for display purposes)
	int cursor_shift = 1 + (b+1) * max_val_size / b + (max_val_size%b != 0);
	unsigned short whitesp;

	while (elem != NULL && user_input != 'q')
	{
		// if we have some space in the terminal to display yet another list element
		if (j < term_height)
		{
			++j;
			++nb_displayed;
			digit_was_displayed = FALSE;

			// Align : right
			CursorHorizontalMove(term_width - cursor_shift);

			// Printing the value of the pointed element
			printf("[");

			tmp = (unsigned short)strlen(elem->value);

			// Number of extra whitespaces to print for all nb to have the same size
			whitesp = (unsigned short)((b + 1)*(max_val_size - tmp) / b);

			/* A little bit of magic */
			if (max_val_size != tmp) {
				if (b == 4) {
					switch (max_val_size%b) {
					case 3:
						if (tmp%b == 0) {
							++whitesp;
						}
						break;
					case 2:
						if (tmp%b == 3 || tmp%b == 0) {
							++whitesp;
						}
						break;
					case 1:
						if (tmp%b != 1) {
							++whitesp;
						}
						break;
					default:
						break;
					}
				}
				else {
					switch (max_val_size%b) {
					case 2:
						if (tmp%b == 0) {
							++whitesp;
						}
						break;
					case 1:
						if (tmp%b != 1) {
							++whitesp;
						}
						break;
					default:
						break;
					}
				}
			}

			// Printing whitespaces for missing left values
			for (unsigned short i = whitesp ; i > 0 ; --i) {
				printf(" ");
			}

			for (unsigned short i = tmp; i-- ;)	// We are in Little Endian
			{
				// We don't want to display eventuals 0 on the left, but we want to display 0 if the actual value is 0
				if (!digit_was_displayed && elem->value[i] == '0' && i != 0){
					printf(" ");
					if (i%b == 0 && i >= b ) {
						printf(" ");
					}
				}
				else
				{
					printf("%c", elem->value[i]);
					digit_was_displayed = TRUE;
					if (i%b == 0 && i != 0) {
						printf(" ");
					}
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
					if (term_width > (max_val_size + 5))
					{
						CursorVerticalMove( -1 );
						if (term_width > (22 + cursor_shift))
						{
							// Align : right
							CursorHorizontalMove(term_width - 22 - cursor_shift);
							printf("Last line was here -->\r");
						}
						else
						{
							CursorHorizontalMove(term_width - 3 - cursor_shift);
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
		(void)InstantGetChar();
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
				case 'A':	//Arrow up
					if (choice == 0)
						choice = (unsigned char)(nb_choices - 1);
					else --choice;
					break;

				case 'B':	//Arrow down
					if (choice == nb_choices - 1)
						choice = 0;
					else ++choice;
					break;

				case '5':	//Page Up
					choice = 0;
					break;

				case '6':	//Page Down
					choice = (unsigned char)(nb_choices - 1);
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

BOOL yes(char* question, char default_ans)
{
	char answer;
	printf("%s [%c/%c]", question, default_ans == 1 ? 'Y' : 'y', default_ans == -1 ? 'N' : 'n');
	SetEcho(FALSE);
	do {
		answer = InstantGetChar();
		answer = (char)tolower(answer);
		if (default_ans == 1) {
			if (answer != 'n') {
				answer = 'y';
			}
		} else {
			if (default_ans == -1) {
				if (answer != 'y') {
					answer = 'n';
				}
			}

		}
	}while (answer != 'y' && answer != 'n');
	SetEcho(TRUE);
	printf("%c\n", answer);
	return answer == 'y' ? TRUE : FALSE;

}
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
	unsigned char base=129;

	printf("What is the base of your new list [2~36] ?\n");
	base = (unsigned char)GetNumberWithinRange(2,36);

	// putting a new list in the array list
	BaseNIntegerList l = CreateIntegerList( base );


	if (yes("Generate a random list ?", 1))
	{
		unsigned short nb_element = 0;
		unsigned char element_size = 0;

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

	char* value;

	do
	{
		value = GetNumber(base, TRUE); // GetNumber allocates a new char*

		if (value != NULL)
		{
			unsigned int i = 0;
			unsigned int j = 0;
			// deleting eventual left 0 (big endian)
			while(value[i] == '0' && value[i+1] != '\0')
			{
				++i;
			}

			if (i != 0) {
				while (value[i+j] != '\0') {
					value[j] = value[i+j];
					++j;
				}
				value[j] = '\0';
				value = (char*) realloc(value, j + 1);
			}

			// we are using little endian
			Reverse(value, (unsigned int)strlen(value));
			l = InsertTail( l, value);
		}
	}while (value != NULL);

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
