// ============================================================================
//
// list container written in pure C.
// (c) 2017, Valentine Akhiarov.
//
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "API.h"

// ============================================================================
// DEFINES
// ============================================================================

#define ISNULL(p, s, v)                         \
	if (p == NULL) {                        	\
		printf("'%s' is invalid !\n", s);		\
		return v;                        		\
	}

#define ZEROSIZE(p)                         	\
	if (p <= 0) {                           	\
		printf("List size is invalid !\n");		\
		return 0;                        		\
	}

// ============================================================================
// LIST STRUCTURE COMPONENTS
// ============================================================================

// to use 'Cell' in Cell struct instead of 'struct Cell'
typedef struct Cell_t Cell_t;

typedef struct Cell_t {
	void* data;
	Cell_t* prev;
	Cell_t* next;
} Cell_t;

typedef struct List_t {
	Cell_t* head;
	Cell_t* tail;
	int size;
} List_t;

List_t* convert(void* data) {
	return (List_t*)data;
}

// ============================================================================
// FUNCTIONS DECLARATION
// ============================================================================

Sequential* list_construct(int size, void** content, int content_size);			// Construct list
Sequential* list_destruct(Sequential* list);									// Destruct list

Iterator* list_iterator_construct(Sequential* list);							// Construct iterator
Iterator* list_iterator_destruct(Iterator* iter);								// Destuct iterator

void list_begin(Sequential* container_list, Iterator* pointer);					// Return iterator to beginning
void list_end(Sequential* container_list, Iterator* pointer);					// Return iterator to end
void list_next(Sequential* container_list, Iterator* pointer);					// Return iterator to next list element
void list_prev(Sequential* container_list, Iterator* pointer);					// Return iterator to previous list element

void* list_get(Sequential* container_list, Iterator* iter);						// Get value by iterator
void list_assign(Sequential* container_list, Iterator* iter, void* content);	// Assign content [to container] [by iterator]
void list_insert(Sequential* container_list, Iterator* iter, void* content);	// Insert elements
//void list_resize(Sequential* container_list, int size);						// Change size
void list_swap (Sequential* container_list, Iterator* iter1, Iterator* iter2);	// Swap content

int list_valid_check(Sequential* container_list);

void list_view(Sequential* container_list);										// View list

// ============================================================================

int list_valid_check(Sequential* container_list) {

	ISNULL(container_list, "List", 0);
	List_t* mylist = convert(container_list->data);
	ZEROSIZE(mylist->size);

	return 1;
}

// ============================================================================

Sequential* list_construct(int size, void** content, int content_size) {

	// check if ok
	ZEROSIZE(size);
	ISNULL(content, "List", 0);

	// allocate list container & define its functions
	Sequential* container_list = (Sequential*)calloc(1, sizeof(Sequential));
	container_list->get = (*list_get);
	container_list->assign = (*list_assign);
	container_list->insert = (*list_insert);
	//	container_list->resize = (*list_resize);
	container_list->swap = (*list_swap);
	container_list->destruct = (*list_destruct);

	container_list->iterator_construct = (*list_iterator_construct);
	container_list->iterator_destruct = (*list_iterator_destruct);

	// allocate data (empty mylist)
	container_list->data = (void*)calloc(1, sizeof(List_t));
	List_t* mylist = convert(container_list->data);
	mylist->head = (Cell_t*)calloc(1, sizeof(Cell_t));
	mylist->head->data = NULL;
	mylist->head->prev = NULL;
	mylist->head->next = NULL;
	mylist->tail = mylist->head;
	mylist->size = 1;

	// fill mylist with content
	int i = 0;
	if (size >= 1) {
		container_list->assign(container_list, (Iterator*)(((Cell_t**)&(mylist->head))), content[i]); //мб **** и &&& !!! changed
	}
	Iterator* iter = list_iterator_construct(container_list);
	for (i = 1; i < size; i++) {
		iter->end(container_list, iter);
		container_list->insert(container_list, iter, content[i]);
		printf("%d - %s\n", i, (char*)content[i]);
	}

	/*int i = 0;
	for (i = 0; i < size; i++) {
		data->array[i] = *(void**)((char*)content + i * content_size);
	}
	data->size = size;
	data->elemsize = content_size;*/

	return container_list;
}

