# define CV_IGNORE_DEBUG_BUILD_GUARD
# define _CRT_SECURE_NO_WARNINGS
# include <opencv2/imgcodecs/imgcodecs_c.h>
#include <stdio.h>
#include <conio.h>

#include "linkedList.h"
#include "gui.h"
#include "view.h"
#include <string.h>

enum options { Exit, addFrame, erase, changeLocation, changeDuration, changeAllDuration, print, reverse, playList, save};

int main()
{
	FrameNode* frameList = NULL;
	FrameNode* newFrame = NULL;
	int exit = FALSE;
	char choice = 0;
	int iChoice = 0;
	int sound = FALSE;
	int isValid = FALSE;
	char path[PATH_SIZE] = { 0 };
	int c = 0;
	printf("Welcome to gif maker :D\n[1] Create New Project\n[2] Load an exist project\n");
	choice = _getch();
	iChoice = choice - '0';
	if (iChoice == 2)
	{
		loadProject(&frameList);
	}
	while ((c = getchar()) != '\n' && c != EOF) {}
	while (!exit)
	{
		printMenu();
		choice = _getch();
		iChoice = choice - '0';
		system("cls");
		switch (iChoice)
		{
		case Exit:
			freeNodes(&frameList);
			exit = TRUE;
			break;

		case addFrame:
			newFrame = createFrame(frameList);

			if (newFrame != NULL)
			{
				insertAtEnd(&frameList, newFrame);
				printf("Frame Added Successfull.!\n");
			}
			else
			{
				getchar(); // clean buffer.
			}
			break;

		case erase:
			eraseFrame(&frameList);
			break;

		case changeLocation:
			changeFrameLocation(&frameList);
			break;

		case changeDuration:
			changeFramePlayTime(&frameList);
			break;

		case changeAllDuration:
			changeAllFramesPlayTime(&frameList);
			break;

		case print:
			printFrames(frameList);
			break;

		case reverse:
			reverseFrames(&frameList);
			break;

		case playList:
			play(frameList);
			break;

		case save:
			saveProject(&frameList);
			break;

		default:
			printf("Please select option between 1 - 9");
			break;
		}
	}
	return 0;
}

