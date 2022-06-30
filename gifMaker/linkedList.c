#include <stdio.h>
#include "linkedList.h"
#include <string.h>


/*
	This function create a frame in the linked list, have those three parametrs, name path and duration.
	This function also validate if the input is correct
	Input: head.
	Output: the new frame.
*/
FrameNode* createFrame(FrameNode* head)
{
	char name[NAME_SIZE] = { 0 };
	char path[PATH_SIZE] = { 0 };
	int duration = 0;
	FrameNode* newFrame = (FrameNode*)malloc(sizeof(FrameNode)); // allocate memory for the new frame
	FILE* fileFrame = NULL;	

	if (newFrame == NULL) // in case the memory didnt allocated well
	{
		printf("Error, cant allocate memory.");
		return NULL;
	}

	newFrame->frame = (Frame*)malloc(sizeof(Frame)); // allocate memory for the frame

	if (newFrame->frame == NULL) // in case the memory didnt allocated well
	{
		printf("Error, cant allocate memory");
		return NULL;
	}
	printf("*** Creating new frames ***\nPlease insert file path:\n");

	/*
		Insert the path
	*/
	myFgets(path, PATH_SIZE); 

	fileFrame = fopen(path, "rb"); // open file

	if (fileFrame != NULL && strstr(path, "png") || strstr(path, "jpg")) // if file doesnt exist or file extension is not image
	{
		newFrame->frame->path = (char*)malloc(strlen(path) * sizeof(char)); // allocate memory for the path in the node
		if (newFrame->frame->path == NULL) // in case allocate memory didnt allocated well
		{
			printf("Error, cant allocate Memory");
			return NULL;
		}
		strcpy(newFrame->frame->path, path); // copy path, into frame path
	}
	else
	{
		printf("File path is not correct.\n");
		free(newFrame);
		return NULL;
	}
	fclose(fileFrame); // close file

	/*
		Insert the duration into the frame
	*/

	printf("Please enter the playtime of the frame: ");
	scanf("%d", &duration);
	getchar(); // clean buffer

	if (duration == 0)
	{
		getchar(); // clean buffer
		free(newFrame);
		return NULL;
	}
	newFrame->frame->duration = duration; // set the frame duration into the duration the user 
	

	/*
		Insert the name
	*/
	printf("Please insert name of the frame: ");
	myFgets(name, NAME_SIZE);

	newFrame->frame->name = (char*)malloc(strlen(name), sizeof(char)); // allocate memory for the name

	if (newFrame->frame->path == NULL)
	{
		printf("Error, cant allocate Memory");
		return NULL;
	}
	
	while (isNameExist(head, name)) // if name already exist or empty
	{
		printf("Name already exist!, please try again: ");
		myFgets(name, NAME_SIZE);
	}

	if (!isNameExist(head, name))
	{
		strcpy(newFrame->frame->name, name); // copy name into frame node name
	}


	newFrame->next = NULL; 

	return newFrame;
}

/*
	This function will print the frames details
	Input: head of the linked list.
	Output: none.
*/
void printFrames(FrameNode* head)
{
	FrameNode* curr = head;
	while (curr != NULL)
	{
		printf("Frame Path				Frame Name			Frame PlayTime\n");
		printf("%s               %s				%d (miliseconds)\n", curr->frame->path, curr->frame->name, curr->frame->duration);
		curr = curr->next;
	}
}

/*
	This function check if name already exist in the linked list.
	Input: head of the linked list, name to check.
	Output: if name already exist
*/
int isNameExist(FrameNode* head, char* name)
{
	FrameNode* curr = head;
	int isExist = FALSE;

	while (curr != NULL)
	{
		if (strcmp(curr->frame->name, name) == 0) // if the name already exist in the frames list.
		{
			isExist = TRUE;
		}
		curr = curr->next; // move forward
	}

	return isExist;
}

void myFgets(char str[], int n)
{
	fgets(str, n, stdin);
	str[strcspn(str, "\n")] = 0;
}

/*
	This function insert node in the head of the linked list.
	Input: pointer to head, node to insert.
	Output: None
*/
void insertAtEnd(FrameNode** head, FrameNode* newNode)
{
	FrameNode* curr = *head;
	if ((*head) == NULL) // empty list!
	{
		*head = newNode;
	}
	else
	{
		while (curr->next) // while the next is NOT NULL (when next is NULL - that is the last node)
		{
			curr = curr->next;
		}

		curr->next = newNode;
		newNode->next = NULL;
	}
}
	

/*
	This function erase frame from the linked list
	Input: pointer to head.
	Output: None.
*/
void eraseFrame(FrameNode** head)
{
	FrameNode* curr = *head;
	char name[NAME_SIZE] = { 0 }; 
	FrameNode* temp = NULL;
	int removed = FALSE;

	printf("Enter the name of the frame to erase: ");
	myFgets(name, NAME_SIZE); // get name to of frame to delete

	if (isNameExist(curr, name))
	{
		if (strcmp(curr->frame->name, name) == 0) // in case the first frame is the one to delete
		{
			*head = (*head)->next; // we are going to delete the node, so we have to fill the deleted node with next one

			free(curr->frame); // free the frame.
			free(curr); // free the whole node	
			printf("Frame Removed Successfully.");
		}
		else
		{
			while (curr->next && !removed) // if deleted stop the loop to not make the loop run more times for nothing
			{
				if (strcmp(curr->next->frame->name, name) == 0)
				{
					temp = curr->next; // set temp as the node to delete
					curr->next = temp->next; // link the nodes

					free(temp->frame); // free the frame.
					free(temp); // free the whole node
					printf("Frame Removed Successfully.");
					removed = TRUE;
				}
				else
				{
					curr = curr->next;
				}
			}
		}
	}
	else
	{
		printf("Error, No frame called %s found", name);
	}	
}


