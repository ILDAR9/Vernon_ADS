/***
* ADS.c
* Author - Ildar Nurgaliev
*/

#include "Assignment3.h"
/* Linked List interface for Queue */
LIST_TYPE *insert(ELEMENT_TYPE, WINDOW_TYPE, LIST_TYPE*);
WINDOW_TYPE empty(LIST_TYPE*);
WINDOW_TYPE end(LIST_TYPE*);
int is_empty(LIST_TYPE*);
WINDOW_TYPE first(LIST_TYPE*);
WINDOW_TYPE last(LIST_TYPE*);
WINDOW_TYPE next(WINDOW_TYPE, LIST_TYPE*);
WINDOW_TYPE previous(WINDOW_TYPE, LIST_TYPE*);
LIST_TYPE *insert(ELEMENT_TYPE, WINDOW_TYPE, LIST_TYPE*);
LIST_TYPE *delete_item(WINDOW_TYPE, LIST_TYPE*);
ELEMENT_TYPE retrieve(WINDOW_TYPE, LIST_TYPE*);
void print(LIST_TYPE*);
int assign_element_values(ELEMENT_TYPE*, VALUE_TYPE);
WINDOW_TYPE declare(LIST_TYPE*);
int size(LIST_TYPE*);

void initialize_graph(Graph *g, boolean directed){ 
	int i;                          /* counter */
	g -> nvertices = 0;   
    g -> nedges = 0;
	g -> directed = directed;
	for (i=1; i<=MAXV; i++)
		g->degree[i] = 0;
	for (i=1; i<=MAXV; i++)
		g->edges[i] = NULL;
} 

Graph* read_graph(Graph* g, int N, int R, boolean directed, FILE* f_input) {
    
    int i;    /* counter                */
    int c1, c2; /* vertices in edge (x,y) */
    int w; /* weight */    
    initialize_graph(g, directed);
    g->nvertices = N;
    for (i=1; i<=R; i++) {
        fscanf(f_input, "%d %d %d", &c1, &c2, &w);
        insert_edge(g,c1,c2,w,directed);
    }
    return g;
}   

void insert_edge(Graph* g, int x, int y, int w, boolean directed) {   
    Edgenode *p;  /* temporary pointer */
    p = (Edgenode*)malloc(sizeof(Edgenode)); /* allocate edgenode storage */
    p->weight = w;
    p->y = y;
    p->next = g->edges[x];
    g->edges[x] = p;              /* insert at head of list        */
    g->degree[x] ++;
    if (directed == FALSE)        /* NB: if undirected add         */
        insert_edge(g,y,x,w,TRUE);   /* the reverse edge recursively  */
    else                          /* but directed TRUE so we do it */
        g->nedges ++;              /* only once                     */ 
} 

void print_graph(Graph* g) {   
    int i;                             /* counter           */   
    Edgenode *p;                       /* temporary pointer */    
    for (i=1; i<=g->nvertices; i++) {     
        printf("%d: ",i);      
        p = g->edges[i];     
        while (p != NULL) {
            printf(" %d, weight=%d;  ",p->y, p->weight);
            p = p->next;
        }
        printf("\n");
    }
}

/*-----------------------------------
* Queue
*/
ELEMENT_TYPE head(LIST_TYPE *queue){
	return retrieve(first(queue), queue);
}

LIST_TYPE* enqueue(ELEMENT_TYPE e, LIST_TYPE *queue){
	return insert(e, end(queue), queue);
}

ELEMENT_TYPE dequeque(LIST_TYPE *queue){
	ELEMENT_TYPE e;
	e = retrieve(first(queue), queue);
	delete_item(first(queue), queue);
	return e;
}

/*-----------------------------------
* LinkedList
*/

/** position following last element in a list ***/
WINDOW_TYPE end(LIST_TYPE *list) {
	WINDOW_TYPE q;
	q = *list;
	if (q == NULL) {
		error("non-existent list");
	}
	else {
		while (q->next != NULL) {
			q = q->next;
		}
	}
	return(q);
}

/*** create a new empty one with a header node ***/
WINDOW_TYPE declare(LIST_TYPE *list){
	WINDOW_TYPE q;
	if ((q = (NODE_TYPE) malloc(sizeof(NODE))) == NULL)
		error("function empty: unable to allocate memory");
	else {
		q->next = NULL;
		*list = q;
	}
	return(end(list));
}

