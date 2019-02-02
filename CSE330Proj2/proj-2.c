#include <stdio.h>
#include <unistd.h>
#include "sem.h"

int inQ = 0;
int outQ = 0;
int buffer[5];
struct Sem *s;
struct Sem *sp;
struct Sem *sv;

void printStuff(char *string) //atomically prints current execution and buffer
{
	printf("%s\n Buffer:\n %d\n %d\n %d\n %d\n %d\n", string, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
	sleep(1);
	return;
}

void firstProducer() //puts a 1 in the buffer and sends producer signal
{
	while(1)
	{
		P(sp);
		buffer[inQ] = 1;
		inQ = (inQ + 1) % 5;
		printStuff("First Producer");
		V(sv);
	}
	return;
}

void secondProducer()
{
	while(1)
	{
		P(sp);
		buffer[inQ] = 1;
		inQ = inQ % 5;
		printStuff("Second Producer");
		V(sv);
	}
	return;
}

void firstConsumer() //consumes or takes a 1 out of buffer and sends consumer signal
{
	while(1)
	{
		P(sv);
		buffer[outQ] = 0;
		outQ = (outQ + 1) % 5;
		printStuff("First Consumer");
		V(sp);
	}
	return;
}

void secondConsumer()
{
	while(1)
	{
		P(sv);
		buffer[outQ] = 0;
		outQ = (outQ + 1) % 5;
		printStuff("Secocnd Consumer");
		V(sp);
	}
	return;
}

void initBuffer() //set buffer to correct size with initial values all 0
{
	for (int i = 0; i < 5; i++)
	{
		buffer[i] = 0;
	}
	return;
}

int main()
{
	sp = (struct Sem*)malloc(sizeof(struct Sem)); //allocates memory for semaphores
	sv = (struct Sem*)malloc(sizeof(struct Sem));
	RunQ = (struct TCB_t*)malloc(sizeof(struct TCB_t)); // allocates space for head of Q
	initQueue(&RunQ); 
	initSem(sp, 5); //sets first sem to size of buffer
	initSem(sv, 0); //second sem to 0 (simulates consumer at empty buffer)
	initBuffer(); //you know what this does
	//start_thread(firstConsumer);
	start_thread(secondConsumer);
	//start_thread(firstProducer);
	start_thread(secondProducer);
	run();
	return 0;
}
