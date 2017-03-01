#include "../API.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct data_t {
	int size;
	void* array;
} data_t;

data_t* convert(void* data)
{	
	return (data_t*)data;	
}


Sequential* vector_create (int size, void* content)
{

	if (content == NULL) 
	{
		perror ("Invalid initial values array!\n");
		return NULL;
	}
	
	if (size <= 0)
	{
		perror ("Invalid vector size!\n");
		return NULL;
	}

	Sequential* vector = (Sequential*) calloc (1, sizeof (Sequential));
	
	vector->data = (void*) calloc (1, sizeof (data_t));
	data_t* data = convert(vector->data);
	
	data->size = size;
	data->array = (void*) calloc (size, sizeof (void));
	
	for (int i = 0; i < size; i++) {
		data->array[i] = content[i];
	}
	
	return vector;
}
