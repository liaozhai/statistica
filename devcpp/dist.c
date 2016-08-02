#include <stdlib.h>
#include <math.h>
#include "dist.h"
#include "list.h"

List* coincidences (double* fst, double* snd, unsigned int count);
List* coincidences (double* fst, double* snd, unsigned int count) {
	List* lst = NULL;
	List* cur = NULL;	
	for (unsigned int i = 0; i < count; ++i){
		if (!isnan (fst[i]) && !isnan (snd[i]))	{
			cur = list_append (cur);
			if (lst == NULL) {
				lst = cur;
			}
			cur->pvalue = malloc (sizeof(unsigned int));
			*((unsigned int*)cur->pvalue) = i;
		}		
	}	
	return lst;	
}

double dist (double* fst, double* snd, unsigned int count) {
	List* lst = coincidences (fst, snd, count);
	unsigned int len = list_length (lst);
	unsigned int indices[len];
	list_to_array (lst, indices, unsigned int);
	list_free (lst);
	double s = 0.0;	
	for (unsigned int i = 0; i < len; ++i){
		unsigned int k = indices[i];
		s += pow (fst[k] - snd[k], 2.0);
	}
	
	return 1 / (1 + s);
}

double pearson (double* fst, double* snd, unsigned int count){
	List* lst = coincidences (fst, snd, count);
	unsigned int len = list_length (lst);
	
	if (len == 0) {
		return 0.0;
	}
	
	unsigned int indices[len];
	list_to_array (lst, indices, unsigned int);
	list_free (lst);
	
	double s1 = 0.0, s2 = 0.0, sq1 = 0.0, sq2 = 0.0, sp = 0.0;
	for (unsigned int i = 0; i < len; ++i){
		unsigned int k = indices[i];
		s1 += fst[k];
		sq1 += pow (fst[k], 2.0);
		s2 += snd[k];
		sq2 += pow (snd[k], 2.0);
		sp += fst[k] * snd[k];
	}
	double n = sp - (s1 * s2) / len;
	double d = sqrt ((sq1 - pow (s1, 2.0) / len) * (sq2 - pow (s2, 2.0) / len));
	if (d == 0.0) {
		return 0.0;
	}
	return n / d;
}
