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

#define ISNULL(p, s)                           	\
	if (p == NULL) {                        	\
		perror("'%s' is invalid !\n", s);		\
		return NULL;                        	\
	}

#define ZEROSIZE(p)                         	\
	if (p <= 0) {                           	\
		perror("List size is invalid !\n");		\
		return NULL;                        	\
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
	Сell_t* head;
	Сell_t* tail;
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

//void list_begin(Sequential*, Iterator pointer);									// Return iterator to beginning
void list_end(Sequential*, Iterator pointer);									// Return iterator to end
//void list_next(Sequential*, Iterator pointer);									// Return iterator to next list element
//void list_prev(Sequential*, Iterator pointer);									// Return iterator to previous list element

//void* list_get(Sequential* container_list, Iterator* iter);						// Get value by iterator
void list_assign(Sequential* container_list, Iterator* iter, void* content);	// Assign content [to container] [by iterator]
void list_insert(Sequential* container_list, Iterator* iter, void* content);	// Insert elements
//void list_resize(Sequential* container_list, int size);							// Change size
//void list_swap (Sequential* container_list, Iterator* iter1, Iterator* iter2);	// Swap content

int list_valid_check(Sequential* container_list);

//void list_view(Sequential* container_list);										// View list

// ============================================================================

Sequential* list_construct(int size, void** content, int content_size) {

	// check if ok
	ZEROSIZE(size);
	ISNULL(content, "List");

	// allocate list container
	Sequential* container_list = (Sequential*)calloc(1, sizeof(Sequential));

	// allocate data variable & convert it
	container_list->data = (void*)calloc(1, sizeof(List_t));
	List_t* data = convert(container_list->data);

	// designate functions
	container_list->get = (*list_get);
	container_list->assign = (*list_assign);
	container_list->insert = (*list_insert);
	container_list->resize = (*list_resize);
	container_list->swap = (*list_swap);

	// designate list destructor
	container_list->destruct = (*list_destruct);

	// designate iterator constructor & destructor
	container_list->iterator_construct = (*list_iterator_construct);
	container_list->iterator_destruct = (*list_iterator_destruct);

	// allocate empty mylist of 1 element (cell)
	List_t* mylist = (List_t*)(container_list->data);
	mylist->head = (Cell_t*)calloc(1, sizeof(Cell_t));
	mylist->head->data = NULL;
	mylist->head->prev = NULL;
	mylist->head->next = NULL;
	mylist->tail = mylist->head;
	mylist->size = 1;

	// initializing list container with content
	int i = 0;
	if (size >= 1) {
		// присваиваем первому элементу
		container_list->assign(container_list, (Iterator*)(((Cell_t***)&&(mylist->head))), content[i]); //мб **** и &&&
	}
	Iterator* iter = list_iterator_construct(container_list);
	for (i = 1; i < size; i++) {
		container_list->end(container_list, iter);
		container_list->insert(list, iter, content[i]);
		printf("%d - %s\n", i, (char*)content[i]);
	}

	/*int i = 0;
	for (i = 0; i < size; i++) {
		data->array[i] = *(void**)((char*)content + i * content_size);
	}
	data->size = size;
	data->elemsize = content_size;*/

	return list;
}

// ============================================================================
Sequential* list_destruct(Sequential* container_list) {
	if (list_valid_check(container_list)) {
		List_t* data = convert(list->data) {
		//free(mylist->head);
		free(container_list->data);
		free(container_list);
	}
	return NULL;
}

// ============================================================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Iterator* list_iterator_construct(Sequential* container_list) {

	if (!list_valid_check(container_list)) return NULL;

	Iterator* iterator = (Iterator*)calloc(1, sizeof(Iterator));
	//void** pointer = (void**)calloc(1, sizeof (void*));

	List_t* data = convert(container_list->data);
	//List_t* data = (List*)(container_list->data);

	iterator->pointer = &(data->head);	//Cell_t**
	//*pointer = data->head;

	//return pointer;

	iterator->begin = (*list_begin);
	iterator->end = (*list_end);
	iterator->prev = (*list_prev);
	iterator->next = (*list_next);

	return iterator;
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
void list_end(Sequential* container_list, Iterator* iter) {
	iter->pointer = *((convert(container_list->data))->tail);
}

// ============================================================================
void list_insert(Sequential* container_list, Iterator* iter, void* content) {

 	ISNULL(iter, "List");
	// if (iter == NULL) return;

	List_t* data = convert(container_list->data);
    Cell_t* temp_cell = NULL;
    Cell_t* insertion = (Cell_t*)сalloc(1, sizeof(Cell_t));
    temp_cell = *(iter->pointer);

    insertion->data = content;
    insertion->prev = temp_cell;
    insertion->next = temp_cell->next;

    if (temp_cell->next) {
        temp_cell->next->prev = insertion;
    }
    temp_cell->next = insertion;

    if (!insertion->prev) {
        data->head = insertion;
    }

    if (!insert->next) {
        data->tail = insertion;
    }

    data->size++;
}

// ============================================================================
int list_valid_check(Sequential* container_list) {

	ISNULL(container_list, "List");

	List_t* data = convert(container_list->data);
	ZEROSIZE(data->size);

	/*if (data->array == NULL) {
		perror ("List initialization is bad !\n");
		return 0;
	}*/

	return 1;
}