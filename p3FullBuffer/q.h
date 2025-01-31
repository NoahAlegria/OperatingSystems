#ifndef Q_H
#define Q_H
#include <stdlib.h>
#include <stdio.h>
#include "tcb.h"

/*typedef struct TCB_t
{
	struct Item *next;
	struct Item *prev;
	int val;
};
*/

struct TCB_t * newItem()
{
	struct TCB_t *newItem;
	newItem = (struct TCB_t*)malloc(sizeof(struct TCB_t));
	newItem->next = NULL;
	newItem->prev = NULL;
	//newItem->val = -1;
	return newItem;
}

void initQueue(struct TCB_t ** qHead)
{
	(*qHead)->next = (*qHead);
	(*qHead)->prev = (*qHead);
	(*qHead)->size = 0;
}

void addQueue(struct TCB_t **headNode, struct TCB_t *item)
{

	if ((*headNode)->size == 0)
	{
		item->next = item->prev = item;
		item->size = 1;
		(*headNode) = item;
		(*headNode)->size = 1;
	}
	else
	{
		struct TCB_t *itty = (*headNode)->prev;
		item->next = (*headNode);
		(*headNode)->prev = item;
		item->prev = itty;
		itty->next = item;
		itty->size = 1;
		item->size = 1;
	}
}


struct TCB_t * deleteQueue(struct TCB_t **headNode)
{

	struct TCB_t * retItem = (*headNode);
	struct TCB_t *temp = (*headNode)->prev;
	temp->next = (*headNode)->next;
	//temp->prev = (*headNode)->prev->next;
	(*headNode)->next->prev = temp;
	(*headNode) = (*headNode)->next; //this was temp->next before and WORKED
	return retItem;  //not sure about this return 
}

void rotateQueue(struct TCB_t **headNode) 
{
	addQueue(headNode, deleteQueue(headNode));
}

void printQueue(struct TCB_t *headNode)
{
	struct TCB_t *printItty = headNode;

	while (printItty->next != headNode)
	{
		printf("%d \n", printItty->val);
		printItty = printItty->next;
	}
	printf("%d \n", printItty->val);
}
#endif
