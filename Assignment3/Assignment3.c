/***
* Assignment3.c
* Author - Ildar Nurgaliev
*	
****/
#include "Assignment3.h"
int push[MAXV];      /* min passageers count in v from start_node */
int pred[MAXV];      /* prevous node index to current node */

int main(void) {
	int N     /* vertex count */
        , R   /* edge count */
        , start_node, goal_node, i, scenario_index = 1, passagers_count, path_length;
    Graph* g = (Graph*)malloc(sizeof(Graph)); /* allocate reusable graph storage */
	FILE* f_input;
	FILE* f_output;
	if ((f_input = fopen(input_file_name, "r")) == NULL ||
		(f_output = fopen(output_file_name, "w")) == NULL){           
			error(MSG_ERR_FILE_NOT_OPEN);
	}	
    fprintf(f_output, "%s\n",AUTHOR_NAME);
	while(fscanf(f_input, "%d %d", &N, &R) && !(N==0 && R ==0)){  
        fprintf(f_output, p_scenario, scenario_index++);
		if(N < CITY_COUNT_MIN && R < 0){  /* if N and R not valid according to assignment's restriction */
            error(MSG_ERR_INVALID_INPUT_STRUCTURE);
        } else if(N==1){
            fscanf(f_input, "%d %d %d", &start_node, &goal_node, &passagers_count);     
            fprintf(f_output, p_number_trips, 0);
            fprintf(f_output, p_route_none);
            continue;
        }        

		g = read_graph(g, N, R, FALSE, f_input); /* read graph from input file */	              
		fscanf(f_input, "%d %d %d", &start_node, &goal_node, &passagers_count);      
        bfs_max_wide(g, start_node, goal_node); /* start search algorithm */     
        /* print min count of trips */
        fprintf(f_output, p_number_trips, ceil_up((double)passagers_count / (push[goal_node]-1)));

        /* proceed route */
        fprintf(f_output, p_route);
        path_length = 0;
        push[path_length++] = goal_node;
        /* inverse found route from goal_node */
        for(i=goal_node; pred[i]>0; i=pred[i]){ 
            push[path_length++] = pred[i];
        }
        /* print route */
        for (i=path_length-1;i>=0 ;i--){
            fprintf(f_output, " %d", push[i]);
        }   
        /* proceed route end */

        fprintf(f_output, "\n\n");  /* set empty row between Scenarios */
	}
	fclose(f_input);
	fclose(f_output);
}

void init(int v_count){
    int i;
    for(i = 1; i <= v_count; i++){
        push[i] = 0;
        pred[i] = 0;
    }
}

void bfs_max_wide(Graph* g, int start_node, int goal_node){   
    Edgenode* child_node;
    ELEMENT_TYPE e;
	LIST_TYPE Q; 
	declare(&Q);
    init(g->nvertices); /* refresh datastructures */
    pred[start_node] = -1; /* mark pred of start_node for easy inverse operation in 'proceed route' */
    push[start_node] = MAX_VAL;
    assign_element_values(&e,start_node);
    enqueue(e, &Q);
    while(!is_empty(&Q)){ /* BFS on GRAPH */    
        int u = dequeque(&Q).value;
        /* if in childe_node possible count of passegers is less than u can propose then proceed that child */
        for (child_node = g->edges[u]; child_node!=NULL;child_node= child_node->next){
            if(  (min(push[u], child_node->weight) > push[child_node->y]) )
            {
                push[child_node->y] = min(push[u], child_node->weight); /* update possible count of passegers throught this node */
                pred[child_node->y] = u;
                assign_element_values(&e, child_node->y);
                enqueue(e, &Q);
            }
        }      
    }
}

int ceil_up(double p){
    if (p - (int)p > 0) {
        p += 1;       
    }
    return (int)p;
}

void error(const char *er_message) {
    printf("Error: %s\n", er_message);
	getchar();
    exit(1);
}