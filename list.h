#pragma once

#include <stdlib.h>

struct list_node {
	void* value;
	size_t size;
	struct list_node* next;
};

typedef struct list_node List;

List* list_append (List* head);
void list_free (List* head);
size_t list_length(const List* head);
void list_to_array(const List* list, void* array);