#include "q.h"
int main()
{
	struct TCB_t *head = (struct TCB_t*)malloc(sizeof(struct TCB_t));
	initQueue(&head);
	int i;

	struct TCB_t *item;

	for (i = 0; i < 10; i++)
	{
		item = newItem();
		item->val = i;
		addQueue(&head, item);
	}
	printQueue(head);
	//deleteQueue(&head);

	for (i = 0; i < 5; i++)
	{
		item = deleteQueue(&head);
		printf("%d \n", item->val);
	}

	printf("Last Item Before: %d \n", head->prev->val);
	rotateQueue(&head);
	printf("Last Item After: %d \n", head->prev->val);

	printf("Last Item Before: %d \n", head->prev->val);
	rotateQueue(&head);
	printf("Last Item After: %d \n", head->prev->val);
	
	printf("Last Item Before: %d \n", head->prev->val);
	rotateQueue(&head);
	printf("Last Item After: %d \n", head->prev->val);
	//item = deleteQueue(&head);
	//printf("%d \n", item->val);
}
