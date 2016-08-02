#include <stdlib.h>
#include "list.h"

List* list_append (List* head){
	List* tail = malloc (sizeof(List));
	tail->pnext = NULL;
	tail->pvalue = NULL;
	if(head != NULL){
		head->pnext = tail;
	}
	return tail;
}

void list_free (List* head){
	List* cur = head;	
	while (cur != NULL){
		List* pnext = cur->pnext;
		free (cur->pvalue);
		free (cur);
		cur = pnext;
	}
}

unsigned int list_length (List* head){
	List* cur = head;
	unsigned int length	= 0;
	while (cur != NULL){
		++length;		
		cur = cur->pnext;
	}
	return length;
}

