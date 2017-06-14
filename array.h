#pragma once

#define array_fold(src, count, start, f) {\
	for (unsigned int i = 0; i < count; ++i){\
		start = f (start, src[i]);\
	}\
}

#define array_map(src, dst, count, f) {\
	for (unsigned int i = 0; i < count; ++i){\
		dst[i] = f(src[i]);\
	}\
}
