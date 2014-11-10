/***
* Queue.c
* Author - Nurgaliev Ildar
*
* Queue implementation based on LinkedList
*
****/

#include "LinkedList.h"

//WINDOW_TYPE empty(LIST_TYPE*);

ELEMENT_TYPE head(LIST_TYPE *queue){
	return retrieve(first(queue), queue);
}
//retrieve(first(Q),Q)

LIST_TYPE* enqueue(ELEMENT_TYPE e, LIST_TYPE *queue){
	return insert(e, end(queue), queue);
}
//insert(e, end(Q), Q)

ELEMENT_TYPE dequeque(LIST_TYPE *queue){
	ELEMENT_TYPE e;
	e = retrieve(first(queue), queue);
	delete_item(first(queue), queue);
	return e;
}
//retrieve(First(Q), Q)
//delete(First(Q), Q)

/***
int main(void) {
	ELEMENT_TYPE e;
	LIST_TYPE queue; 
	declare(&queue);

	printf("queue\n");

	assign_element_values(&e, 1);
	enqueue(e,&queue);
	assign_element_values(&e, 2);
	enqueue(e,&queue);
	empty(&queue);
	assign_element_values(&e, 1);
	enqueue(e,&queue);
	assign_element_values(&e, 2);
	enqueue(e,&queue);

	while(!is_empty(&queue)){
		printf("size: %d\n", size(&queue));
		e = dequeque(&queue);
		
		printf("%f \n", e.value);
		
	}
	getchar();
}***/
