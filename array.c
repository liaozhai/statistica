#include <stdlib.h>
#include <assert.h>
#include "array.h"

void cpy (size_t size, void* src, void* dst);
void cpy (size_t size, void* src, void* dst) {
	if (src != NULL && dst != NULL) {		
		for (size_t i = 0; i < size; ++i) {
			*((char*)dst + i) = *((char*)src + i);
		}
	}
}

void array_fold(const void* src, const size_t size, const size_t count, void* start, void* result, void folder(const void*, const void*, void*)) {	
	void* t = NULL;
	void* p = malloc(size);
    assert(p);
	cpy(size, start, p);
	for (size_t i = 0; i < count; ++i) {
		t = malloc(size);
        assert(t);
		folder(p, src + size * i, t);
		cpy(size, t, p);
	}
	cpy(size, t, result);
	free(t);
	free(p);
}