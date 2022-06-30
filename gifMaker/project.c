#include <stdio.h>
#include "project.h"
#include <string.h>

#define MAX_LINE 500

/*
	This function save project into file, using format : {name},{duration},{path}\n etc...
	Input: pointer to head.
	Output: None
*/
void saveProject(FrameNode** head)
{
	FrameNode* curr = *head;
	FILE* projectFile = NULL;
	int first = TRUE;
	char filePath[PATH_SIZE] = { 0 };
	printf("Please enter file path to save project in: ");
	myFgets(filePath, PATH_SIZE);

	projectFile = fopen(filePath, "w");

	if (projectFile != NULL)
	{
		while (curr) 
		{
			fprintf(projectFile, "%s,%d,%s\n", curr->frame->name, curr->frame->duration, curr->frame->path); // add to the file name,duration,path and new line again 
			curr = curr->next;
		}
	}
	else
	{
		printf("Cant open file, please try again with another path.");
	}

	fclose(projectFile); // move this near the return.
}

/*
	This function load project from file, into linked list
	Input: pointer to head of the list.
	Output: None
*/
void loadProject(FrameNode** head)
{
	FILE* projectFile = NULL;
	char name[NAME_SIZE] = { 0 };
	int duration = 0;
	char path[PATH_SIZE] = { 0 };
	char line[MAX_LINE] = { 0 };
	char* temp = 0;

	printf("Enter the path of the project (including project name):\n");
	myFgets(path, PATH_SIZE);

	projectFile = fopen(path, "r"); // load project

	if (projectFile == NULL)
	{
		printf("Error! Unable to open file!!\n");
		return 1;
	}

	while (fgets(line, MAX_LINE, projectFile)) // read all lines
	{
		line[strlen(line) - 1] = 0;

		// this lines get name, duration, path of each line
		temp = strtok(line, ","); 
		strcpy(name, temp);

		temp = strtok(NULL, ","); 
		duration = atoi(temp);

		temp = strtok(NULL, ","); 
		strcpy(path, temp);

		if ((strstr(path, "png") || strstr(path, "jpg")))
		{
			FrameNode* newFrame = (FrameNode*)malloc(sizeof(FrameNode)); // allocate memory for new node
			newFrame->frame = (Frame*)malloc(sizeof(Frame)); // allocate memory for new frame

			// allocate memory for name and insert the name
			newFrame->frame->name = (char*)malloc(sizeof(char) * strlen(name) + 1);
			strcpy(newFrame->frame->name, name);

			// allocate memory for name and insert the path
			newFrame->frame->path = (char*)malloc(sizeof(char) * strlen(path) + 1);
			strcpy(newFrame->frame->path, path);

			newFrame->frame->duration = duration; // insert the path
			newFrame->next = NULL;

			insertAtEnd(head, newFrame);
		}
	}

	fclose(projectFile); // move this near the return.
}

