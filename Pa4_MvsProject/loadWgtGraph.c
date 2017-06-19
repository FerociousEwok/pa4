/*
loadWgtGraph.c
Ben Donn
bdonn
pa4
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adjWgtVec.h"
#include "loadWgtGraph.h"

int globalEdgeCount = 0;


void printAdjVerts(AdjWgtVec *adjList, int nodeCount)
{
	int n = nodeCount, m = 0;
	int debug = 0;
	AdjWgt data;

	m = getEdgeCount(adjList);

	fprintf(stdout, "nodeCount = %d\nedgeCount = %d\n\n", n, m);
	for (int w = 1; w <= n; w++) //for each node
	{
		fprintf(stdout, " %2d  [", (w));
		for (int u = 0; u < adjWgtSize(adjList[w]); u++) //for each edge from that node
		{
			data = adjWgtData(adjList[w], u);
			fprintf(stdout, "%2d", data.to);
			if (u < adjWgtSize(adjList[w]) - 1) //if its not the last element
				fprintf(stdout, ", ");
		}
		fprintf(stdout, "]\n");
	}
	fprintf(stdout, "\n");
}


/*
The below function callocs an array of vectors and fills it based on inputFile
	then returns a pointer to the array.
*/
AdjWgtVec* loadGraph(FILE *inputFile, int nodeCount, char* flag)
{
	//local variables
	int *tempInt = 0, *dataValue = 0, equal = 0;
	float* weight = calloc(1, sizeof(float));
	AdjWgtVec *tempList = NULL;
	char *lineOfFile;
	AdjWgt tempWgt, tempWgt2;
	//begin the calloc's-------------------------------------------------
	lineOfFile = calloc(30, sizeof(char));
	tempInt = calloc(1, sizeof(int));
	dataValue = calloc(1, sizeof(int));
	weight = calloc(1, sizeof(float));
	
	
	tempList = calloc(nodeCount + 1, sizeof(AdjWgtVec));
	for (int i = 0; i <= nodeCount; i++)
		tempList[i] = adjWgtMakeEmptyVec();
	
	while ((fgets(lineOfFile, 20, inputFile) != NULL)) //for each line of the file.
	{
		if (lineOfFile[0] == '\n') //if fgets needed to clear newline character
			fgets(lineOfFile, 20, inputFile);
		sscanf(lineOfFile, "%d %d %f", tempInt, dataValue, weight);
		
		tempWgt.to = *dataValue;
		tempWgt.wgt = *weight;

		adjWgtVecPush(tempList[*tempInt], tempWgt);//dataValue);
			globalEdgeCount++;
			equal = strcmp(flag, "-P");//if primm's algorithm, load undirected.
			if (equal == 0) 
			{
				tempWgt2.to = *tempInt;
				tempWgt2.wgt = *weight;

				adjWgtVecPush(tempList[*dataValue], tempWgt2);
				globalEdgeCount++;
			}
	}
	return tempList;
}

int getNodeCount(FILE *inputFile) 
{
	int temp = 0;
	char *tempString = calloc(5, sizeof(char));
	fgets(tempString, 5, inputFile);
	temp = atoi(tempString);
	
	return temp;
}

int getEdgeCount(AdjWgtVec *adjList) //Can call multiple times.
{
	return globalEdgeCount;
}