#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "Types.h"

int error(char*);
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
int print(LIST_TYPE*);
int assign_element_values(ELEMENT_TYPE*, VALUE_TYPE);
LIST_TYPE *delete_item(WINDOW_TYPE, LIST_TYPE*);
WINDOW_TYPE declare(LIST_TYPE*);
int size(LIST_TYPE*);