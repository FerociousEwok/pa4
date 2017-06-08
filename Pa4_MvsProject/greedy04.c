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
#include "AdjWgtVec.h"
#include "greedy04.h"
#include "loadWgtGraph.h"



int nodeCount = 0;
/*
//AdjWgtVec finishStk1; should be in dfsTrace1.c struct now
//char *color; should be in dfsTrace1.c struct now


AdjWgtVec* findSCCs(AdjWgtVec *adjList, dfsData dfsInfo)//Todo: 2 things, 2 comments.; Also, dfs1Trace must take parameter roots also.
{
	AdjWgtVec *roots;//where the scc answer will go.
	int tempRoot = -1, newRoot2 = -1;
	AdjWgtVec *adjListT;//transposed
	dfsData dfsInfoT;//transposed
	adjListT = calloc(nodeCount, sizeof(AdjWgtVec));
	dfsInfoT = makeNewDfsDataObj(nodeCount);

	roots = calloc(nodeCount + 1, sizeof(AdjWgtVec));

	
	// Vector should only be made if its a root, handle this in dfsPhase2.c
	for (int i = 1; i <= nodeCount; i++)
	{
		roots[i] = intMakeEmptyVec();
	}
	

	adjListT = transposeGraph(adjList, nodeCount);
	fprintf(stdout, "\n-----Transpose-----\n");
	printAdjVerts(adjListT, nodeCount);
	printAdjMatrix(makeAdjMatrix(adjListT, nodeCount), nodeCount);//formating my be needed in these lines.

	roots = dfsPhase2(adjListT, dfsInfoT);//------Formating probably needed for the below lines----
	
	printDfsData2(dfsInfoT, roots);
	return roots;
}
*/



int updateFringePrim(MinPQ pq, AdjWgtVec myVec, int v)
{
	for (int i = 0; i<adjWgtSize(myVec); i++)//while more edges
	{
		AdjWgt weightInfo = adjWgtData(myVec, i);
		int w = weightInfo.to;
		double newWgt = weightInfo.wgt;
		if (getStatus(pq, w) == UNSEEN)
			insertPQ(pq, w, newWgt, v);
		else if (getStatus(pq, w) == FRINGE)
			if (newWgt < getPriority(pq, w))
				decreaseKey(pq, w, newWgt, v);
		//remAdj = rest(remAdj);//what?
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
		fprintf(stdout, "\nPlease type a file name(Up to 25 characters): ");
		userInput = calloc(25, sizeof(char));
		//userInput = getc(stdin);//thats not how this should work. use scanf
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

	/*
	adjList = loadGraph(inputFile, nodeCount, flag);
	adjMatrix = makeAdjMatrix(adjList, nodeCount);
	printAdjVerts(adjList, nodeCount);
	if (nodeCount <= 20)
		printAdjMatrix(adjMatrix, nodeCount);
	roots1 = calloc(nodeCount + 1, sizeof(AdjWgtVec));
	dfsInfo = makeNewDfsDataObj(nodeCount);
	newRoot = dfsSweepT(dfsInfo);
	while (newRoot != -1)//infinite loop here i think.
	{
		roots1[newRoot] = intMakeEmptyVec();
		dfsTrace1(adjList, newRoot, dfsInfo, roots1, newRoot);//dfs starting at node newRoot
		newRoot = dfsSweepT(dfsInfo);
	}
	printDfsData(dfsInfo);
	fprintf(stdout, "\nFSTK: ");
	//while (intSize(getFinishStk(dfsInfo)) != 0)
	for(int i = 0; i< intSize(*getFinishStk(dfsInfo)); i++)//added star6/5:0352pm
	{
		fprintf(stdout, "%d  ", intData(*getFinishStk(dfsInfo), i));//added star^
	}
	fprintf(stdout, "\n");
	sccList = calloc(nodeCount, sizeof(AdjWgtVec));
	sccList = findSCCs(adjList, dfsInfo);
	fprintf(stdout, "Program completed with no errors, Press any key to exit: ");
	getc(stdin);
	return EXIT_SUCCESS;
	*/