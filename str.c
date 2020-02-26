#include <string.h>
#include "str.h"
#include "list.h"

bool index_of (const char* str, const size_t start, const char sym, size_t* index) {    
    size_t i = start;
    while (str[i] != '\0') {
        if (str[i] == sym) {            
            *index = i;
            return true;
        }
        ++i;
    }
    *index = i;
    return false;
}

char** tokenize (const char* src, const char sym, size_t* length) {
    size_t start = 0;
    List* lst = NULL;
    List* tail = NULL;
    size_t end;
    size_t len = 0;
    const size_t size = sizeof(char);
    while (index_of(src, start, sym, &end)) {
        const size_t count = end - start;
        tail = list_append(tail);
        if (lst == NULL) {
            lst = tail;
        }
        tail->value = calloc(count + 1, size);
        tail->size = count;        
        memcpy(tail->value, src + size * start, count);
        start = end + 1;
        ++len;
    }
    if (end > 0) {
        const size_t count = end - start;
        tail = list_append(tail);        
        tail->value = calloc(count + 1, size);
        tail->size = count;        
        memcpy(tail->value, src + size * start, count);
        ++len;
    }    
    *length = len;
    char** tokens = calloc(len, sizeof(char*));
    size_t i = 0;
    while (lst != NULL) {
        tokens[i] = calloc(lst->size + 1, size);
        memcpy(tokens[i], lst->value, lst->size);
        ++i;
        lst = lst->next;
    }    
    return tokens;
}