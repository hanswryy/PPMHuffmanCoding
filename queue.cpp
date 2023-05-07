#include "header.h"

// Returns a new queue 
struct PriorityQueue *newPriorityQueue()
{
	struct PriorityQueue *q = (struct PriorityQueue *) malloc(sizeof(struct PriorityQueue));
	if (q == NULL)
	{
		printf("\n Memory overflow , When creating a new Queue");
	}
	else
	{
		q->front = NULL;
		q->rear = NULL;
		q->size = 0;
	}
	return q;
}

// Add a node into Priority queue
void enQueue(struct PriorityQueue *q, struct TreeNode *auxiliary)
{
	//Create a dynamic node
	struct QNode *node = (struct QNode *) malloc(sizeof(struct QNode));
	if (node == NULL)
	{
		printf("\n Memory overflow , When creating a new Queue Node");
	}
	else
	{
		// Set node value
		node->n = auxiliary;
		node->next = NULL;
		node->prev = NULL;
		if (q->front == NULL)
		{
			// When adding a first node of queue
			q->front = node;
			q->rear = node;
		}
		else if (q->front->n->freq > auxiliary->freq)
		{
			// Add node at beginning position
			node->next = q->front;
			q->front->prev = node;
			q->front = node;
		}
		else if (q->rear->n->freq <= auxiliary->freq)
		{
			// Add node at last position
			node->prev = q->rear;
			q->rear->next = node;
			q->rear = node;
		}
		else
		{
			struct QNode *temp = q->front;
			// Find the location of inserting priority node
			while (temp->n->freq <= auxiliary->freq)
			{
				temp = temp->next;
			}
			// Add node
			node->next = temp;
			node->prev = temp->prev;
			temp->prev = node;
			if (node->prev != NULL)
			{
				node->prev->next = node;
			}
		}
		q->size = q->size + 1;
	}
}

// Remove a front node of a queue
void deQueue(struct PriorityQueue *q)
{
	if (isEmpty(q) == 0)
	{
		struct QNode *temp = q->front;
		q->front->n = NULL;
		if (q->front == q->rear)
		{
			// When queue contains only one node
			q->rear = NULL;
			q->front = NULL;
		}
		else
		{
			q->front = q->front->next;
			q->front->prev = NULL;
		}
		// Change queue size
		q->size--;
		free(temp);
	}
	else
	{
		printf("\n Empty Queue \n");
	}
}
