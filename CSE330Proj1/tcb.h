#include <ucontext.h>
#include <string.h>

typedef struct TCB_t
{
	struct TCB_t *next;
	struct TCB_t *prev;
	ucontext_t context;
	int size;
	int val;
} TCB_t;

void init_TCB(TCB_t *tcb, void *func, void *sp, int stack_size)
{
	memset(tcb, '\0', sizeof(TCB_t));
	getcontext(&tcb->context); // pulls context of parent
	
	tcb->context.uc_stack.ss_sp = sp;
	tcb->context.uc_stack.ss_size = (size_t)stack_size;
	makecontext(&tcb->context, func, 0);
}

