/*
loadGraph.h
Ben Donn
bdonn
pa3
*/


/*
int** makeAdjMatrix(AdjWgtVec *adjList, int nodeCount);
*/


/*
AdjWgtVec* transposeGraph(AdjWgtVec *adjList, int n);
*/


/*

*/
void printAdjVerts(AdjWgtVec *adjList, int nodeCount);

/*
void printAdjMatrix(int **adjMatrix, int nodeCount);
*/


/*

*/

AdjWgtVec* loadGraph(FILE *inputFile, int nodeCount, char *flag);

/*

*/
int getNodeCount(FILE *inputFile);

/*

*/
int getEdgeCount(AdjWgtVec *adjList);