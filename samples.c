#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "samples.h"
#include "list.h"
#include "str.h"

#define BUFFER_SIZE 256

void print_row (const float row[], const size_t count){
	printf ("[");
	printf ("%.2f", row[0]);
	for (size_t i = 1; i < count; ++i){
		printf (", %.2f", row[i]);
	}
	printf ("]");
}

int cmp (const void* a, const void* b){
   return (*(int*)a - *(int*)b);
}

void normalize(const int src[], float dst[], const size_t count, const float minscore, const float maxscore){
	int tmp[count];
	memcpy (tmp, src, sizeof(int) * count);	
	qsort (tmp, count, sizeof (int), cmp);
	int min = tmp[0];
	int max = tmp[count - 1];
	
	float f = (maxscore - minscore) / (max - min);
	for (size_t i = 0; i < count; ++i){
		dst[i] = f * src [i];
	}
}

void gen_samples (const char* file, const size_t cols, const size_t rows, const float minscore, const float maxscore) {
	srand(time(NULL));
	List* lst = NULL;
	List* cur = NULL;
	for (size_t i = 0; i < rows; ++i){
		int row[cols];
		gen_row (row, cols);		
		
		for (size_t k = 0; k < cols; ++k){
			cur = list_append (cur);
			if (lst == NULL) {
				lst = cur;
			}
			cur->value = malloc (sizeof (int));
			*((int*)cur->value) = row[k];
		}
							
	}	
	const size_t count = list_length(lst);	
	int src[count];
	list_to_array (lst, (void*)src);
	list_free (lst);
	float dst[count];
	normalize (src, dst, count, minscore, maxscore);
	size_t k = 0;
	FILE* fs = fopen (file, "w+");
	for (size_t i = 0; i < rows; ++i){
		fprintf (fs, "%.2f", dst[k++]);
		for (size_t j = 1; j < cols; ++j){			
			fprintf (fs, "\t%.2f", dst[k++]);
		}		
		fprintf (fs, "\n");
	}
	fclose (fs);
}

float** read_samples (const char* file, size_t* pcols, size_t* prows) {
	FILE* fp = fopen (file, "r+");	
	char line[BUFFER_SIZE];
	List* lst = NULL;	
	List* cur = NULL;
	size_t rows = 0;
	size_t cols = 0;
	while (fgets(line, BUFFER_SIZE, fp) != NULL) {				
		size_t n;
		if (index_of(line, 0, '\n', &n) && n >= 0) {
			line[n] = '\0';
		}
		char** tokens = tokenize(line, '\t', &cols);
		float* values = (float*) calloc(cols, sizeof (float));
		for (size_t i = 0; i < cols; ++i) {
			if (strcmp(tokens[i], "NAN") == 0) {
	        	values[i] = NAN;
			}
			else {
				char* e;
				values[i] = strtof(tokens[i], &e);
			}
			free(tokens[i]);
		}
		free(tokens);

		cur = list_append (cur);
		if(lst == NULL){
			lst = cur;
		}
		cur->value = values;
		cur->size = cols;
		++rows;
    }    
    float** buf = calloc (rows, sizeof(float*));
    cur = lst;
    for (size_t i = 0; i < rows; ++i){
    	buf[i] = cur->value;    	
		cur = cur->next;
	}
    list_free (lst);
	fclose (fp);
	*prows = rows;
	*pcols = cols;
	return buf;
}
