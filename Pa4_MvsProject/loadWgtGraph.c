#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adjWgtVec.h"//adWgtVec.h instead when its done
#include "loadWgtGraph.h"
/*
loadGraph.c
Ben Donn
bdonn
pa4
ToDo: replace AdjWgtVec type with AdjWgtVecNode type
*/
int globalEdgeCount = 0;
/*

int** makeAdjMatrix(AdjWgtVec *adjList, int nodeCount)
{
	int** adjMatrix = calloc(nodeCount, sizeof(int *));
	int dataValue = 0;
	for (int i = 0; i <= nodeCount; i++)
		adjMatrix[i] = calloc(nodeCount, sizeof(int));

	for (int i = 1; i <= nodeCount; i++)//for each node. i.e. each index of array.
	{
		for (int j = 1; j <= nodeCount; j++) //for each node that adjList[i] could have an edge to.
		{
			for (int z = 0; z < intSize(adjList[i]); z++) //for each element in adjList[i]->data
			{
				dataValue = intData(adjList[i], z);
				if (dataValue == j)//if adjList[i] has edge to adjList[j]
				{
					adjMatrix[i][j] = 1;
				}
				else if(adjMatrix[i][j] != 1)
				{
					adjMatrix[i][j] = 0;
				}
			}
		}
	}
	return adjMatrix;
}
*/


/*
AdjWgtVec* transposeGraph(AdjWgtVec* adjList, int n)
{
	int data = 0;
	AdjWgtVec* transposedList = calloc(n+1, sizeof(AdjWgtVec));
	for (int i = 0; i <= n; i++) //initialize a new array of vectors.
	{
		transposedList[i] = intMakeEmptyVec();
	}

	for (int i = 1; i <= n; i++)//traverse through adjList data
	{
		for (int j = 0; j < intSize(adjList[i]); j++)//for each element in adjList[i]->data
		{
			data = intData(adjList[i], j);
			if(data >=0) //added to avoid bad number
				intVecPush(transposedList[data], i);//transpose from adjList to new vector array.
		}
	}
	return transposedList;
}
*/

void printAdjVerts(AdjWgtVec *adjList, int nodeCount)
{
	int n = nodeCount, m = 0;
	int debug = 0;
	AdjWgt data;

	m = getEdgeCount(adjList);

	fprintf(stdout, "nodeCount = %d\nedgeCount = %d\n\n", n, m);
	for (int w = 1; w <= n; w++) //for each node
	{
		fprintf(stdout, "%d  [", (w));
		for (int u = 0; u < adjWgtSize(adjList[w]); u++) //for each edge from that node
		{
			data = adjWgtData(adjList[w], u);

			//if (data < 0)//this might mess up alignment
				//fprintf(stdout, "%d", (int*)data);//maybe-------------------------
			//else
				fprintf(stdout, "%d", data.to);
			if (u < adjWgtSize(adjList[w]) - 1) //if its not the last element
					fprintf(stdout, ", ");
			
		}
		fprintf(stdout, "]\n");
	}
	fprintf(stdout, "\n");
}
/*
void printAdjMatrix(int** adjMatrix, int nodeCount)
{
	fprintf(stdout, "Matrix:\n");
	fprintf(stdout, "     ");
	for (int i = 1; i <= nodeCount; i++)
	{
		fprintf(stdout, "%d  ", i);
	}
	fprintf(stdout, "\n");
	for (int i = 1; i <= nodeCount; i++) //for each adjList[i]
	{
		fprintf(stdout, "\n%d :  ", i);
		for (int j = 1; j <= nodeCount; j++) //for each potential edge
		{
			if(adjMatrix[i][j] == 0 || adjMatrix[i][j] == 1)//needed in case where intSize(vector) == 0
				fprintf(stdout, "%d  ", adjMatrix[i][j]);
			else
				fprintf(stdout, "0  ");
		}
	}
	fprintf(stdout, "\n\n");
}
*/


/*
The below function callocs an array of vectors and fills it based on inputFile
	then returns a pointer to the array.
*/
AdjWgtVec* loadGraph(FILE *inputFile, int nodeCount, char* flag)
{
	//local variables
	int tempInt = 0, dataValue = 0, equal = 0;
	double weight = 0.00;
	AdjWgtVec *tempList = NULL;
	char *lineOfFile, *tempToken,
		*tempDataValue, *tempWeight;
	AdjWgt tempWgt, tempWgt2;
	//begin the calloc's-------------------------------------------------
	lineOfFile = calloc(30, sizeof(char));
	tempToken = calloc(30, sizeof(char));
	tempDataValue = calloc(30, sizeof(char));
	tempWeight = calloc(15, sizeof(char));

	
	tempList = calloc(nodeCount + 1, sizeof(AdjWgtVec));
	for (int i = 0; i <= nodeCount; i++)
		tempList[i] = adjWgtMakeEmptyVec();
	//below is some input file cleanup
	for (int i = 0; i < 1; i++)
		fgets(lineOfFile, 20, inputFile);
	while ((fgets(lineOfFile, 20, inputFile) != NULL)) //for each line of the file.
	{
		if (lineOfFile[0] == '\n') //if fgets needed to clear newline character
			fgets(lineOfFile, 20, inputFile);
		sscanf(lineOfFile, "%s %s %s", tempToken, tempDataValue, tempWeight);

		tempInt = (int)tempToken[0] - (int)'0';
		dataValue = (int)tempDataValue[0] - (int)'0';
		if (!((double)tempWeight[0] == 0.00))
			weight = (double)tempWeight[0] - (double)'0';

		tempWgt.to = dataValue;
		tempWgt.wgt = weight;

		adjWgtVecPush(tempList[tempInt], tempWgt);//dataValue);
			globalEdgeCount++;
			equal = strcmp(flag, "-P");//if primm's algorithm, load undirected.
			if (equal == 0) 
			{
				tempWgt2.to = tempInt;
				tempWgt2.wgt = weight;

				adjWgtVecPush(tempList[dataValue], tempWgt2);
				globalEdgeCount++;
			}
	}
	return tempList;
}

int getNodeCount(FILE *inputFile) //Only call once or there might be errors.
{
	int temp = 0;
	char tempString[5];
	fgets(tempString, 2, inputFile);
	
	return (int)((int)tempString[0] - (int)'0'); //convert string to int.
}

int getEdgeCount(AdjWgtVec *adjList) //Can call multiple times.
{
	return globalEdgeCount;
	/*
	fprintf(stdout, "congrats, made it to getEdgeCount\n");
	int n = 0, m = 0;
	n = sizeof(adjList) / sizeof(AdjWgtVec); //no it doesnt.
	n -= 1;
	for (int i = 0; i < n; i++)
		m += intSize(adjList[i]);
	return m;
	*/
}