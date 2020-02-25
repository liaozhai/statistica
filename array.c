#include <stdlib.h>
#include <string.h>
#include "array.h"

void array_fold(
	const void* src,
	const size_t size,
	const size_t count,
	const void* start,
	void* result,
	void folder(const void*, const void*, void*)) {
	if (src != NULL && start != NULL && size != 0 && count != 0 && result != NULL) {
		void* prev = calloc(1, size);
		if (prev != NULL) {
			memcpy(prev, start, size);
			for (size_t i = 0; i < count; ++i) {
				void* next = calloc(1, size);
				if (next != NULL) {
					folder(prev, src + size * i, next);
					memcpy(prev, next, size);
					free(next);
				}
			}
			memcpy(result, prev, size);
			free(prev);
		}
	}
}