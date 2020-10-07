#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// pQueue data structure
typedef struct pQueue
{
	char name[35];
	unsigned int priority;
	struct pQueue* next;
}pQueue;

// QUEUE
pQueue QUEUE;

// function declarations
void enqueue(char* name, unsigned int priority);
bool dequeue(void);
void traverse(void);
bool queue_empty(void);

int main(void)
{
	// list of names and priorities
	char* names[5] = { "Aman", "Tom", "Pratyush", "Dawud", "Mr. Wood" };
	unsigned int priorities[5] = { 2, 4, 3, 1, 0 };

	// enqueue new names into priority queue
	for (int i = 0; i < 5; i++)
	{
		enqueue(names[i], priorities[i]);
	}

	// print queue
	printf("LIST\n");
	traverse();

	// dequeue 2 nodes in queue
	for (int i = 0; i < 2; i++)
	{
		dequeue();
	}

	// print queue
	printf("\nLIST\n");
	traverse();

	// dequeue all items in list - reject dequeues when empty
	for (int i = 0; i < 7; i++)
	{
		dequeue();
	}

	// print queue
	printf("\nLIST\n");
	traverse();
}

void enqueue(char* name, unsigned int priority)
{
	// empty queue
	if (queue_empty())
	{

		strcpy_s(QUEUE.name, strlen(name) + 1, name);
		QUEUE.priority = priority;
	}
	else if (QUEUE.priority > priority)
	{
		// create temp. pointer
		pQueue* tmpPtr;
		do
		{
			tmpPtr = malloc(sizeof(pQueue));
			if (tmpPtr == NULL)
			{
				free(tmpPtr);
			}
		} while (tmpPtr == NULL);

		// copy start of queue into the temp. pointer
		tmpPtr->next = QUEUE.next;
		strcpy_s(tmpPtr->name, strlen(QUEUE.name) + 1, QUEUE.name);
		tmpPtr->priority = QUEUE.priority;

		// create new node into start of queue
		strcpy_s(QUEUE.name, strlen(name) + 1, name);
		QUEUE.priority = priority;
		QUEUE.next = tmpPtr;
	}
	else
	{
		// find queue with lower priority or until end of queue reached
		pQueue* posPtr = &QUEUE;
		while (true)
		{
			if (posPtr->next == NULL)
			{
				break;
			}
			else
			{
				if (posPtr->next->priority > priority)
				{
					break;
				}
			}
			posPtr = posPtr->next;
		}

		// declare newPtr
		pQueue* newPtr;
		do
		{
			newPtr = malloc(sizeof(pQueue));
			if (newPtr == NULL)
			{
				free(newPtr);
			}
		} while (newPtr == NULL);

		// initialise newPtr
		strcpy_s(newPtr->name, strlen(name) + 1, name);
		newPtr->priority = priority;


		if (posPtr->next == NULL)
		{
			newPtr->next = NULL;
			posPtr->next = newPtr;
		}
		else
		{
			newPtr->next = posPtr->next;
			posPtr->next = newPtr;
		}
	}
}

bool dequeue(void)
{
	if (queue_empty())
	{
		return false;
	}
	// if no QUEUE.next - delete current QUEUE.name
	else if (QUEUE.next == NULL)
	{
		strcpy_s(QUEUE.name, strlen("") + 1, "");
	}
	else
	{
		//delete node
		pQueue* tmpPtr = QUEUE.next;

		strcpy_s(QUEUE.name, strlen(QUEUE.next->name)+1, QUEUE.next->name);
		QUEUE.priority = QUEUE.next->priority;
		QUEUE.next = QUEUE.next->next;

		free(tmpPtr);
	}
	return true;
}

bool queue_empty(void)
{
	return strcmp(QUEUE.name, "") == false;
}

// print queue
void traverse(void)
{
	pQueue* posPtr = &QUEUE;
	while (true)
	{
		printf("name: %s, priority: %i\n", posPtr->name, posPtr->priority);
		if (posPtr->next != NULL)
		{
			posPtr = posPtr->next;
		}
		else
		{
			break;
		}
	}
}