/*
	This function change frame location in the linked list.
	Input: pointer to head.
	Output: None.
*/

void changeFrameLocation(FrameNode** head)
{
	int index = 0; 
	char name[NAME_SIZE] = { 0 };
	FrameNode* curr = *head;
	FrameNode* temp = *head;
	int i = 0;
	int indexOfNode = 0;
	int moved = FALSE;
	printf("Enter the name of the frame: ");
	myFgets(name, NAME_SIZE); // get name to of frame to move

	if (!isNameExist(curr, name))
	{
		printf("This frame doesn't exist.");
	}
	else
	{
		printf("Enter the new index in the movie you wish to place the frame: ");
		scanf("%d", &index);
		getchar(); // clear buffer
		index = index - 1;
		if (index < 0 || framesCount(curr) < index)
		{
			printf("Max index in list is: %d, please try again", framesCount(curr));
		}
		else
		{
			if (strcmp(curr->frame->name, name) == 0) // if the name to find is the same as the frame name
			{
				*head = (*head)->next; 
				temp = curr;

				if (framesCount(curr) > index)
				{
					for (i = 0; i < index - 1; i++) // run to the index 
					{
						curr = curr->next; 
					}

					temp->next = curr->next;
					curr->next = temp;
				}
			} 
			else
			{
				while (curr && !moved) // run on all the frames
				{
					if ((strcmp(curr->next->frame->name, name)) == 0)  // if there is a match on the name.
					{	
						temp = curr->next;  
						curr->next = temp->next; // link the node to the node after

						curr = *head;


						if (!(index > framesCount(*head)))
						{
							for (i = 0; i < index; i++) // run on all the index's
							{
								curr = curr->next;
							}

							if (curr->next)
							{
								temp->next = curr->next; // link the node to move 
								curr->next = temp;
								moved = TRUE;
							}
						}
					}
					else
					{
						curr = curr->next;
					}
				}
			}
		}
	}
}



/*
	This function change specific frame playtime(duration) by the name
	Input: pointer to head.
	Output: none
*/
void changeFramePlayTime(FrameNode** head)
{
	char name[NAME_SIZE] = { 0 };
	FrameNode* curr = *head;
	int changed = FALSE;
	int duration = 0;
	printf("Enter the name of the frame: ");
	myFgets(name, NAME_SIZE); // get name to of frame to move

	if (!isNameExist(curr, name))
	{
		printf("This frame doesn't exist.");
	}
	else
	{
		printf("Please Enter a new duration: ");
		scanf("%d", &duration);
		getchar(); // clean buffer.
		while (curr != NULL && !changed)
		{
			if (strcmp(curr->frame->name, name) == 0) 
			{
				curr->frame->duration = duration; // set the frame duration as the new duration
				changed = TRUE; 
			}
			curr = curr->next; // move forward
		}
	}
}


/*
	This function change all frames playtime (duration)
	Input: pointer to head.
	Output: none
*/
void changeAllFramesPlayTime(FrameNode** head)
{
	int duration = 0;
	FrameNode* curr = *head;

	printf("Please Enter a new duration: ");
	scanf("%d", &duration);
	getchar(); // clean buffer
	if (duration < 0)
	{
		printf("Please try again with a valid value.");
	}
	else
	{
		while (curr != NULL) // run untill there is no frames
		{
			curr->frame->duration = duration; // set frame new duration
			curr = curr->next; // move forward
		} 
	}
}

/*
	This function count the frames in the linked list.
	Input: head.
	Output: frames count.
*/
int framesCount(FrameNode* head)
{
	int frames = 0;
	
	while (head != NULL) // run untill there's no frames
	{
		frames++; 
		head = head->next;  // move forward
	}

	return frames;
}

/*
	This function is free the allocated memory of the linked list.
	Input: pointer to head.
	Output: none.
*/
void freeNodes(FrameNode** head)
{
	if (*head)
	{
		if ((*head)->next)
		{
			freeNodes(&((*head)->next));
		}
		free((*head)->frame);
		free(*head); // after freeing the other allocated 
	}
}

/*
	This function reverse all the frames
	Input: pointer to head of the linked list.
	Output: None.
*/
void reverseFrames(FrameNode** head)
{
	FrameNode* prev = NULL;
	FrameNode* current = *head;
	FrameNode* next = NULL;

	while (current != NULL)
	{
		next = current->next; // save the next frame
		current->next = prev; // set the next node as the previous
		prev = current; // move previous next
		current = next; // move current next
	}

	*head = prev;
}