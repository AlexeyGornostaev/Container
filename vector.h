#include "API.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct Data_t 
{
	int size;
	void** array;
	int elemsize;
	
} Data_t;

Data_t* convert(void* data) 
{
	return (Data_t*)data;	
}

	
Sequential* vectorDestruct (Sequential* vector);
void vectorResize (Sequential* vector, int size);
void vectorSwap (Sequential* vector, Iterator* iter1, Iterator* iter2);
void vectorInsert (Sequential* vector, Iterator* iter, void* content);
void* vectorGet (Sequential* vector, Iterator* iter);

Iterator* vectorIteratorConstruct(Sequential* vector);
Iterator* vectorIteratorDestruct(Iterator* iterator);

void vectorBegin(Sequential* vector, Iterator* iter);
void vectorEnd (Sequential* vector,  Iterator* iter);
void vectorNext (Sequential* vector, Iterator* iter);
void vectorPrev (Sequential* vector, Iterator* iter);

char vectorValidCheck(Sequential* vector);




Sequential* vector_create(int size, void** content, int content_size) 
{
	
	if (size <= 0) 
	{
		perror ("Vector size is invalid!\n");
		return NULL;
	}

	if (content == NULL) 
	{
		perror ("Initial data is invalid!\n");
		return NULL;
	}
	
	Sequential* vector = (Sequential*)calloc(1, sizeof(Sequential));

	vector->data = (void*)calloc(1, sizeof(Data_t));
	Data_t* data = convert(vector->data);
	
	data->array = (void**)calloc(size, sizeof(void*));
	
	int i = 0;
	for (i = 0; i < size; i++) 
		data->array[i] = *(void**)((char*)content + i * content_size);
	
	data->size = size;
	data->elemsize = content_size;
	
	
	vector->destruct = (*vectorDestruct);
	vector->resize = (*vectorResize);
	vector->insert = (*vectorInsert);
	vector->get = (*vectorGet);

	vector->iterator_construct = (*vectorIteratorConstruct);
	vector->iterator_destruct = (*vectorIteratorDestruct);
	
	return vector;

}


char vectorValidCheck(Sequential* vector)
{
	
	if (vector == NULL) 
	{
		perror ("Vector is invalid!\n");
		return 0;
	}
	
	Data_t* data = convert(vector->data);
	
	if (data->size <= 0) 
	{
		perror ("Vector size is invalid!\n");
		return 0;
	}
	
	if (data->array == NULL)
	{
		perror ("Vector initialization is bad!\n");
		return 0;
	}
	
	return 1;
}


Sequential* vectorDestruct(Sequential* vector) 
{
	
	if (vectorValidCheck (vector)) 
	{
		
		Data_t* data = convert(vector->data);
		
		free (data->array);
		free (vector->data);
		free (vector);
		
	}
	
	return NULL;
	
}


void vectorResize(Sequential* vector, int size) 
{

	if (vectorValidCheck(vector)) 
	{

		if (size <= 0)
		{
			perror ("Size is invalid!");
			return;
		}
		
		Data_t* data = convert(vector->data);
		
		int oldSize = data->size;
		data->size = size;
		
		void** newArray =(void**)calloc(size, sizeof(void*));
		
		int i = 0;
		for (i = 0; i < oldSize && i < size; i++) 
			newArray[i] = data->array[i];
		
		if (oldSize < size) 
		{
			int i = 0;
			for (i = oldSize; i < size; i++) 
				newArray[i] = 0;
		}
		
		free(data->array); 
		data->array = newArray;
	
	}
	
}



Iterator* vectorIteratorConstruct(Sequential* vector) 
{
	
	if (!vectorValidCheck(vector)) return NULL;
	
	Iterator* iterator = (Iterator*)calloc(1, sizeof(Iterator));
	
	Data_t* data = convert(vector->data);
	
	iterator->pointer = data->array;
	
	iterator->begin = (*vectorBegin);
	iterator->end = (*vectorEnd);
	iterator->next = (*vectorNext);
	iterator->prev = (*vectorPrev);
	
	return iterator;
	
}

Iterator* vectorIteratorDestruct(Iterator* iterator) 
{	
	free(iterator);
	
	return 0;
}



void vectorInsert(Sequential* vector, Iterator* iter, void* initData) 
{
	
	if (!vectorValidCheck(vector)) return;

	Data_t* data = convert(vector->data);
	int len = iter->pointer - data->array;
	
	vector->resize(vector, data->size + 1);
	
	iter->pointer = data->array + len;
	
	int initIndex = len / sizeof(void*);
	int i = 0;
	for (i = data->size - 2; i >= initIndex; i--) 
	{
		data->array[i + 1] = data->array[i];
	//	printf("%d\n", data->array[i]);
	}
	
	data->array[i+1] = initData; 
	
//	printf("%d\n", data->array[i+1]);
	
}


void* vectorGet (Sequential* vector, Iterator* iter) 
{

	if (!vectorValidCheck(vector)) return NULL;
	
	Data_t* data = convert(vector->data);
	
	int len = iter->pointer - data->array;
	int initIndex = len / sizeof(void*);
	
	return data->array[initIndex];
}



void vectorBegin(Sequential* vector, Iterator* iter)
{

	if (!vectorValidCheck(vector)) return;

	Data_t* data = convert(vector->data);
	
	iter->pointer = data->array;

}



void vectorEnd(Sequential* vector, Iterator* iter)
{
	
	if (!vectorValidCheck(vector)) return;

	Data_t* data = convert(vector->data);
	
	iter->pointer = data->array + (data->size - 1)*sizeof(void*);
	
}



void vectorNext (Sequential* vector, Iterator* iter) 
{

	if (!vectorValidCheck(vector)) return;

	Data_t* data = convert(vector->data);
	
	if (iter->pointer < data->array + (data->size - 1)*sizeof(void*))
		iter->pointer += sizeof(void*);

}



void vectorPrev(Sequential* vector, Iterator* iter) 
{

	if (!vectorValidCheck(vector)) return;

	Data_t* data = convert(vector->data);
	
	if (iter->pointer > data->array) 
		iter->pointer -= sizeof(void*);

}
