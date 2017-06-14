#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "array.h"
#include "list.h"
#include "dist.h"
#include "samples.h"

int add (int x, int y);
int add (int x, int y) {
	return x + y;
}

void test_array ();
void test_array (){
	printf ("test array...\n");
	int src [] = {1,2,3,4,5};
	int start = 0;
	array_fold (src, sizeof (src) / sizeof (int), start, add);
	printf ("sum = %d\n", start);
}

void test_list ();
void test_list (){
	printf ("test list...\n");
	List* head = NULL;
	List* tail = NULL;
	unsigned int count = 5;
	for (unsigned int i = 0; i < count; ++i){
		tail = list_append (tail);
		if (head == NULL) {
			head = tail;
		}		
		tail->pvalue = malloc (sizeof (unsigned int));
		*((unsigned int*)tail->pvalue) = i;
	}
	unsigned int len = list_length (head);
	printf ("list length = %u\n", len);
	unsigned int dst[len];
	list_to_array (head, dst, unsigned int);
	printf ("array of list:\n");
	for (unsigned int i = 0; i < len; ++i){
		printf ("dst[%u] = %u\n", i, dst[i]);
	}
	list_free (head);
}

void test_dist ();
void test_dist (){
	double fst[] = {1.0,NAN,1.0,1.8,2.3};
	double snd[] = {1.3,1.0,NAN,2.0,2.1};
	unsigned int count = sizeof (fst) / sizeof (double);
	printf ("Euclidian distance = %.2f\n", dist(fst, snd, count));
	printf ("Pearson distance = %.2f\n", pearson(fst, snd, count));
}

void test_samples ();
void test_samples (){	
	unsigned int cols, rows;
	double fst[] = {0.30,2.95,0.46,3.99,2.00,1.77,0.69,4.02,3.25,3.75};
	double** snd = read_samples ("series.txt", &cols, &rows);
	
	printf ("#\tEucl\tPearson\n");
	for (unsigned int i = 0; i < rows; ++i){
		printf ("%d\t%.2f\t%.2f\n", i, dist(fst, snd[i], cols), pearson(fst, snd[i], cols));		
	}
	
	free (snd);
}

int main(int argc, char** argv) {
	// gen_samples ("series.txt", 10, 10, 1.0, 5.0);
	test_samples();
	return 0;
}
