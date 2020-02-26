#include <stdlib.h>
#include <math.h>
#include "dist.h"
#include "list.h"

List* coincidences (const float* fst, const float* snd, const size_t count);
List* coincidences (const float* fst, const float* snd, const size_t count) {
	List* lst = NULL;
	List* cur = NULL;	
	const size_t size = sizeof(size_t);
	for (size_t i = 0; i < count; ++i){
		if (!isnan (fst[i]) && !isnan (snd[i]))	{
			cur = list_append (cur);
			if (lst == NULL) {
				lst = cur;
			}
			cur->value = calloc (1, size);
			cur->size = size;
			*((size_t*)cur->value) = i;
		}
	}
	return lst;	
}

float dist (const float* fst, const float* snd, const size_t count) {
	List* lst = coincidences (fst, snd, count);
	const size_t len = list_length (lst);
	size_t indices[len];
	list_to_array (lst, indices);
	list_free (lst);
	float s = 0.0;
	for (size_t i = 0; i < len; ++i){
		size_t k = indices[i];
		s += pow (fst[k] - snd[k], 2.0);
	}
	
	return 1 / (1 + s);
}

float pearson (const float* fst, const float* snd, const size_t count){
	List* lst = coincidences (fst, snd, count);
	const size_t len = list_length (lst);
	
	if (len == 0) {
		return 0.0;
	}
	
	size_t indices[len];
	list_to_array (lst, (void*)indices);
	list_free (lst);
	
	float s1 = 0.0;
	float s2 = 0.0;
	float sq1 = 0.0;
	float sq2 = 0.0;
	float sp = 0.0;

	for (size_t i = 0; i < len; ++i){
		const size_t k = indices[i];
		s1 += fst[k];
		sq1 += pow (fst[k], 2.0);
		s2 += snd[k];
		sq2 += pow (snd[k], 2.0);
		sp += fst[k] * snd[k];
	}

	const float n = sp - (s1 * s2) / len;
	const float d = sqrt ((sq1 - pow (s1, 2.0) / len) * (sq2 - pow (s2, 2.0) / len));

	if (d == 0.0) {
		return 0.0;
	}
	return n / d;
}