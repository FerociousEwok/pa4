/*
adjWgtVec.c
Ben Donn
bdonn
pa4
*/
#include "adjWgtVec.h"
#include <stdlib.h>
#include <stdio.h>



typedef struct AdjWgtVecNode
{
	AdjWgt *data;
	int sz;
	int capacity;
}AdjWgtVecNode;


typedef struct AdjWgtVecNode * AdjWgtVec;



AdjWgt adjWgtTop(AdjWgtVec myVec)
{
	if (myVec->capacity == 0)
		exit(EXIT_FAILURE);
	return myVec->data[(myVec->sz) - 1];
}

AdjWgt adjWgtData(AdjWgtVec myVec, int i)
{
	if (!(i >= 0 && i < myVec->sz))
		exit(EXIT_FAILURE);
	return myVec->data[i];
}

int adjWgtSize(AdjWgtVec myVec)
{
	if (myVec == NULL)
		exit(EXIT_FAILURE);
	return myVec->sz;
}

int adjWgtCapacity(AdjWgtVec myVec)
{
	if (myVec == NULL)
		exit(EXIT_FAILURE);
	return myVec->capacity;
}

AdjWgtVec adjWgtMakeEmptyVec(void)
{
	AdjWgtVec newVec = calloc(1, sizeof(struct AdjWgtVecNode));
	newVec->data = calloc(adjWgtInitCap, sizeof(AdjWgt));
	for (int i = 0; i < adjWgtInitCap; i++)
	{
		newVec->data[i].to = -1;
		newVec->data[i].wgt = -1;
	}
	newVec->sz = 0;
	newVec->capacity = adjWgtInitCap;
	return newVec;
}

void adjWgtVecPush(AdjWgtVec myVec, AdjWgt newE)
{
	if (myVec == NULL) //if precondition fails.
	{
		fprintf(stderr, "Error: myVec == NULL");
		exit(EXIT_FAILURE);
	}
	//replacing 
	if (adjWgtSize(myVec) == adjWgtCapacity(myVec))
	{
		myVec->data = (struct AdjWgtStruct*)realloc(myVec->data, (sizeof(struct AdjWgtStruct) * (adjWgtSize(myVec)) * 2));
		if (myVec->data == NULL) //if realloc failed.
		{
			fprintf(stderr, "Error: realloc failed");
			exit(EXIT_FAILURE);
		}
		myVec->capacity = (adjWgtCapacity(myVec)) * 2;
	}

	myVec->data[adjWgtSize(myVec)] = newE;

	//postconditions
	myVec->sz = (adjWgtSize(myVec)) + 1;
	return;
}

void adjWgtVecPop(AdjWgtVec myVec)
{
	if (myVec == NULL) //if precondition fails.
	{
		fprintf(stderr, "Error: myVec not constructed");
		exit(0);
	}
	myVec->data[(adjWgtSize(myVec) - 1)].to = -1;
	myVec->data[(adjWgtSize(myVec) - 1)].wgt = -1;
	myVec->sz = (adjWgtSize(myVec)) - 1;
	return;
}

