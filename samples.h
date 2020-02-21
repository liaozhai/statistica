#pragma once

#define gen_row(row, count) {for (unsigned int i = 0; i < count; ++i) { row[i] = rand (); }}

void print_row (const double row[], const unsigned int count);
int cmp (const void* a, const void* b);
void normalize(const int src[], double dst[], const size_t count, const double minscore, const double maxscore);
void gen_samples (const char* file, const unsigned int cols, const unsigned int rows, double minscore, double maxscore);
double** read_samples (const char* file, unsigned int* pcols, unsigned int* prows);