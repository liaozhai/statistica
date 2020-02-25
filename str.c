#include <string.h>
#include "str.h"
#include "list.h"

size_t index_of (const char* str, const size_t start, const size_t len, char sym) {
    const size_t count = len - start;
    for(size_t i = start; i < count; ++i) {
        if (*(str + i) == sym) {
            return i;
        }
    }
    return -1;
}

List* tokenize (const char* src, char sym) {
    size_t start = 0, end;
    const size_t len = strlen(src);
    const size_t size = sizeof(char);
    List* list = NULL;
    do {
        end = index_of(src, start, len, sym);
        char* t = (char*)calloc(end - start, size);
        memcpy(t, src + start, size);
        list = list_append(list);
        list->value = (void*)t;

    } while (end != -1);
    return list;
}