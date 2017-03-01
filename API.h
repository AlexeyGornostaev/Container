#pragma once

typedef void* Iterator;
typedef struct Sequential Sequential;

typedef struct Sequential {	
	void* data;
	
	void  (*destructor) (Sequential* container);
	
	void (*begin) (Sequential* container, Iterator pointer);
	void (*end) (Sequential* container, Iterator pointer);
	void (*next) (Sequential* container, Iterator pointer);
	void (*prev) (Sequential* container, Iterator pointer);
	
	void* (*get) (Sequential* container, Iterator pointer);	
	void  (*insert) (Sequential* container, Iterator index, void* content);
	void  (*resize) (Sequential* container, int size);
	void  (*swap) (Sequential* container, Iterator index1, Iterator index2);

	Iterator (*iterator_construct) (struct Sequential* container);
	void (*iterator_destruct) (Iterator pointer);
} Sequential;

Sequential* vector_create (int size, void* content);
Sequential* list_create (int size, void* content);
