#include <stdlib.h>
#include <string.h>
#include "list.h"

List* list_append (List* tail){
	List* node = (List*) calloc (1, sizeof(List));
	node->next = NULL;
	node->value = NULL;	
	if(tail != NULL){		
		tail->next = node;
	}
	return node;
}

void list_free (List* head){
	List* cur = head;
	while (cur != NULL){
		List* next = cur->next;
		free (cur->value);
		free (cur);
		cur = next;
	}
}

size_t list_length (const List* head){
	if (head != NULL) {
		List* cur = head->next;
		size_t length = 1;
		while (cur != NULL){
			++length;
			cur = cur->next;
		}
		return length;
	}
	else {
		return 0;	
	}	
}

void list_to_array(const List* list, void* array) {
	if (list != NULL) {
		memcpy(array, list->value, list->size);
		List* cur = list->next;
		size_t i = 1;
		while (cur != NULL)	{
			memcpy(array + cur->size * i, cur->value, cur->size);
			cur = cur->next;
			++i;
		}
	}
}