// ============================================================================

Sequential* list_destruct(Sequential* container_list) {

	if (list_valid_check(container_list)) {
		List_t* mylist = convert(container_list->data);
		free(mylist->head);
		free(container_list->data);
		free(container_list);
	}

	return NULL;
}

// ============================================================================

Iterator* list_iterator_construct(Sequential* container_list) {

	if (!list_valid_check(container_list)) return NULL;

	Iterator* iter = (Iterator*)calloc(1, sizeof(Iterator));
	//void** pointer = (void**)calloc(1, sizeof (void*));

	List_t* mylist = convert(container_list->data);
	//List_t* data = (List*)(container_list->data);

	iter->pointer = (void**)(&(mylist->head));	//!!!meaw Cell_t** to void **
	//*pointer = data->head;

	iter->begin = (*list_begin);
	iter->end = (*list_end);
	iter->prev = (*list_prev);
	iter->next = (*list_next);

	return iter;
}

/*
Iterator* list_iterator_construct(Sequential* container_list) {
	//if (!vectorValidCheck(vector)) return NULL;

	Iterator* iterator = (Iterator*)calloc(1, sizeof(Iterator));

	List_t* data = convert(container_list->data);

	iterator->pointer = &((data->head)->data);	//void**

	iterator->begin = (*list_begin);
	iterator->end = (*list_end);
	iterator->prev = (*list_prev);
	iterator->next = (*list_next);

	return iterator;
}*/

/*
Iterator list_iterator_init(struct Sequential* container_list) {
	List_t* l = (List_t*)(list->data);	// l обозначает data, приведённую к типу List_t*
	void** pointer = (void**) malloc (sizeof (void*)); // аллоцируем память под размер указателя void (т.е. void*)
	// т.е. указатель на выделенную память
	*pointer = l->head;	//

	return pointer;
}
*/

// ============================================================================

Iterator* list_iterator_destruct(Iterator* iter) {
	free(iter);
	return 0;
}

// ============================================================================

void list_assign(Sequential* container_list, Iterator* iter, void* content) {

	//((node*)(*iter))->data = content;
	((Cell_t*)(*(iter->pointer)))->data = content;
	//if (!vectorValidCheck(vector) ||
	//	!iteratorValidCheck(vector, iter)) return;
/*
	List_t* data = convert(container_list->data); // void* -> Data_t*!!!!!

	int len = iter->pointer - (&((data->head)->data)); //void** - void**
	int index = len / sizeof(void*);

	data->array[index] = content;
	data->array = void**
*/
}

// ============================================================================

void list_insert(Sequential* container_list, Iterator* iter, void* content) {

 	if (!list_valid_check(container_list)) return;
	// if (iter == NULL) return;

	List_t* mylist = convert(container_list->data);
	Cell_t* newCell = (Cell_t*)calloc(1, sizeof(Cell_t));
	Cell_t* currentCell = NULL;
    currentCell = (Cell_t*)(*(iter->pointer));

    newCell->data = content;
    newCell->prev = currentCell;
    newCell->next = currentCell->next;

    if (currentCell->next) {
		(currentCell->next)->prev = newCell;
    }
    currentCell->next = newCell;

	if (!(newCell->next)) mylist->tail = newCell;
    if (!(newCell->prev)) mylist->head = newCell;
    //+ if there was no head size = 1 & tail = newCell?

	(mylist->size)++;

}

// ============================================================================

