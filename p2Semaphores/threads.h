#include "q.h"

struct TCB_t *RunQ;

void start_thread(void (*function)(void))
{
	void *sp = (void*)malloc(8192);
	struct TCB_t *tcb = (struct TCB_t*)malloc(sizeof(struct TCB_t));
	init_TCB(tcb, function, sp,  8192);
	addQueue(&RunQ,tcb);
}

void run()
{
	ucontext_t parent;
	getcontext(&parent);
	swapcontext(&parent, &(RunQ->context));
}

void yield() //not good yet (lies)
{
	ucontext_t other = RunQ->context;
	getcontext (&other);
	rotateQueue(&RunQ);
	swapcontext(&(other), &(RunQ->context));
}


