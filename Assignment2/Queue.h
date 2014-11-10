#include "Types.h"

WINDOW_TYPE declare(LIST_TYPE*);
WINDOW_TYPE empty(LIST_TYPE*);
ELEMENT_TYPE head(LIST_TYPE*);
LIST_TYPE* enqueue(ELEMENT_TYPE, LIST_TYPE*); 
ELEMENT_TYPE dequeque(LIST_TYPE*);
int is_empty(LIST_TYPE*);

int assign_element_values(ELEMENT_TYPE*, VALUE_TYPE);
int size(LIST_TYPE*);