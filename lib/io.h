#ifndef BOOL_DEFINED
#define BOOL_DEFINED
typedef enum{
	FALSE = 0,
	TRUE = 1
}BOOL;
#endif // BOOL_DEFINED

#ifndef SPECIAL_DEFINED
#define SPECIAL '['
#endif

#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

// pure output
void Clear(void);
void SetTextAttributes(char* attribute);
void SetBgColor(char* color);
void SetTextColor(char* color);
void CPrint(char* text, unsigned short y_pos);
//void PrintList(List l);

// input & output
unsigned char Menu(char* choices, unsigned char nb_choices, char* text_color, char* bg_color);

// pure input
//void GetList(ArrayOfList list_array, unsigned char base);
char InstantGetChar(void);

// inner functions
unsigned short ConsoleHeight(void);
unsigned short ConsoleWidth(void);
void SetCursorPos(unsigned short x, unsigned short y);
void CursorHorizontalMove(int x);
void CursorVerticalMove(int y);
void SetEcho(BOOL on);
//void GenerateRandomList();

#endif // IO_H_INCLUDED
