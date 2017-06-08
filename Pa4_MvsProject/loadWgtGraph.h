/*
loadWgtGraph.h
Ben Donn
bdonn
pa4
*/

void printAdjVerts(AdjWgtVec *adjList, int nodeCount);

AdjWgtVec* loadGraph(FILE *inputFile, int nodeCount, char *flag);

int getNodeCount(FILE *inputFile);

int getEdgeCount(AdjWgtVec *adjList);