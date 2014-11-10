/***
* Assignemnt3.h 
* assignment #3 (Graph)
* Author: Ildar Nurgaliev
*
* Test cases in input.txt with reponse in output.txt:
*   1) test from asignment's list
*   Scenario #1
*   Minimum Number of Trips = 5
*   Route = 1 2 4 7
*   
*   2) the same as the 1st test for checking pureness of algorithm
*   Scenario #2
*   Minimum Number of Trips = 5
*   Route = 1 2 4 7
*   
*   3) the same as the 1st test instead of  changed edge 1 2 30 to 1 2 5
*   Scenario #3
*   Minimum Number of Trips = 8
*   Route = 1 3 6 7
*   
*   4) tabs and spaces between datas
*   Scenario #4
*   Minimum Number of Trips = 5
*   Route = 1 2 4 7
*   
*   5) N = 0 with passegers count = 55
*   Scenario #5
*   Minimum Number of Trips = 0
*   Route = -

*   6) the same as the 1st test but with permutation in edges list
*   Scenario #6
*   Minimum Number of Trips = 5
*   Route = 1 2 4 7   
*
*   7) 2 nodes, 1 2 10, need 30 passegers passed with Mr. G.
*   Scenario #7
*   Minimum Number of Trips = 4
*   Route = 2 1
*
****/

#include <stdlib.h>
#include <stdio.h>

#define AUTHOR_NAME "Ildar Nurgaliev"

/* relative path to input and output files in build directory */
#define input_file_name "input.txt"
#define output_file_name "output.txt"

#define CITY_COUNT_MIN    1 /* min restriction for city count */
#define MAX_VAL 99999999 /* possible max weight in Graph */
/* error messages */
#define MSG_ERR_INVALID_INPUT_STRUCTURE "Invalid input structure of the input file."
#define MSG_ERR_FILE_NOT_OPEN "File cannot be openned."

/* output patterns */
#define p_scenario     "Scenario #%d\n"
#define p_number_trips "Minimum Number of Trips = %d\n"
#define p_route        "Route ="
#define p_route_none        "Route = -\n\n"

#define FALSE 0
#define TRUE 1

/*-------------------------------------------------
* Types for Graph                                                                
* Directed edge (x, y) is represented by edgenode y in x’s        
* adjacency list. Vertices are numbered 1 .. MAXV    
*/ 

#define MAXV 1000  /* maximum number of vertices  */
typedef int boolean;
typedef struct edge{
    int y;                        /* adjacent vertex number          */  
	int weight;                   /* edge weight, if any             */  
	struct edge* next;        /* next edge in list               */ 
} Edgenode;

typedef struct graph{       
	Edgenode* edges[MAXV+1]; /* adjacency info: list of edges   */     
	int degree[MAXV+1];      /* number of edges for each vertex */   
	int nvertices;           /* number of vertices in graph     */  
	int nedges;              /* number of edges in graph        */ 
	boolean directed;           /* is the graph directed?          */ 
} Graph;

/*-------------------------------------
* Assignment3 interface
*/
void reverse_and_print_path(int); /*  */
void init(int);  /* init push, pred and mark */
void bfs_max_wide(Graph*, int, int); /* BFS with passegers restriction rule */
int ceil_up(double p);  /* round double to upper int */
void error(const char*); /* programm error logger */

/*--------------------------------------
* Graph interface
*/
void initialize_graph(Graph*, boolean); /* Initialize graph from data in a file */ 
void print_graph(Graph*); /* Print a graph */
void insert_edge(Graph*, int, int, int, boolean); /* Initialize graph from data in a file */
Graph* read_graph(Graph*, int, int, boolean, FILE*); /* Initialize graph from data in a file */

/*--------------------------------------
* Types for Queue
*/
typedef int VALUE_TYPE;
typedef struct {
	VALUE_TYPE value;
} ELEMENT_TYPE;

typedef struct node *NODE_TYPE;
typedef struct node{
	ELEMENT_TYPE element;
	NODE_TYPE next;
} NODE;

//NODE_TYPE is a pointer to struct node
typedef NODE_TYPE LIST_TYPE;
typedef NODE_TYPE WINDOW_TYPE;

/*-------------------------------------
* Queue interface
*/
WINDOW_TYPE declare(LIST_TYPE*);
WINDOW_TYPE empty(LIST_TYPE*);
ELEMENT_TYPE head(LIST_TYPE*);
LIST_TYPE* enqueue(ELEMENT_TYPE, LIST_TYPE*); 
ELEMENT_TYPE dequeque(LIST_TYPE*);
int is_empty(LIST_TYPE*);
void print(LIST_TYPE*);
int assign_element_values(ELEMENT_TYPE*, VALUE_TYPE);
int size(LIST_TYPE*);