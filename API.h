#pragma once

typedef void** Iterator;
typedef struct Sequential Sequential;

typedef struct Sequential {
	void* data;

	void  (*destruct) (Sequential* container);

	void (*begin) (Sequential* container, Iterator pointer);	// Iterator to beginning
	void (*end) (Sequential* container, Iterator pointer);		// Iterator to end
	void (*prev) (Sequential* container, Iterator pointer);		// Get iterator to previous element
	void (*next) (Sequential* container, Iterator pointer);		// Get iterator to next element

	void* (*get) (Sequential* container, Iterator pointer);
	void  (*insert) (Sequential* container, Iterator index, void* content);
	void  (*resize) (Sequential* container, int size);
	void  (*swap) (Sequential* container, Iterator index1, Iterator index2);

	Iterator (*iterator_construct) (struct Sequential* container);
	void (*iterator_destruct) (Iterator pointer);
} Sequential;

Sequential* vector_create (int size, void** content, size_t content_size);
Sequential* list_create (int size, void** content, size_t content_size);
