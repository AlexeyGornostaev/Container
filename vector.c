#include "../API.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Data_t
{
	int size;
	void* array;
	
} Data_t;

Data_t* convert(void* data)
{	
	return (Data_t*)data;	
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
	
	vector->data = (void*)calloc(1, sizeof(Data_t));
	Data_t* data = convert(vector->data);
	
	data->size = size;
	data->array = (void**)calloc(size, sizeof(void*));
	
	for (int i = 0; i < size; i++)
	{
		data->array[i] = content[i];
	}
	
	
	vector->validity_check = (*vectorValidityCheck);
	vector->desturctor = (*vectorDestructor);
	vector->resize = (*vectorResize);
	vector->itetator_construct(*vectorIteratorConstruct);
	vector->iterator_destruct(*vectorIteratorDestruct);
	
	
	return vector;
}


int vectorValidityCheck(Sequential* vector)
{
	
	if (vector == NULL)
	{
		perror("Invalid vector pointer!\n");
		return 0;
	}
	
	Data_t* data = convert(vector->data);
	
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
		
		Data_t* data = convert(vector->data);
		
		free(data->array);
		free(vector->vars);
		free(vector);
		
	}
	
	return NULL;
}

Iterator vectorIteratorConstruct(Sequential* vector) 
{
	if (!vectorValidityCheck(vector)) return NULL;
	
	Data_t* data = convert(vector->data);
	
	return (Iterator)(data->array);	  
}


Iterator vectorIteratorDestruct(Iterator pointer)
{	
	return NULL;
}


void vectorResize(Sequential* vector, int size)
{

	if (vectorValidityCheck(vector)) 
	{

		if (size <= 0) 
		{
			perror("This size cannot be!\n");
			return;
		}
		
		Data_t* data = convert(vector->data);
		int prevSize = data->size;
		
		data->size = size;
		void** newArray = (void**)calloc(size, sizeof(void*));
		
		for (int i = 0; (i < prevSize) && (i < size); i++) 
			newArray[i] = data->array[i];
			
		free(data->array);
		data->array = newArray;
	
	}
	
}