void list_begin(Sequential* container_list, Iterator* iter) {

	if (!list_valid_check(container_list)) return;
	List_t* mylist = convert(container_list->data);
	iter->pointer = (void**)(&(mylist->head));	//!!!meaw cell_t** to void**

}

// ============================================================================

void list_end(Sequential* container_list, Iterator* iter) {

	if (!list_valid_check(container_list)) return; //added
	List_t* mylist = convert(container_list->data);
	iter->pointer = (void**)(&(mylist->tail)); //!!!meaw changed * to & cell_t** to void**

}

// ============================================================================

void list_prev(Sequential* container_list, Iterator* iter) {

	if (!list_valid_check(container_list)) return;
	List_t* mylist = convert(container_list->data);
	// iter->pointer = (void **)(&(data->tail));

	//if (iter->pointer > data->array)
	//	iter->pointer -= sizeof(void*);

	if (iter->pointer != (void**)(&(mylist->head))) {
		Cell_t* prev = ((Cell_t*)(*(iter->pointer)))->prev;
		iter->pointer = (void**)(&prev);
		//iter->pointer = (void**)(&((mylist->head)->prev));
	} else {
		// do nothing, because prev elem is NULL
		printf("WARNING: Cannot reference to previous element of first one !\n");
	}

	/*Cell_t** pCell = (void**)(iter->pointer);

	if (pCell->prev != mylist->head) {
		iter->pointer = (void**)(&(pCell->prev));
	}*/ //else {
	//	iter->pointer = NULL;
	//}
}

// ============================================================================

void list_next(Sequential* container_list, Iterator* iter) {

	if (!list_valid_check(container_list)) return;
	List_t* mylist = convert(container_list->data);

	//if (iter->pointer <= data->array + (data->size - 1)*sizeof(void*))
	//	iter->pointer += sizeof(void*);

	if (iter->pointer != (void**)(&(mylist->tail))) {
		Cell_t* next = ((Cell_t*)(*(iter->pointer)))->next;
		iter->pointer = (void**)(&next);
		//iter->pointer = (void**)(&((mylist->head)->prev));
	} else {
		// do nothing, because prev elem is NULL
		printf("WARNING: Cannot reference to previous element of first one !\n");
	}

	/*if ((((Cell_t*)(iter))->next) != data->tail) {
		iter = ((Cell_t*)(iter))->next;
	} else {
		iter = NULL;
	}*/
}

// ============================================================================

void* list_get(Sequential* container_list, Iterator* iter) {

	if (!list_valid_check(container_list)) return NULL;

	return ((Cell_t*)(*(iter->pointer)))->data;
	/*
	List_t* data = convert(container_list->data);

	int len = iter->pointer - data->array;
	int initIndex = len / sizeof(void*);

	if (initIndex < data->size)
		return data->array[initIndex];
	else printf("No element hear!");
	*/
}

// ============================================================================

void list_swap(Sequential* container_list, Iterator* iter1, Iterator* iter2) {

	Cell_t* cell1 = (Cell_t*)(*(iter1->pointer));
    Cell_t* cell2 = (Cell_t*)(*(iter2->pointer));
	void* temp = NULL;

	temp = cell1->data;
	cell1->data = cell2->data;
	cell2->data = temp;

}

// ============================================================================

void list_show(Sequential* container_list) {

	List_t* mylist = convert(container_list);
	Cell_t* cell = mylist->head;

	printf("////////////////////////////");

	while (cell != mylist->tail) {
		printf("\ncell - %p\ncell->prev - %p\ncell->next - %p\ncell->data - %p\n\n",
				cell, cell->prev, cell->next, (char*)(cell->data));
		cell = cell->next;
	}

	printf("\ncell - %p\ncell->prev - %p\ncell->next - %p\ncell->data - %p\n",
			cell, cell->prev, cell->next, (char*)(cell->data));

	printf("\nlist size - %d\n", mylist->size);

	printf("/\\\\\\\\\\\\\\\\\\\\\\\\\\/\n");

}
