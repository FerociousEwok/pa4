/*
minPQ.c
Ben Donn
bdonn
pa4
*/
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include "minPQ.h"

MinPQ createPQ(int n, int status[], double priority[], int parent[])
{
	MinPQ tempPQ;
	tempPQ = calloc(1, sizeof(MinPQ));//assuming n is nodeCount;
	


	tempPQ->parent = parent;

	tempPQ->priority = priority;
	tempPQ->status = status;
	for (int i = 1; i <= n; i++)
	{
		tempPQ->status[i] = UNSEEN;
	}
	tempPQ->numVertices = n;
	tempPQ->minVertex = -1;
	tempPQ->infinity = DBL_MAX;
	tempPQ->numPQ = 0;
	return tempPQ;
}


int isEmptyPQ(MinPQ pq)//returns 1 if empty
{
	if (pq == NULL)
		return 1;
	return (pq->numPQ == 0);
}

int getMin(MinPQ pq)
{
	if (pq == NULL)
		exit(EXIT_FAILURE);

	double minWgt = DBL_MAX;

		for (int v = 1; v <= pq->numVertices; v++)
		{
			if (pq->status[v] == FRINGE)
				if (pq->priority[v] < minWgt)
				{
					pq->minVertex = v;
					minWgt = pq->priority[v];
				}
		}
	return pq->minVertex;
}

int getStatus(MinPQ pq, int id)
{
	if (pq == NULL || id < 0 || id > pq->numVertices)
	{
		return 117;
	}
	return pq->status[id];
}

int getParent(MinPQ pq, int id)
{
	if (pq == NULL)
		exit(EXIT_FAILURE);
	return pq->parent[id];
}

double getPriority(MinPQ pq, int id)
{
	if (pq == NULL)
		exit(EXIT_FAILURE);
	return pq->priority[id];
}

void delMin(MinPQ pq)
{
	if (pq == NULL)
		exit(EXIT_FAILURE);
	int oldMin = getMin(pq);
	pq->status[oldMin] = INTREE;
	pq->minVertex = -1;
	pq->numPQ--;
	return;
}

void insertPQ(MinPQ pq, int id, double priority, int par)
{
	if (pq == NULL || id < 0 || id > pq->numVertices)
	{
		return;
	}

	pq->parent[id] = par;
	pq->priority[id] = priority;
	pq->status[id] = FRINGE;
	pq->minVertex = -1;
	pq->numPQ++;
	return;
}

void decreaseKey(MinPQ pq, int id, double priority, int par)
{
	if (pq == NULL)
		exit(EXIT_FAILURE);
	pq->parent[id] = par;
	pq->priority[id] = priority;
	pq->minVertex = -1;
	return;
}

