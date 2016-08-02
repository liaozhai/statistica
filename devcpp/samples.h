#pragma once

#define gen_row(row, count) {\
	for (unsigned int i = 0; i < count; ++i){\
		row[i] = rand ();\
	}\
}

void gen_samples (const char* file, const unsigned int cols, const unsigned int rows, double minscore, double maxscore);
double** read_samples (const char* file, unsigned int* pcols, unsigned int* prows);
