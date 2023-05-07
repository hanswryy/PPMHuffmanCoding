#include "header.h"

int isEmpty(struct PriorityQueue *q)
{
	if (q->size == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int isSize(struct PriorityQueue *q)
{
	return q->size;
}

void swap(int *xp, int *yp, char *xc, char *yc)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
	
	char simpan = *xc;
	*xc = *yc;
	*yc = simpan;
}