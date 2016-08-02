#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "samples.h"
#include "list.h"

void print_row (double row[], const unsigned int count);
void print_row (double row[], const unsigned int count){
	printf ("[");
	printf ("%.2f", row[0]);
	for (unsigned int i = 1; i < count; ++i){
		printf (", %.2f", row[i]);
	}
	printf ("]");
}

int cmp (const void* a, const void* b);
int cmp (const void* a, const void* b){
   return (*(int*)a - *(int*)b);
}

void normalize(int src[], double dst[], const size_t count, const double minscore, const double maxscore);
void normalize(int src[], double dst[], const size_t count, const double minscore, const double maxscore){
	int tmp[count];
	memcpy (tmp, src, sizeof(int) * count);	
	qsort (tmp, count, sizeof (int), cmp);
	int min = tmp[0];
	int max = tmp[count - 1];
	
	double f = (maxscore - minscore) / (max - min);
	for (unsigned int i = 0; i < count; ++i){
		dst[i] = f * src [i];
	}
}

void gen_samples (const char* file, const unsigned int cols, const unsigned int rows, const double minscore, const double maxscore) {
	srand(time(NULL));
	List* lst = NULL;
	List* cur = NULL;
	for (unsigned int i = 0; i < rows; ++i){
		int row[cols];
		gen_row (row, cols);		
		
		for (unsigned int k = 0; k < cols; ++k){
			cur = list_append (cur);
			if (lst == NULL) {
				lst = cur;
			}
			cur->pvalue = malloc (sizeof (int));
			*((int*)cur->pvalue) = row[k];
		}
							
	}
	size_t count = list_length (lst);
	int src[count];
	list_to_array (lst, src, int);
	list_free (lst);
	double dst[count];
	normalize (src, dst, count, minscore, maxscore);
	unsigned int k = 0;
	FILE* fs = fopen (file, "w+");
	for (unsigned int i = 0; i < rows; ++i){
		fprintf (fs, "%.2f", dst[k++]);
		for (unsigned int j = 1; j < cols; ++j){			
			fprintf (fs, "\t%.2f", dst[k++]);
		}		
		fprintf (fs, "\n");
	}
	fclose (fs);
}

double** read_samples (const char* file, unsigned int* pcols, unsigned int* prows) {
	FILE* fp = fopen (file, "r+");
	char line[256];
	size_t len = 0;
	ssize_t count = 0;
	List* lst = NULL;	
	List* cur = NULL;
	*prows = 0;
	while (fgets(line, sizeof line, fp) != NULL) {
		++(*prows);
		char* token = strtok (line, "\t");
		*pcols = 0;	
		while (token){
			++(*pcols);
			cur = list_append (cur);
			if(lst == NULL){
				lst = cur;
			}
			cur->pvalue = malloc (sizeof(double));
	        if (strcmp(token, "NAN") == 0) {        	
	        	*((double*)cur->pvalue) = NAN;
			}
			else {
				char* end;
				*((double*)cur->pvalue) = strtod (token, &end);				
			}	
			token = strtok(NULL, "\t");
		}		
    }
    const unsigned int cols = *pcols;
	const unsigned int rows = *prows;
    double** buf = malloc (sizeof(double*) * rows);
    cur = lst;
    for (unsigned int i = 0; i < rows; ++i){
    	buf[i] = malloc (sizeof(double) * cols);
    	for (unsigned int j = 0; j < cols; ++j){
    		buf[i][j] = *((double*)cur->pvalue);
    		cur = cur->pnext;
		}
	}
    list_free (lst);
	fclose (fp);
	return buf;
}
