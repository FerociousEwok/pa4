/*
greedy04.c
Ben Donn
bdonn
pa3


*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minPQ.h"
#include "adjWgtVec.h"
#include "greedy04.h"
#include "loadWgtGraph.h"
int nodeCount = 0;

int updateFringePrim(MinPQ pq, AdjWgtVec myVec, int v)
{
	for (int i = 0; i < adjWgtSize(myVec); i++)//while more edges
	{
		AdjWgt weightInfo = adjWgtData(myVec, i);
		int w = weightInfo.to;
		double newWgt = weightInfo.wgt;

		if (getStatus(pq, w) == UNSEEN)
		{
			insertPQ(pq, w, newWgt, v);
		}
		else
		{
			if (getStatus(pq, w) == FRINGE)
				if (newWgt < getPriority(pq, w))
					decreaseKey(pq, w, newWgt, v);
		}
	}
	return EXIT_SUCCESS;
}

MinPQ primMST(AdjWgtVec *adjInfo, int n, int s, int *parent, double *priority)
{
	int *status = calloc(n + 1, sizeof(int));
	MinPQ pq = createPQ(n, status, priority, parent);

	insertPQ(pq, s, 0, -1);
	while (!isEmptyPQ(pq))
	{
		int v = getMin(pq);
		delMin(pq);
		updateFringePrim(pq, adjInfo[v], v);
	}
	return pq;
}

int updateFringeDijkstras(MinPQ pq, AdjWgtVec myVec, int v)
{
	double myDist = getPriority(pq, v);
	for (int i = 0; i < adjWgtSize(myVec); i++)
	{
		AdjWgt weightInfo = adjWgtData(myVec, i);
		int w = weightInfo.to;
		double newDist = myDist + weightInfo.wgt;
		
		
		if (getStatus(pq, w) == UNSEEN)
			insertPQ(pq, w, newDist, v);
		else if (getStatus(pq, w) == FRINGE)
			if (newDist < getPriority(pq, w))
				decreaseKey(pq, w, newDist, v);
	}
	return EXIT_SUCCESS;
}

MinPQ dijkstraSSSP(AdjWgtVec *adjInfo, int n, int s, int *parent, double *priority)
{
	int *status = calloc(n + 1, sizeof(int));
	MinPQ pq = createPQ(n, status, priority, parent);
	insertPQ(pq, s, 0, -1);
	while (!isEmptyPQ(pq))
	{
		int v = getMin(pq);
		delMin(pq);
		updateFringeDijkstras(pq, adjInfo[v], v);
	}
	return pq;
}

int main(int argc, char **argv)
{
	//variables
	FILE *inputFile = NULL;
	char *tempInputString = "", *readMode = "r+", *flag = "default", *userInput = "";
	AdjWgtVec *adjList;
	int flagCheckOne = 0, flagCheckTwo = 0, startVertex = 0;
	MinPQ resultPQ;
	int *parent;
	double *priority;
	//Cmd Line: ./greedy04 [-P or -D]  [start vertex]  "filename"

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
		userInput = calloc(30, sizeof(char));
		
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
	adjList = loadGraph(inputFile, nodeCount, flag);
	printAdjVerts(adjList, nodeCount);

	//Now check with algorithm they want and perform it.
	
	parent = calloc(nodeCount+1, sizeof(int));
	priority = calloc(nodeCount+1, sizeof(double));
	if (!strcmp(flag, "-P"))//if primm's algorithm.
	{
		fprintf(stdout, "\n\nPerforming Primm's Algorithm:\n\n");
		resultPQ = primMST(adjList, nodeCount, startVertex, parent, priority);
	}
	else //if dijkstra's algorithm.
	{
		fprintf(stdout, "\n\nPerforming dijkstra's Algorithm:\n\n");
		resultPQ = dijkstraSSSP(adjList, nodeCount, startVertex, parent, priority);
	}
	fprintf(stdout, "Starting Vertex == %d\nStatus: ", startVertex);
	for (int i = 1; i <= nodeCount; i++)
	{
		fprintf(stdout, "%d ", getStatus(resultPQ, i));
	}
	fprintf(stdout, "\nParent: ");
	for (int i = 1; i <= nodeCount; i++)
	{
		fprintf(stdout, "%d ", getParent(resultPQ, i));
	}
	fprintf(stdout, "\nPriority: ");
	for (int i = 1; i <= nodeCount; i++)
	{
		fprintf(stdout, "%f ", getPriority(resultPQ, i));
	}
	fprintf(stdout, "\n");

	getc(stdin);
}