/*** empty a list ***/
WINDOW_TYPE empty(LIST_TYPE *list) {
	WINDOW_TYPE p, q;

	if	(&list != NULL) {
		/* list exists: delete all nodes including header */
		q = *list;
		while (q->next != NULL) {
			p = q;
			q = q->next;
			free(p);
		}
		free(q);
	}

	/* now, create a new empty one with a header node */
	return (declare(list));
}

/*** test to see if a list is empty ***/
int is_empty(LIST_TYPE *list) {
	WINDOW_TYPE q;
	q = *list;
	if (q == NULL) {
		error("non-existent list");
	}
	else {
		if (q->next == NULL) {
			return(TRUE);
		} else{
			return(FALSE);
		}
	}
}

/*** position at first element in a list ***/
WINDOW_TYPE first(LIST_TYPE *list) {
	if (is_empty(list) == FALSE) {
		return(*list);
	} else {
		return(end(list));
	}
}

/*** position at next element in a list ***/
WINDOW_TYPE next(WINDOW_TYPE w, LIST_TYPE *list) {
	if (w == (WINDOW_TYPE)last(list)) {
		return(end(list));
	} else if (w == end(list)) {
		error("can’t find next after end of list");
	} else {
		return(w->next);
	}
}


/*** position at previous element in a list ***/
WINDOW_TYPE previous(WINDOW_TYPE w, LIST_TYPE *list) {
	WINDOW_TYPE p;
	if (w != first(list)) {
		p = first(list);
		while (p->next != w) {
			p = p->next;
			if (p == NULL) break;	/* trap this to ensure */
		}							/* we don’t dereference */
		if (p != NULL)				 /* a null pointer in the */
			return(p);				/* while condition */
		else {
			error("can’t find previous to a non-existent node");
		}
	}
	else {
		error("can’t find previous before first element of list");
		return(w);
	}
}

/*** position at last element in a list ***/
WINDOW_TYPE last(LIST_TYPE *list) {
	WINDOW_TYPE p, q;
	if (*list == NULL) {
		error("non-existent list");
	}else {
		/* list exists: find last node */
		if (is_empty(list)) {
			p = end(list);
		} else {
			p = *list;
			q = p->next;
			while (q->next != NULL) {
				p = q;
				q = q->next;
			}
		}
		return(p);
	} 
}

/***  count of elements in the list ***/
int size(LIST_TYPE *list){
	WINDOW_TYPE p, q;
	int count= 0;
	if (*list == NULL) {
		error("non-existent list");
	}else {
		/* list exists: find last node */
		if (!is_empty(list)) { 
			count++;
			p = *list;
			q = p->next;
			while (q->next != NULL) {
				count++;
				p = q;
				q = q->next;
			}
		}
		return count;
	} 
}

/*** insert an element in a list ***/
LIST_TYPE *insert(ELEMENT_TYPE e, WINDOW_TYPE w, LIST_TYPE *list) {
	WINDOW_TYPE temp;
	if (*list == NULL) {
		error("cannot insert in a non-existent list"); 
	}
	else {
		/* insert it after w */
		temp = w->next;
		if ((w->next = (NODE_TYPE) malloc(sizeof(NODE))) == NULL)
			error("function insert: unable to allocate memory");
		else {
			w->next->element = e;
			w->next->next = temp;
		}
		return(list);
	}
}

/*** delete an element from a list ***/
LIST_TYPE *delete_item(WINDOW_TYPE w, LIST_TYPE *list) {
	WINDOW_TYPE p;
	if (*list == NULL) {
		error("cannot delete from a non-existent list");
	} else {
		p = w->next; /* node to be deleted */
		w->next = w->next->next; /* rearrange the links */
		free(p); /* delete the node */
		return(list); 
	}
}

/*** retrieve an element from a list ***/
ELEMENT_TYPE retrieve(WINDOW_TYPE w, LIST_TYPE *list) {
	if (*list == NULL) {
		error("cannot retrieve from a non-existent list");
	} else {
        return(w->next->element);
	}
}

/*** print all elements in a list ***/
void print(LIST_TYPE *list) {
	WINDOW_TYPE w; 
	ELEMENT_TYPE e;
	printf("Contents of list: \n");
	w = first(list);
	while (w != end(list)) {
		e = w->next->element;  //ToDo check
		printf("%d\n", e.value);
		w = next(w, list);
	}
	printf("---\n");
}

/*** assign values to an element ***/
int assign_element_values(ELEMENT_TYPE *e, VALUE_TYPE value) 
{
	e->value = value;
}