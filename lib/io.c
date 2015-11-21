#include "io.h"


// pure output
void Clear()
{
	printf("\033[2J");	// ANSI escape for clearing the screen
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
	SetEcho( FALSE );
	Clear();
	ListElem* elem = l.head;
	unsigned short term_height = ConsoleHeight();
	unsigned short term_width = ConsoleWidth();
	unsigned short j=0;
	unsigned short val_size = (unsigned short)strlen(elem->value); // all values should have the same size
	unsigned char nb_displayed = 0;
	char user_input = 0;
	BOOL digit_was_displayed;

	if (term_width < (val_size + 2))
	{
		printf("This screen is too small to display this list properly.\n");
		printf("Press Enter if you still want to do it.");
		if (InstantGetChar() != '\n')
			return;
		Clear();
	}

	//keeping space for percentage display
	--term_height;

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
			for (unsigned short i = 0; i < val_size; ++i)
			{
				// We don't want to display left 0, but we want to display 0 if its value is 0
				if (digit_was_displayed == FALSE && elem->value[i] == '0' && i+1 < val_size)
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
				printf("-- %d%% -- [inputs : ' ', '\\n', 's', 'q']\r", 100 * nb_displayed / l.size);
			else
				printf("-- %d%% --\r", 100 * nb_displayed / l.size);
			SetTextAttributes("-invert");

			user_input = InstantGetChar();

			// Clearing line
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
					--j;
					break;
			}

			// Clearing line
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
		printf("-- END --");
		SetTextAttributes("-invert");
		InstantGetChar();
	}
	printf("\n");
	SetEcho( TRUE );
}
void SetTextAttributes(char* attribute)
{
	switch (attribute[0])
	{
		case '+':
			if (!strcmp(attribute, "+bold"))               printf("\033[1m");/**ifbreak**/
			else if (!strcmp(attribute, "+dim"))           printf("\033[2m");/**ifbreak**/
			else if (!strcmp(attribute, "+underline"))     printf("\033[4m");/**ifbreak**/
			else if (!strcmp(attribute, "+blink"))         printf("\033[5m");/**ifbreak**/
			else if (!strcmp(attribute, "+invert"))        printf("\033[7m");/**ifbreak**/
			else if (!strcmp(attribute, "+strike"))        printf("\033[8m");/**ifbreak**/
			break;
		case '-':
			if (!strcmp(attribute, "-bold"))               printf("\033[21m");/**ifbreak**/
			else if (!strcmp(attribute, "-dim"))           printf("\033[22m");/**ifbreak**/
			else if (!strcmp(attribute, "-underline"))     printf("\033[24m");/**ifbreak**/
			else if (!strcmp(attribute, "-blink"))         printf("\033[25m");/**ifbreak**/
			else if (!strcmp(attribute, "-invert"))        printf("\033[27m");/**ifbreak**/
			else if (!strcmp(attribute, "-strike"))        printf("\033[29m");/**ifbreak**/
			break;
		default:
			if (!strcmp(attribute, "reset"))               printf("\033[0m");/**ifbreak**/
			break;
	}
}
void SetBgColor(char* color)
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

void SetTextColor(char* color)
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
unsigned char Menu(char* choices, unsigned char nb_choices, char* text_color, char* bg_color)
{
	char** text = malloc(nb_choices*sizeof(char*)); // text is an array of pointers that will point on each choice

	unsigned short j=0; // generic iterator
	unsigned short max_length=0; // maximum size of a choice
	unsigned short length[nb_choices]; // length is an array containing each text's length.
	for (unsigned char i = 0; i < nb_choices; ++i)
	{
		text[i] = choices+j; // points right after the last '\0' encountered
		length[i] = (unsigned short)strlen(text[i]);
		if (length[i] > max_length)
		{
			max_length = length[i];
		}
		for (; choices[j] != '\0'; ++j ); // increment until reaching a '\0'
		++j;
	}

	unsigned short term_width = ConsoleWidth();
	unsigned short term_height = ConsoleHeight();

	if (term_height < (nb_choices + 3) || term_width < (max_length + 3))
	{
		printf("Your screen is too small to have a nice display.\n");
		return 255;
	}//else

	unsigned short x_text[nb_choices]; // x coordinate of each text to print
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
		x_text[i] = (unsigned short) ((max_length + 2 - length[i]) / 2 + x_box);
		y_text[i] = (unsigned short) (y_box + i + 1);
		SetCursorPos(x_text[i], y_text[i]);
		printf("%s", text[i]);
	}

	// Default selection : text[0]
	SetTextAttributes("+invert");
	SetCursorPos(x_text[0], y_text[0]);
	printf("%s", text[0]);
	SetTextAttributes("-invert");
	SetCursorPos(x_text[0], y_text[0]);

	// We don't want arrow keys to display their weird stuff on the screen
	SetEcho( FALSE );

	// j is used to store the current selected text
	j=0;
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
			SetCursorPos(x_text[j], y_text[j]);
			printf("%s", text[j]);

			switch (key_pressed)
			{

				case 'A':
					if (j == 0)
						j=(unsigned short)(nb_choices - 1);
					else --j;
					break;

				case 'B':
					if (j == nb_choices - 1)
						j=0;
					else ++j;
					break;

				default:
					break;
			}

			// selecting text
			SetCursorPos(x_text[j], y_text[j]);
			SetTextAttributes("+invert");
			printf("%s", text[j]);
			SetTextAttributes("-invert");
			SetCursorPos(x_text[j], y_text[j]);
		}
	// loop until the user press Enter
	}while( key_pressed != '\n' );

	// echo back to normal
	SetEcho( TRUE );
	free(text);
	return (unsigned char)j;
}
// pure input
/*void GetList(ArrayOfList list_array, unsigned char base)
{
	char user_input;
	printf("Generate a random list ? [Y/n]");
	user_input = getchar();

	while(getchar() != '\n'); // clears the buffer

	if (user_input == 'y' || user_input == 'Y')
	{
		GenerateRandomList();
		return;
	}//else;

	unsigned short x_pos, y_pos;
	GetCursorPos(&x_pos, &y_pos);
	do
	{
		printf("[ ]");

	}while (user_input != '\n');
}*/

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
	printf("\033[%d;%dH", (int)(y+1), (int)(x+1)); // Quite a barbarian stuff…
}

void CursorHorizontalMove(int x)
{
	if (x < 0)
		printf("\033[%dD", -x);
	else
		printf("\033[%dC", x);

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
	if( on == TRUE )
		tty.c_lflag |= ECHO;
	else
		tty.c_lflag &= ~ECHO;

	tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}