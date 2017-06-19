/* minPQ.h (This file impliments a Priority Queue adt.)
* Ben Donn
* pa4
*/

#ifndef C101MinPQ
#define C101MinPQ
/* Multiple typedefs for the same type are an error in C. */

typedef struct minPQNode //nodeObj minPQ is pointer to that Obj
{
	int numVertices, numPQ;
	int minVertex;
	double infinity;
	int* status, *parent;
	double* priority;

}minPQNode;
typedef struct minPQNode * MinPQ;

#define UNSEEN ('u')
#define FRINGE ('f')
#define INTREE ('t')

/* ***************** Access functions */


int isEmptyPQ(MinPQ pq); //precondition is pq no being null.

/** getMin (//precondition is pq not being null.)
*/
int getMin(MinPQ pq);

/** getStatus (//precondition is pq not build null and id being in between 1 and nodeCount+1)
*/
int getStatus(MinPQ pq, int id);

/** getParent (//precondition is pq not being null and id being in between 1 and nodeCount+1)
*/
int getParent(MinPQ pq, int id);

/** getPriority (//precondition is pq not being null and id being in range.)
*/
double getPriority(MinPQ pq, int id);


/* ***************** Manipulation procedures */

/** delMin (//precondition pq not null.)
*/
void delMin(MinPQ pq);

/** insertPQ (//precondition pq not null and id/priority/par are not invalid values.)
*/
void insertPQ(MinPQ pq, int id, double priority, int par);

/** decreaseKey (//precondition pq not null and id/priority/par not invalid values.)
*/
void decreaseKey(MinPQ pq, int id, double priority, int par);


/* ***************** Constructors */

/** createPQ (//precondition pq not null and id/priority/par not invalid values.)
*/
MinPQ createPQ(int n, int status[], double priority[], int parent[]);


#endif

