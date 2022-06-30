#include <stdio.h>
#include<conio.h>
#include "gui.h"


#define BLUE "\033[0;34m"
#define GREEN "\033[0;32m"
#define CYAN "\033[0;36m"
#define RED "\033[0;31m"
#define MAGENTA "\033[0;35m"
#define YELLOW "\033[0;33m"

/*
	This function print the menu using colors
	Input: None
	Output: None
*/

void printMenu()
{
	printf("What would you like to do ?\n");
	printf(RED);

	printf("( 0 ) Exit\n");
	printf(MAGENTA);

	printf("( 1 ) Add new Frame\n");
	printf(RED);

	printf("( 2 ) Remove a Frame\n");
	printf(CYAN);

	printf("( 3 ) Change frame index\n");
	printf(BLUE);

	printf("( 4 ) Change frame duration\n");
	printf(YELLOW);

	printf("( 5 ) Change duration of all frames\n");
	printf(MAGENTA);

	printf("( 6 ) List frames\n");
	printf(CYAN);

	printf("( 7 ) Reverse List\n");
	printf(GREEN);

	printf("( 8 ) Play movie!\n");
	printf(YELLOW);

	printf("( 9 ) Save project\n");
}