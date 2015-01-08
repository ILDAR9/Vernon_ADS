/* 

  Assignment4.c - application file for the solution of the travelling saleman problem by exhaustive search using backtracking

  CS-CO-412 Algorithms and Data Structures Assignment No. 4

  See travellingSalesman.h for details of the problem

  Ildar Nurgaliev
  26 November 2014

*/
 
#include "Assignment4.h"

int pred[NUMBER_OF_STOPS];       /* forwardtracking */
int pred_temp[NUMBER_OF_STOPS];  /* forwardtracking in permutations */
int min_path_length;			 /* length of min path */

int p[NUMBER_OF_STOPS];		     /* permutations */
boolean used[NUMBER_OF_STOPS];   /* for dynamics generating of permutations */
int n;							 /* n shops and n+1 indicates the carparking */

int distances[NUMBER_OF_STOPS][NUMBER_OF_STOPS];	 // distances between shop i (row) and shop j (column)

int main() {

   struct record_type record[NUMBER_OF_STOPS];

   int i, j, k, goal_node;				 // general purpose counters
   int number_of_test_cases;                      
   char shop_name[STRING_SIZE];          // general purpose string
   
   int debug = FALSE;                    // flag: if TRUE print information to assist with debugging

   FILE *fp_in, *fp_out;                 // input and output file pointers


   /* open input and output files */

   if ((fp_in = fopen("input.txt","r")) == 0) {
	   printf("Error can't open input input.txt\n");
      exit(0);
   }

   if ((fp_out = fopen("output.txt","w")) == 0) {
	   printf("Error can't open output output.txt\n");
       exit(0);
   }

   fscanf(fp_in, "%d", &number_of_test_cases); /* read the number of test cases */
   fgetc(fp_in); // move past end of line for subsequent fgets; fgets fails unless we do this

   if (debug) printf ("%d\n", number_of_test_cases);

   fprintf(fp_out, "Ildar Nurgaliev\n");

   /* main processing loop, one iteration for each test case */
   for (k=0; k<number_of_test_cases; k++) {
	  fprintf(fp_out, "%d\n", k+1); 	  	 
      /* read the data for each test case  */
      /* --------------------------------  */            
      fscanf(fp_in, "%d", &n);                   /* number of shops */
      (fp_in);  // move past end of line for subsequent fgets
	   fgetc(fp_in); // move past end of line for subsequent fgets; fgets fails unless we do this
      if (debug) printf ("%d\n",n);

      /* get the shop names and the car name */
      for (i = 0; i < n+1; i++) {

         fgets(shop_name, STRING_SIZE, fp_in);
         remove_new_line(shop_name);

         record[i].key = i+1;
         strcpy(record[i].string,shop_name);

         if (debug) printf ("%s\n",record[i].string);
      }

      /* get the matrix of distances */
      for (i = 0; i < n+1; i++) {
         for (j = 0; j < n+1; j++) {
            fscanf(fp_in, "%d", &(distances[i][j]));
         }
      }

      if (debug) {
         for (i = 0; i < n+1; i++) {
            for (j = 0; j < n+1; j++) {
               printf("%3d ", distances[i][j]);
            }
            printf("\n");
         }
      }

      /* reinit  helping ADS */
	  for (i=0;i < n;i++){
		used[i] = FALSE;
		p[i] = i;
	  }
      min_path_length = MAX_NUMBER;   //reinit minimum distance
	  p[n] = n;
      /* main processing begins here */
      /* --------------------------- */
	  saleman_find_path(0);         //start algorithm of searching

	  fprintf(fp_out, "%d\n", min_path_length); 
      /* print route */
	  fprintf(fp_out, "%s\n", record[n].string);
	  for (j = n; (j=pred[j])!=n;){
		  fprintf(fp_out, "%s\n", record[j].string);
	  }	
	  fprintf(fp_out, "%s\n", record[n].string);
      fprintf(fp_out, "\n");  /* set empty row between Scenarios */
      if (debug)
		  getchar();

   }

   fclose(fp_in);
   fclose(fp_out);                                                         
}

void remove_new_line(char string[]) {
   int i;

   i=0;
   while(string[i] != '\0' && string[i] != '\n')
      i++;
   string[i] = '\0';
}

void saleman_find_path(int pos){
  int i ;
  if (pos == n) {
	trace_gen_path(); // proceed generated path for testing	
    return;
  }
  for (i=0;i<n;i++) {
    if (!used[i]) {
      used[i] = TRUE;
      p[pos] = i;
 
      saleman_find_path(pos+1);
      
      p[pos] = 0; 
      used[i] = FALSE;
    }
  }
}

void cp_forwardtracking(int from[], int to[]){
	int i = 0;
	for (i = 0;i < NUMBER_OF_STOPS; i++){
		to[i] = from[i];
	}
}

void trace_gen_path(){
	int i, path_length = 0, pred_i = n;
	for (i = 0;i < n+1; i++){
		path_length += distances[p[pred_i]][p[i]];

		pred_temp[p[pred_i]] = p[i];
		pred_i = i;		/* persist index */
	}
	path_length += distances[n][p[pred_i]];
	if (path_length<min_path_length){
		min_path_length = path_length;
		cp_forwardtracking(pred_temp, pred);
	}
}