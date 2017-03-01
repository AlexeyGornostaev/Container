#pragma once

typedef void* Iterator;

struct Sequential typedef Sequential;

typedef struct Sequential {
	
	int size;
	void** array;
	
	void  (*destructor) (Sequential* container);
	
	void (*begin) (Sequential* container, Iterator pointer);
	void (*end) (Sequential* container, Iterator pointer);

	void (*next) (Sequential* container, Iterator pointer);
	void (*prev) (Sequential* container, Iterator pointer);
	
	void* (*get) (Sequential* container, Iterator pointer);	
	void  (*insert) (Sequential* container, Iterator index, void* content);
	void  (*resize) (Sequential* container, int size);
	void  (*swap) (Sequential* container, Iterator index1, Iterator index2);

	Iterator (*iterator_init) (struct Sequential* container);
	void (*iterator_destroy) (Iterator pointer);
	
} Sequential;

Sequential* vector_create (int size);
Sequential* list_create (int size);
