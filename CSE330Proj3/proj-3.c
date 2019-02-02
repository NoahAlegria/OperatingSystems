/*
  Solution to Reader-Writer problem
  Noah Alegria
  ID: 1210011306
*/

#include "sem.h"
#include <unistd.h>

//forward declarations

int buffer[3] = {1, 2, 3};
int rc, wc, rwc, wwc;
struct Sem *rsem, *wsem, *mutex;


void write1()
{
	while(1)
	{
		P(mutex);
		if (rc > 0 || wc > 0)
		{
			printf("Writer 1 is waiting due to: rc=%d, wc=%d\n", rc, wc);
			wwc++;
			V(mutex);
			P(wsem);
			wwc--;
		}
		wc++;
		sleep(1);
		V(mutex);

		printf("Writer 1 enters the CS\n");
		for (int i = 0; i < 3; i++) {
			buffer[i] = buffer[i] * 2;
		}

		printf("Writer 1 writes: %d %d %d\n", buffer[0], buffer[1], buffer[2]);
		P(mutex);
		wc--;
		printf("Writer 1 is exiting\n");
		if (rwc > 0)
			V(rsem);
		else if (wwc > 0)
			V(wsem);
		else
			V(mutex);
		sleep(1);
	}
}

void write2()
{
	while(1)
	{
		P(mutex);
		if (rc > 0 || wc > 0)
		{
			printf("Writer 2 is waiting due to: rc=%d, wc=%d\n", rc, wc);
			wwc++;
			V(mutex);
			P(wsem);
			wwc--;
		}
		wc++;
		sleep(1);
		V(mutex);

		printf("Writer 2 enters the CS\n");
		for (int i = 0; i < 3; i++) {
			buffer[i] = buffer[i] * 2;
		}
		printf("Writer 2 writes: %d %d %d\n", buffer[0], buffer[1], buffer[2]);
		P(mutex);
		wc--;
		printf("Writer 2 is exiting\n");
		if (rwc > 0)
			V(rsem);
		else if (wwc > 0)
			V(wsem);
		else
			V(mutex);
		sleep(1);
	}
}

void read1()
{
	while(1)
	{
		P(mutex);
		if (wc > 0 || wwc > 0)
		{
			printf("Reader 1 is waiting due to wc=%d, wwc=%d\n", wc, wwc);
			rwc++;
			sleep(1);
			V(mutex);
			P(rsem);
			rwc--;
		}
		rc++;
		if (rwc > 0)
			V(rsem);
		else
			V(mutex);

		printf("Reader 1 reads the buffer: %d %d %d\n", buffer[0], buffer[1], buffer[2]);
		P(mutex);
		rc--;
		printf("Reader 1 is exiting\n");
		if (rc == 0 && wwc > 0)
			V(wsem);
		else
			V(mutex);
		sleep(1);
	}
}

void read2()
{
	while(1)
	{
		P(mutex);
		if (wc > 0 || wwc > 0)
		{
			printf("Reader 2 is waiting due to wc=%d, wwc=%d\n", wc, wwc);
			rwc++;
			sleep(1);
			V(mutex);
			P(rsem);
			rwc--;
		}
		rc++;
		if (rwc > 0)
			V(rsem);
		else
			V(mutex);

		printf("Reader 2 reads the buffer: %d %d %d\n", buffer[0], buffer[1], buffer[2]);
		P(mutex);
		rc--;
		printf("Reader 2 is exiting\n");
		if (rc == 0 && wwc > 0)
			V(wsem);
		else
			V(mutex);
		sleep(1);
	}
}

void read3()
{
	while(1)
	{
		P(mutex);
		if (wc > 0 || wwc > 0)
		{
			printf("Reader 3 is waiting due to wc=%d, wwc=%d\n", wc, wwc);
			rwc++;
			sleep(1);
			V(mutex);
			P(rsem);
			rwc--;
		}
		rc++;
		if (rwc > 0)
			V(rsem);
		else
			V(mutex);

		printf("Reader 3 reads the buffer: %d %d %d\n", buffer[0], buffer[1], buffer[2]);
		P(mutex);
		rc--;
		printf("Reader 3 is exiting\n");
		if (rc == 0 && wwc > 0)
			V(wsem);
		else
			V(mutex);
		sleep(1);
	}
}

int main()
{
	rc = wc = rwc = wwc = 0;

	RunQ = (struct TCB_t*)malloc(sizeof(struct TCB_t)); //begin initializations
	initQueue(&RunQ);

	rsem = (struct Sem*)malloc(sizeof(struct Sem));
	wsem = (struct Sem*)malloc(sizeof(struct Sem));
	mutex = (struct Sem*)malloc(sizeof(struct Sem));
	initSem(rsem, 0);
	initSem(wsem, 0);
	initSem(mutex, 1);
	start_thread(write1);
	start_thread(write2);
	start_thread(read1);
	start_thread(read2);
	start_thread(read3);
	run();
}
