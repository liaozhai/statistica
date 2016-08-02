#pragma once

struct list_node {\
	void* pvalue;
	struct list_node* pnext;
};

typedef struct list_node List;

List* list_append (List* head);
void list_free (List* head);
unsigned int list_length(List* head);

#define list_to_array(lst, dst, type){\
	List* cur = lst;\
	unsigned i = 0;\
	while (cur != NULL){\
		dst[i++] = *((type*)cur->pvalue);\
		cur = cur->pnext;\
	}\
}
