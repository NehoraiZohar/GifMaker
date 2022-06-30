# define CV_IGNORE_DEBUG_BUILD_GUARD
# include <opencv2/imgcodecs/imgcodecs_c.h>

#ifndef LINKEDLISTH

#define LINKEDLISTH

#define FALSE 0
#define TRUE !FALSE

#define PATH_SIZE 256
#define NAME_SIZE 256

// Frame struct
typedef struct Frame
{
	char* name;
	unsigned int	duration;
	char* path;
} Frame;


// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;


/*
	This fuction get creates a node, of frame (name, duration, path).
	Input: head.
	Output: the pointer to the node
*/
FrameNode* createFrame(FrameNode* head);

/*
	This function erase (remove) a node from the linked list.
	Input: pointer to head 
	Output: None
*/
void eraseFrame(FrameNode** head);

/*
	This function change frame location in the linked list.
	Input: pointer to head.
	Output: None.
*/

void changeFrameLocation(FrameNode** head);

/*
	This function change frame playtime, like 1s to 5s.
	Input: pointer to head.
	Output: none
*/
void changeFramePlayTime(FrameNode** head);

/*
	This function change *all* frames playtime in the linked list 
	Input: pointer to head
*/

void changeAllFramesPlayTime(FrameNode** head);

/*
	This function print the frames in the linked list.
	Input: head.
	Output: None
*/

void printFrames(FrameNode* head);

/*
	This function count the linked list nodes.
	Input: head.
	Output: the length of the list
*/
int framesCount(FrameNode* head);

/*
	This function free the memory of the nodes.
	Input: pointer to head.
	Output: None.
*/
void freeNodes(FrameNode** head);

/*
	This function check if the name in the node is already exist.
	Input: head, name
	Output: if the name is exist or not.
*/
int isNameExist(FrameNode* head, char* name);

void myFgets(char str[], int n);

/*
	this function is inserting at the end.
	Input: pointer to head, newMode.
	Output: none.
*/
void insertAtEnd(FrameNode** head, FrameNode* newNode);

/*
	This function reverse all the frames
	Input: pointer to head of the linked list.
	Output: None.
*/
void reverseFrames(FrameNode** head);


#endif
