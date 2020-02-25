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
	// const int src [] = {1,2,3,4,5};
	// int start = 0;
	// array_fold (src, sizeof(src), sizeof (src) / sizeof (int), &start, add);
	// printf ("sum = %d\n", start);
}

void test_list (){
	printf ("test list...\n");
	List* tail = NULL;	
	List* lst = NULL;
	const unsigned int count = 5;
	const unsigned int size = sizeof(unsigned int);
	for (unsigned int i = 0; i < count; ++i){
		tail = list_append (tail);
		if (lst == NULL) {
			lst = tail;
		}
		tail->value = calloc (1, size);
		*((unsigned int*)tail->value) = i;
	}
	const unsigned int len = list_length (lst);
	printf ("list length = %u\n", len);
	unsigned int dst[len];
	list_to_array (lst, dst, size);
	printf ("array of list:\n");
	for (unsigned int i = 0; i < len; ++i){
		printf ("dst[%u] = %u\n", i, dst[i]);
	}
	list_free (lst);
}

void test_dist (){
	printf ("test list...\n");
	const double fst[] = {1.0,NAN,1.0,1.8,2.3};
	const double snd[] = {1.3,1.0,NAN,2.0,2.1};
	const size_t count = sizeof (fst) / sizeof (double);
	printf ("Euclidian distance = %.2f\n", dist(fst, snd, count));
	printf ("Pearson distance = %.2f\n", pearson(fst, snd, count));
}

void test_samples (){	
	unsigned int cols, rows;
	const double fst[] = {0.30,2.95,0.46,3.99,2.00,1.77,0.69,4.02,3.25,3.75};
	double** snd = read_samples ("series.txt", &cols, &rows);
	
	printf ("#\tEucl\tPearson\n");
	for (unsigned int i = 0; i < rows; ++i){
		const double d = dist(fst, snd[i], cols);
		const double p = pearson(fst, snd[i], cols);
		printf ("%d\t%.2f\t%.2f\n", i, d, p);
	}
	
	free (snd);
}

int main(int argc, char** argv) {
	// gen_samples ("series.txt", 10, 10, 1.0, 5.0);
	// test_array();
	test_list();
	// test_dist();
	// test_samples();
	return 0;
}
