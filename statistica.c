#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "array.h"
#include "list.h"
#include "dist.h"
#include "samples.h"
#include "statistica.h"

void add_int (const void* px, const void* py, void* result);
void add_int (const void* px, const void* py, void* result) {
	*(int*)result = *(int*)px + *(int*)py;
}

void test_array (){
	printf ("test array...\n");
	const int src[] = {1,2,3,4,5};	
	const int start = 0;
	const size_t count = 5;
	int result;
	array_fold((void*)src, sizeof (int), count, (void*)&start, (void*)&result, add_int);	
}

void test_list (){
	printf ("test list...\n");
	List* tail = NULL;	
	List* lst = NULL;
	const size_t count = 5;
	const size_t size = sizeof(size_t);
	for (size_t i = 0; i < count; ++i){
		tail = list_append (tail);
		if (lst == NULL) {
			lst = tail;
		}
		tail->value = calloc (1, size);
		tail->size = size;
		*((size_t*)tail->value) = i;
	}
	const size_t len = list_length (lst);
	printf ("list length = %Iu\n", len);
	size_t dst[len];
	list_to_array (lst, dst);
	printf ("array of list:\n");
	for (size_t i = 0; i < len; ++i){
		printf ("dst[%Iu] = %Iu\n", i, dst[i]);
	}
	list_free (lst);
}

void test_dist (){
	printf ("test list...\n");
	const float fst[] = {1.0,NAN,1.0,1.8,2.3};
	const float snd[] = {1.3,1.0,NAN,2.0,2.1};
	const size_t count = sizeof (fst) / sizeof (float);
	printf ("Euclidian distance = %.2f\n", dist(fst, snd, count));
	printf ("Pearson distance = %.2f\n", pearson(fst, snd, count));
}

void test_samples (){	
	size_t cols, rows;
	const float fst[] = {0.30,2.95,0.46,3.99,2.00,1.77,0.69,4.02,3.25,3.75};
	float** snd = read_samples ("series.txt", &cols, &rows);
	
	printf ("#\tEucl\tPearson\n");
	for (size_t i = 0; i < rows; ++i){
		const float d = dist(fst, snd[i], cols);
		const float p = pearson(fst, snd[i], cols);
		printf ("%Iu\t%.2f\t%.2f\n", i, d, p);
	}
	
	free (snd);
}

int main(int argc, char** argv) {
	// gen_samples ("series.txt", 10, 10, 1.0, 5.0);
	// test_array();
	// test_list();
	// test_dist();
	test_samples();
	return 0;
}
