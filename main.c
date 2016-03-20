#include<stdio.h>
#include<stdlib.h>
#include"sorted-list.h"

int Compare(void *n1, void *n2)
{
	if(n1>n2)
	{
		return 1;
	}
	if(n1<n2)
	{
		return -1;
	}
	if(n2 == n1)
	{
		return 0;	
	}
return 0;
}
void Destruct( void * buster )
{
	return;
}
void printadd(SortedListPtr buster, int a)
{
	SortedListIteratorPtr ptr =NULL;
	printf("adding %c to list\n",a);	
	printf("new list:\n");
	for(ptr = buster->node; ptr!= NULL; ptr=ptr->next)
	{
		printf("%c\n", ptr->item);	
	}
	
	printf("\n");
	
}
void printremove(SortedListPtr buster, int a)
{
	SortedListIteratorPtr ptr;
	ptr  =NULL;
	printf("removing %c from list\n",a);	
	printf("new list:\n");
	for(ptr = buster->node; ptr!= NULL; ptr=ptr->next)
	{
		printf("# %c\n", ptr->item);	
	}
	
	printf("\n");
	
}
int main(int argc, char ** argv)
{
	char k ='c';
	char b ='d';
	char a= 'e';
	char c ='f';
	char d ='g';
	char e ='h';
	char f ='i' ;
	char g ='j';	
	SortedListPtr buster = SLCreate(*Compare, *Destruct);
	SLInsert(buster, (void *)g);	
	printadd(buster, g);

	SLInsert(buster, (void*) d);	
	printadd(buster, d);
	
	SLInsert(buster, (void *)k);
	printadd(buster, k);

	SLInsert(buster, (void *)b);
	printadd(buster, b);

	SLInsert(buster, (void *)a);
	printadd(buster, a);
	
	SLInsert(buster, (void *)c);
	printadd(buster, c);

	SLInsert(buster, (void *)e);
	printadd(buster, e);

	SLInsert(buster, (void *)f);
	printadd(buster, f);
/*
	SLRemove(buster, (void *)g);	
	printremove(buster, g);

	SLRemove(buster, (void*) d);	
	printremove(buster, d);
	
	SLRemove(buster, (void *)k);
	printremove(buster, k);

	SLRemove(buster, (void *)b);
	printremove(buster, b);

	SLRemove(buster, (void *)a);
	printremove(buster, a);
	
	SLRemove(buster, (void *)c);
	printremove(buster, c);

	SLRemove(buster, (void *)e);
	printremove(buster, e);

	SLRemove(buster, (void *)f);
	printremove(buster, f);

*/







	SLDestroy(buster);
	printf("destroyed\n");
/*	printadd(buster, k);
*/





return 0;
}
