#pragma once

typedef struct Iterator Iterator;
typedef struct Sequential Sequential;


typedef struct Iterator {
	
	void** pointer;
	
	void (*begin) (Sequential* container, Iterator* iter);
	void (*end) (Sequential* container, Iterator* iter);	
	void (*prev) (Sequential* container, Iterator* iter);	
	void (*next) (Sequential* container, Iterator* iter);	
	
} Iterator;


typedef struct Sequential {
	
	void* data;

	Sequential*  (*destruct) (Sequential* container);

	void* (*get) (Sequential* container, Iterator* iter);
	void  (*insert) (Sequential* container, Iterator* iter, void* content);
	void  (*resize) (Sequential* container, int size);
	void  (*swap) (Sequential* container, Iterator* iter1, Iterator* iter2);

	Iterator* (*iterator_construct) (Sequential* container);
	Iterator* (*iterator_destruct) (Iterator* iterator);
	
} Sequential;

Sequential* vector_create (int size, void** content, int content_size);
Sequential* list_create (int size, void** content, int content_size);
