/*********************************
* Class: MAGSHIMIM Final Project *
* Play function declaration	 	 *
**********************************/

#ifndef PROJECTH
#define PROJECTH
#include "LinkedList.h"

/*
	This function load the project, into linked list by the file.
	Input: project, pointer to head.
	Output: none
*/

void loadProject(FrameNode** head);

/*
	This function save project into file.
	Input: head pointer.
	Output: None.
*/
void saveProject(FrameNode** head);


#endif