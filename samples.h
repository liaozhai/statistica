#pragma once

#include <stdlib.h>
#include "list.h"

#define gen_row(row, count) {for (size_t i = 0; i < count; ++i) { row[i] = rand (); }}

void print_row (const float row[], const size_t count);
int cmp (const void* a, const void* b);
void normalize(const int src[], float dst[], const size_t count, const float minscore, const float maxscore);
void gen_samples (const char* file, const size_t cols, const size_t rows, float minscore, float maxscore);
void read_samples (const char* file, size_t cols, size_t rows, float mat[rows][cols]);