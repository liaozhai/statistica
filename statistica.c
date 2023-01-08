#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dist.h"

#define BUFFER_SIZE 1024

void read_samples (const char* file, const size_t cols, const size_t rows, float mat[rows][cols]);
void read_samples (const char* file, size_t cols, size_t rows, float mat[rows][cols]) {
	FILE* fp = fopen (file, "r+");
	char line[BUFFER_SIZE];
	size_t i = 0;
	while ((fgets(line, BUFFER_SIZE, fp)) != NULL) {
		size_t len = strcspn(line, "\n");
		line[len] = '\0';
		char* t = strtok(line, "\t");
		size_t j = 0;
		while(t != NULL) {
			mat[i][j] = strtof(t, NULL);
			++j;
			t = strtok(NULL, "\t");
		}
		++i; 
	}
	fclose (fp);
}

int main(void) {
	size_t cols = 10;
	size_t rows = 10;
	const float fst[] = {0.30,2.95,0.46,3.99,2.00,1.77,0.69,4.02,3.25,3.75};
	float snd[rows][cols];
	read_samples ("series.txt", cols, rows, snd);

	printf ("#\tEucl\tPearson\n");
	for (size_t i = 0; i < rows; ++i){
		const float d = dist(cols, fst, snd[i]);
		const float p = pearson(cols, fst, snd[i]);
		printf ("%lu\t%.2f\t%.2f\n", i, d, p);
	}
	return EXIT_SUCCESS;
}
