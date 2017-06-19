/*
greedy04.c
Ben Donn
bdonn
pa4
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minPQ.h"
#include "adjWgtVec.h"
#include "greedy04.h"
#include "loadWgtGraph.h"
int nodeCount = 0;

double calcPriority(AdjWgtVec myVec, char *flag, int parent, int i, MinPQ pq)
{
	if (!strcmp(flag, "-P"))//if primms algorithm
	{
		AdjWgt weightInfo = adjWgtData(myVec, i);
		double newWgt = weightInfo.wgt;
		return newWgt;
	}
	else //if dijkstras.
	{
		double myDist = getPriority(pq, parent);
		AdjWgt weightInfo = adjWgtData(myVec, i);
		double newDist = myDist + weightInfo.wgt;
		return newDist;
	}
}
int updateFringe(MinPQ pq, AdjWgtVec myVec, int v, char *flag)
{
	for (int i = 0; i < adjWgtSize(myVec); i++)//while more edges
	{
		/*
		AdjWgt weightInfo = adjWgtData(myVec, i);
		int w = weightInfo.to;
		double newWgt = weightInfo.wgt;
		*/
		int w = adjWgtData(myVec, i).to;

		if (getStatus(pq, w) == UNSEEN)
		{
			insertPQ(pq, w, calcPriority(myVec, flag, v, i, pq), v);
		}
		else
		{
			if (getStatus(pq, w) == FRINGE)
				if (calcPriority(myVec, flag, v, i, pq) < getPriority(pq, w))
					decreaseKey(pq, w, calcPriority(myVec, flag, v, i, pq), v);
		}
	}
	return EXIT_SUCCESS;
}
MinPQ greedytree(AdjWgtVec *adjInfo, int n, int s, int *parent, double *priority, char *flag)
{
    int *status = calloc(n + 1, sizeof(int));
	MinPQ pq = createPQ(n, status, priority, parent);

	insertPQ(pq, s, 0, -1);
	while (!isEmptyPQ(pq))
	{
		int v = getMin(pq);
		delMin(pq);
		updateFringe(pq, adjInfo[v], v, flag);
	}
	return pq;
}



int main(int argc, char **argv)
{
	//variables
	FILE *inputFile = NULL;
	char *tempInputString = "", *readMode = "r+", *flag = "default", *userInput;
	AdjWgtVec *adjList;
	int flagCheckOne = 0, flagCheckTwo = 0, startVertex = 0;
	MinPQ resultPQ;
	int *parent;
	double *priority;
	//Cmd Line: ./greedy04 [-P or -D]  [start vertex]  "filename"
	userInput = calloc(30, sizeof(char));
	//Handle cmd input below--
	if (argc != 4) //no command line argument
	{
		fprintf(stderr, "Error: no command line arguments.\nPress any key to close: ");
		getc(stdin);
		exit(EXIT_FAILURE);
	}
	flag = argv[1];
	startVertex = atoi(argv[2]);
	tempInputString = argv[3];
	if (strcmp(tempInputString, "-") == 0)
	{
		fprintf(stdout, "\nPlease type a file name(Up to 30 characters): ");
		
		
		scanf("%s", userInput);
		tempInputString = userInput;
		fprintf(stdout, "\n");
	}
	inputFile = fopen(tempInputString, readMode);
	if (inputFile == 0)
	{
		fprintf(stderr, "fopen() error\nPress any key to close: ");
		getc(stdin);
		exit(EXIT_FAILURE);
	}
	nodeCount = getNodeCount(inputFile);
	flagCheckOne = strcmp(flag, "-P");
	flagCheckTwo = strcmp(flag, "-D");
	if (flagCheckOne != 0 && flagCheckTwo != 0)//if bad command line input
	{
		fprintf(stderr, "Error reading command line input\nPress any key to close: ");
		getc(stdin);
		exit(EXIT_FAILURE);
	}
	//End of cmd input.---
	adjList = loadGraph(inputFile, nodeCount, flag);
	printAdjVerts(adjList, nodeCount);

	
	parent = calloc(nodeCount+1, sizeof(int));
	priority = calloc(nodeCount+1, sizeof(double));
	//perform algorithm and return result.
	resultPQ = greedytree(adjList, nodeCount, startVertex, parent, priority, flag);
	
	//Print out MinPQ data structure.
	fprintf(stdout, "Starting Vertex == %d\n\n          ", startVertex);
	for (int i = 1; i <= nodeCount; i++)
	{
		fprintf(stdout, "%2d   ", i);
	}
	fprintf(stdout, "\n           ");
	for (int i = 0; i <= nodeCount*5; i++)
	{
		fprintf(stdout, "-");
	}
	fprintf(stdout, "\nStatus:    ");
	for (int i = 1; i <= nodeCount; i++)
	{
		fprintf(stdout, "%c    ", getStatus(resultPQ, i));
	}
	fprintf(stdout, "\nParent:   ");
	for (int i = 1; i <= nodeCount; i++)
	{
		fprintf(stdout, "%2d   ", getParent(resultPQ, i));
	}
	fprintf(stdout, "\nPriority: ");
	for (int i = 1; i <= nodeCount; i++)
	{
		fprintf(stdout, "%.1f  ", getPriority(resultPQ, i));
	}
	fprintf(stdout, "\n");
	//free calloc/malloc calls.
	for (int i = 1; i <= nodeCount; i++)
	{
		free(adjList[i]);
	}
	free(adjList);
	free(userInput);
	free(inputFile);
	free(resultPQ->parent);
	free(resultPQ->status);
	free(resultPQ->priority);
	printf("\nProgram completed, press any key to exit: ");
	getc(stdin);
	
}
