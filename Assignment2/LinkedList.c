/***
* LinkedList.c
* Author - Nurgaliev Ildar
*
* Linked list implementation of LIST ADT
*
****/

#include "LinkedList.h"

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
		error("can�t find next after end of list");
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
		}							/* we don�t dereference */
		if (p != NULL)				 /* a null pointer in the */
			return(p);				/* while condition */
		else {
			error("can�t find previous to a non-existent node");
		}
	}
	else {
		error("can�t find previous before first element of list");
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
int print(LIST_TYPE *list) {
	WINDOW_TYPE w; 
	ELEMENT_TYPE e;
	printf("Contents of list: \n");
	w = first(list);
	while (w != end(list)) {
		e = w->element;  //ToDo check
		printf("%f\n", e.value);
		w = next(w, list);
	}
	printf("---\n");
	return(0);
}


/*** error handler: print message passed as argument and
take appropriate action ***/
/**
int error(char *s) {
	printf("Error: %s\n", s);
	exit(0);
}
**/

/*** assign values to an element ***/
int assign_element_values(ELEMENT_TYPE *e, VALUE_TYPE value) 
{
	e->value = value;
}
/***
int main(void){
	WINDOW_TYPE w;
	ELEMENT_TYPE e;
	LIST_TYPE list; 
	//declare(&list);
	empty(&list);
	print(&list);
	assign_element_values(&e, 1, "String A");
	w = first(&list);
	insert(e, w, &list);
	print(&list);
	assign_element_values(&e, 2, "String B");
	insert(e, w, &list);
	print(&list);
	assign_element_values(&e, 3, "String C");
	insert(e, last(&list), &list);
	print(&list);
	assign_element_values(&e, 4, "String D");
	w = next(last(&list), &list);
	insert(e, w, &list);
	print(&list);
	w = previous(w, &list);
	delete_item(w, &list);
	print(&list);
	getchar();
} ***/