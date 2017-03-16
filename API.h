#pragma once

typedef struct Iterator Iterator;
typedef struct Sequential Sequential;


typedef struct Iterator {
	
	void** pointer;
	
	void (*begin) (Sequential* container, void** pointer);	
	void (*end) (Sequential* container, void** pointer);
	void (*prev) (Sequential* container, void** pointer);	
	void (*next) (Sequential* container, void** pointer);	
	
} Iterator;


typedef struct Sequential {
	
	void* data;

	Sequential*  (*destruct) (Sequential* container);

	void* (*get) (Sequential* container, void** pointer);
	void  (*insert) (Sequential* container, void** index, void* content);
	void  (*resize) (Sequential* container, int size);
	void  (*swap) (Sequential* container, void** index1, void** index2);

	Iterator* (*iterator_construct) (Sequential* container);
	Iterator* (*iterator_destruct) (Iterator* iterator);
	
} Sequential;

Sequential* vector_create (int size, void** content, int content_size);
Sequential* list_create (int size, void** content, int content_size);
