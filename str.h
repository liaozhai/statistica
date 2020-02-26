#pragma once

#include <stdlib.h>
#include <stdbool.h>

bool index_of (const char* str, const size_t start, const char sym, size_t* index);
char** tokenize (const char* src, const char sym, size_t* length);