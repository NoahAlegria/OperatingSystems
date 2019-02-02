#include <stdio.h>
#include "threads.h"
#include <unistd.h>

int x = 0;
double y = 1;
int count = 0;
int w = 1;
void generic_even_counter()
{
	while(1)
	{
		x++;
		if (x % 2 == 0)
		{
			printf("Levels Rising \n");
		}
		else
		{
			printf("Getting Higher \n");
		}
		sleep(1);
		yield();
	}
}

void give_meaningless_values()
{
	while(1)
	{
		y = (y *.0078) + y;
		printf("Your Current Wait Time Is: %lf \n", y);
		sleep(1);
		yield();	
	}
}

void printw()
{
	while(1)
	{
		w += w;
		printf("Current Anger Level: %d \n" , w);
		if (w == -2147483648)
		{
			w = 1;
			printf("\n\n\nAnger Cap Reached, Do It Again! \n\n\n\n");
		}
		sleep(1);
		yield();
	}
}

void countFast()
{
	while(1)
	{
		count++;
		printf("Current Count: %d \n", count);
		sleep(1);
		yield();
	}
}
int main()
{
	RunQ = (struct TCB_t*)malloc(sizeof(struct TCB_t));
	initQueue(&RunQ);
	start_thread(give_meaningless_values);
	start_thread(printw);
	//start_thread(generic_even_counter);
	//start_thread(countFast);
	run();
}
