#include "../API.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct data_t
{
	int size;
	void* array;
	
} data_t;

data_t* convert(void* data)
{	
	return (data_t*)data;	
}


Sequential* vector_create(int size, void** content)
{

	if (content == NULL) 
	{
		perror("Invalid data!\n");
		return NULL;
	}
	
	if (size <= 0)
	{
		perror("Invalid vector size!\n");
		return NULL;
	}

	Sequential* vector = (Sequential*)calloc(1, sizeof(Sequential));
	
	vector->data = (void*)calloc(1, sizeof(data_t));
	data_t* data = convert(vector->data);
	
	data->size = size;
	data->array = (void**)calloc(size, sizeof(void*));
	
	for (int i = 0; i < size; i++)
	{
		data->array[i] = content[i];
	}
	
	
	vector->validity_check = (*vectorValidityCheck);
	vector->desturctor = (*vectorDestructor);
	
	
	
	return vector;
}


int vectorValidityCheck(Sequential* vector)
{
	
	if (vector == NULL)
	{
		perror("Invalid vector pointer!\n");
		return 0;
	}
	
	data_t* data = convert(vector->data);
	
	if (data->size <= 0)
	{
		perror("Invalid size of the vector!\n");
		return 0;
	}
	
	if (data->array == NULL)
	{
		perror("Vector was not initialized properly!\n");
		return 0;
	}
	
	return 1;
}


Sequential* vectorDestructor(Sequential* vector)
{
	
	if (vectorValidityCheck(vector))
	{
		
		data_t* data = convert(vector->data);
		
		free(data->array);
		free(vector->vars);
		free(vector);
		
	}
	
	return NULL;
}
