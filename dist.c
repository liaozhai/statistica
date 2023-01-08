#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "dist.h"

void coincidences (const size_t count, const float fst[count], const float snd[count], bool indices[count]);
void coincidences (const size_t count, const float fst[count], const float snd[count], bool indices[count]) {
	for (size_t i = 0; i < count; ++i){
		indices[i] = !isnan (fst[i]) && !isnan (snd[i]);
	}
}

float dist (const size_t count, const float fst[count], const float snd[count]) {
	bool indices[count];
	coincidences (count, fst, snd, indices);
	float s = 0.0;
	for (size_t i = 0; i < count; ++i){
		if (indices[i]) {
			s += pow (fst[i] - snd[i], 2.0);
		}
	}
	return 1 / (1 + s);
}

float pearson (const size_t count, const float fst[count], const float snd[count]){
	bool indices[count];
	coincidences (count, fst, snd, indices);
	
	float s1 = 0.0;
	float s2 = 0.0;
	float sq1 = 0.0;
	float sq2 = 0.0;
	float sp = 0.0;

	size_t k = 0;
	for (size_t i = 0; i < count; ++i){
		if (indices[i]) {
			s1 += fst[i];
			sq1 += fst[i] * fst[i];
			s2 += snd[i];
			sq2 += snd[i] * snd[i];
			sp += fst[i] * snd[i];
			++k;
		}
	}

	const float n = sp - (s1 * s2) / k;
	const float d = sqrt ((sq1 - s1 * s1 / k) * (sq2 - s2 * s2 / k));

	if (d == 0.0) {
		return 0.0;
	}
	return n / d;
}