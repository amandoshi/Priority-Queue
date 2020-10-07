#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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
char* peek(void);
void dequeue(void);

int main(void)
{
	char* names[5] = { "Aman", "Tom", "Pratyush", "Dawud", "Mr. Wood" };
	unsigned int priorities[5] = { 2, 4, 3, 1, 0 };

	for (int i = 0; i < 5; i++)
	{
		enqueue(names[i], priorities[i]);
	}

	printf("LIST\n");
	pQueue* posPtr = &QUEUE;
	for (int i = 0; i < 5; i++)
	{
		printf("name: %s, priority: %i\n", posPtr->name, posPtr->priority);
		if (posPtr->next != NULL)
		{
			posPtr = posPtr->next;
		}
	}

	printf("\npeek: %s\n", peek());
	dequeue();
	printf("poped\n");


	printf("\nLIST\n");
	posPtr = &QUEUE;
	for (int i = 0; i < 4; i++)
	{
		printf("name: %s, priority: %i\n", posPtr->name, posPtr->priority);
		if (posPtr->next != NULL)
		{
			posPtr = posPtr->next;
		}
	}

	printf("\npeek: %s\n", peek());
}

void enqueue(char* name, unsigned int priority)
{
	// empty queue
	if (strcmp(QUEUE.name, "") == false)
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

char* peek(void)
{
	if (QUEUE.next != NULL)
	{
		return QUEUE.next->name;
	}
	return NULL;
}

void dequeue(void)
{
	// if no QUEUE.next - delete current QUEUE.name
	if (QUEUE.next == NULL)
	{
		strcpy_s(QUEUE.name, strlen("") + 1, "");
	}
	else
	{
		// delete node
		pQueue* tmpPtr = QUEUE.next;

		strcpy_s(QUEUE.name, strlen(QUEUE.next->name)+1, QUEUE.next->name);
		QUEUE.priority = QUEUE.next->priority;
		QUEUE.next = QUEUE.next->next;

		free(tmpPtr);
	}
}