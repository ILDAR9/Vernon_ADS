#define FALSE 0
#define TRUE 1


typedef double VALUE_TYPE;
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