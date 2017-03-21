#include "vector.h"

 int main() 
 {
    int n, i, j;
    int a;
    
    scanf_s("%d", &n);
    scanf_s("%d", &a);
    
    Sequential* cont = vector_construct(1, &a, sizeof(void*));
    Iterator* iter1 = cont->iterator_construct(cont);
    Iterator* iter2 = cont->iterator_construct(cont);

	a = 0;

	for(i = 1 ; i < n; i++) 
	{ 
        scanf_s("%d", &a);
        iter1->end(cont, iter1);
        cont->insert(cont, iter1, a);
    }
    
    for(i = 0 ; i < n - 1; i++) 
    {
    	iter1->begin(cont, iter1);
    	iter2->begin(cont, iter2);
    	iter2->next(cont, iter2);
    	for(j = 0 ; j < n - 1 - i; j++) 
    	{    	
    		int a = cont->get(cont, iter1);
    		int b = cont->get(cont, iter2);
    		
        	if(a > b) 
			{           
            	cont->swap(cont, iter1, iter2);
        	}
        	
			iter1->next(cont, iter1);
			iter2->next(cont, iter2);	
		
    	}
	}
	
	iter1->begin(cont, iter1);
	for(i = 0; i < n; i++)
	{
		printf("%d ", cont->get(cont, iter1));
		iter1->next(cont, iter1);
	}

}
