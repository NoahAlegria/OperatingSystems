#include <stdio.h>
#include "threads.h"

typedef struct Sem 
{
	struct TCB_t *headQueue;
	int value;
} Sem;

void initSem(Sem *s, int initValue) //method to initialize sems to passed value to begin blocks
{
	s->headQueue = (struct TCB_t *)malloc(sizeof(struct TCB_t));
	initQueue(&(s->headQueue));
	s->value = initValue;
	return;
}

void P(Sem *s) //decrement method used for blocking and allowing threads
{ 
	struct TCB_t *temp;
	s->value--; //not sure why this works rather than below code
	if (s->value < 0)
	{
		//printf("BLOCKED HERE\n");
		temp = deleteQueue(&RunQ); //this is the beginning of the block
		addQueue(&(s->headQueue), temp); //blocks whatever is in head of Q of passed sem
		swapcontext(&(temp->context), &(RunQ->context));
	}
	else
	{
		//printf("BLOCKED HERE\n");
		//s->value--; //profs code but doesnt seem to run right
	}
	return;
}

void V(Sem *s)
{
	struct TCB_t *temp;
	s->value++;
	if (s->value <= 0) //if true, go into unblock process
	{
		temp = deleteQueue(&(s->headQueue)); //takes thread out of buffer 
		addQueue(&RunQ, temp); //adds it to current RunQ
	}
	//printf("ALLOW\n");
	yield(); //allow next process 
	return;
}
