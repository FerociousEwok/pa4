/* minPQ.h (This file impliments a Priority Queue adt.)
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

/** getMin (what are the preconditions, if any? Replace this question with your comments.)
*/
int getMin(MinPQ pq);//precondition is pq not being null.

/** getStatus (what are the preconditions, if any? Replace this question with your comments.)
*/
int getStatus(MinPQ pq, int id);//precondition is pq not build null and id being in between 1 and nodeCount+1

/** getParent (what are the preconditions, if any? Replace this question with your comments.)
*/
int getParent(MinPQ pq, int id);//precondition is pq not being null and id being in between 1 and nodeCount+1

/** getPriority (what are the preconditions, if any? Replace this question with your comments.)
*/
double getPriority(MinPQ pq, int id);//precondition is pq not being null and id being in range.


/* ***************** Manipulation procedures */

/** delMin (what are the preconditions and/or postconditions? Replace this question with your comment.)
*/
void delMin(MinPQ pq);//precondition pq not null.

/** insertPQ (what are the preconditions and/or postconditions? Replace this question with your comment.)
*/
void insertPQ(MinPQ pq, int id, double priority, int par);//precondition pq not null and id/priority/par are not invalid values.

/** decreaseKey (what are the preconditions and/or postconditions? Replace this question with your comment.)
*/
void decreaseKey(MinPQ pq, int id, double priority, int par);//precondition pq not null and id/priority/par not invalid values.


/* ***************** Constructors */

/** createPQ (what are the preconditions and/or postconditions? Replace this question with your comment.)
*/
MinPQ createPQ(int n, int status[], double priority[], int parent[]);//precondition pq not null and id/priority/par not invalid values.


#endif

