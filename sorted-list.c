#include<stdio.h>
#include<stdlib.h>
#include"sorted-list.h"
/*
 * SLCreate creates a new, empty, 'SortedList'.
 *
 * SLCreate's parameters will be a comparator (cf) and destructor (df) function.
 *   Both the comparator and destructor functions will be defined by the user as per
 *   the prototypes above.
 *   Both functions must be stored in the SortedList struct.
 * 
 * SLCreate must return NULL if it does not succeed, and a non-NULL SortedListPtr
 *   on success.
 *    */
SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df)
{
	SortedListPtr List =NULL;
	if(cf == NULL || df == NULL)
	{
		return NULL;	
	}
	List =malloc(sizeof(SortedListPtr));       
	List->compare=cf;
	List->destroy=df;
	List->node = SLCreateIterator(List);
	return List;
}

  /*
* SLDestroy destroys a SortedList, freeing all dynamically-allocated memory.
*   
*
*  */

void SLDestroy(SortedListPtr list)
{
	SortedListIteratorPtr ptr2 = NULL;
	SortedListIteratorPtr nextt;
	ptr2 = list->node;
	
	nextt = list->node;
	if(ptr2 == NULL)
	{
		free(list);
		return;
	}
	else
	if(ptr2->next == NULL)
	{
		free(ptr2);
		free(list);
		return;
	}	
	else{	
		while(nextt != NULL)
		{ 
			printf("ptr2->data = %d\n", ptr2->item);
			if(ptr2->next == NULL)
			{
				free(ptr2);
				free(list);
				return;
			}
			nextt = ptr2->next;
			free(ptr2);
			ptr2 = nextt; 
	/*	ptr2->next = NULL;
*/
		}
	}
/*
	if(list->node == NULL)
	{
		free(list);
		return;
	}	
	if(list->node->next == NULL)
	{
		list->destroy(list->node->item);
		free(list->node);
	//	free(list);
		return;
	} 
	SLDestroy(list->);
	*/
	return;
}

 /*
 *  SLInsert inserts a given data item 'newObj' into a SortedList while maintaining the
 *  order and uniqueness of list items.
 * 
 *  SLInsert should return 1 if 'newObj' is not equal to any other items in the list and
 *  was successfully inserted.
 *  SLInsert should return 0 if 'newObj' is equal to an item already in the list or it was
 *  not successfully inserted
 *
 *  Data item equality should be tested with the user's comparator function *
 */


int SLInsert(SortedListPtr list, void *newObj)
{
SortedListIteratorPtr ptr2 = NULL;
SortedListIteratorPtr ptr = list->node;
if(list == NULL)
{
	return 0;
}
if(list->node->item == NULL)
		{
			list->node = SLCreateIterator(list);
			list->node->item = newObj;
			return 1;
		}
	while(ptr != NULL)
	{
	/*
		if(list->node->item == NULL)
		{
			printf("busddddter\n");
			list->node = SLCreateIterator(list);
			ptr->item = newObj;
			return 1;
		}
		*/
		if(list->compare(ptr->item, newObj) == 0) /*first and second are equal */
		{
			return 0;
		}
		if(list->compare(ptr->item, newObj) == -1) /* ptr is less than new object  */
		{
			if(ptr->next != NULL && ptr->prev != NULL) /*Standard Case, N1 and N2 have a prev and a next */
			{
				ptr2 =	SLCreateIterator(list);
				ptr2->item = newObj;
				ptr2->next = ptr;
				ptr->prev->next = ptr2;
				ptr2->prev = ptr->prev;
				ptr->prev = ptr2;
				return 1;
			}
			else 
			if(ptr->next != NULL && ptr->prev == NULL) /*Insert as new first one in list, Ptr has no prev but has next */
			{
				ptr2 = SLCreateIterator(list);
				ptr2->item = newObj;
				ptr2->next = ptr;
				ptr->prev = ptr2;
				ptr2->prev = NULL;
				list->node = ptr2;
				return 1;
			}
			else
			if(ptr->next == NULL && ptr->prev == NULL) /* ptr has no prev or next */
			{
				ptr2 =SLCreateIterator(list);
				ptr2->item = newObj;
				ptr2->next = ptr;
				ptr->prev = ptr2;
				ptr->next = NULL;
				list->node = ptr2;
				return 1;
			}	
			else
			if(ptr->next == NULL && ptr->prev != NULL)/* ptr has a prev but no next */
			{	
				ptr2 =SLCreateIterator(list);
				ptr2->item = newObj;
				ptr2->next = ptr;
				ptr->prev->next = ptr2;
				ptr2->prev = ptr->prev;
				ptr->prev = ptr2;
				ptr->next = NULL;
				return 1;
			}	
			
		}
		if((list->compare(ptr->item, newObj) == 1) && ptr->next == NULL) /* ptr has no next*/
		{
			ptr2 = SLCreateIterator(list);
			ptr2->item = newObj;
			ptr->next = ptr2;
			ptr2->prev = ptr;
			ptr2->next = NULL;
			return 1;
		} 
		if(list->compare(ptr->item, newObj) == 1) /*first is less than second */
		{
			
			ptr= ptr->next;
		}
	/*list->node = list->node->next;
	/list->node->item = newObj;
	*/
	}
	return 0;	
}

/*
* SLRemove should remove 'newObj' from the SortedList in a manner that
*   maintains list order.
*
* SLRemove must not modify the data item pointed to by 'newObj'.
*
* SLRemove should return 1 on success, and 0 on failure.
*/


int SLRemove(SortedListPtr list, void *newObj)
{
	SortedListIteratorPtr ptr;
	SortedListIteratorPtr ptr2 = NULL;
	SortedListIteratorPtr ptr3 = NULL;
				
	if(list == NULL)
	{
		return 0; 
	}
	ptr = list->node;
	if(list->compare(ptr->item,newObj) ==0 && ptr->next != NULL) /* remove head*/
	{
	list->node = ptr->next;	
	list->destroy(ptr->item);	
	ptr3=ptr;
	free(ptr3);
  list->node->prev =NULL;
	
		return 1;
	}
	if(list->compare(ptr->item, newObj) == 0 && ptr->next ==NULL) /* remove sole item in list */
	{
		list->destroy(ptr->item);
		ptr3=ptr;
		free(ptr3);
		list->node = NULL;
		return 1;
	}
	while(ptr->next != NULL)
	{
			
		if(list->compare(ptr->next->item, newObj) == 0)
		{
			if(ptr->next->next != NULL) /* remove middle  */
			{
				ptr3=ptr->next;
				ptr->next = ptr->next->next;	
				ptr->next->prev = ptr;
				list->destroy(ptr->next->item);
				
				free(ptr3);
				return 1;		
			}
			else if(ptr->next->next == NULL ) /*remove last item */
			{
 				ptr2 = ptr->next;
				ptr->next = NULL;
				list->destroy(ptr2);
				return 1;
			}
		}
		
		
	ptr = ptr->next;
	}
	return 0;
}

 /*
 * 119  * SortListIterator allows a SortedList to be easily 'walked' through,
 * 120  *  item by item using repeated calls to 'SLNextItem'.
 * 121  * Each 'SLNextItem' call to a SortedListIterator should result in the 
 * 122  *  next consecutive item in a SortedList, from the beginning to the end.
 * 123  * A SortedListIterator provides a one-way traversal through all of a SortedList
 * 124  *  

 * 139  * SLCreateIterator creates a SortedListIterator for the SortedList pointed to by 'list'.
 * 140  *
 * 141  * SLCreateIterator should return a non-NULL SortedListIteratorPtr on success.
 * 142  * SLCreateIterator should return a NULL SortedListIteratorPtr if it could not
 * 143  *  construct a SortedListIterator, or if the SortedListPtr parameter 'list' is NULL.
 * 144  */


SortedListIteratorPtr SLCreateIterator(SortedListPtr list)
{
	SortedListIteratorPtr ListNode =NULL;
		if(list == NULL)
	{
		return NULL;

	}	
	ListNode = malloc(sizeof(SortedListIteratorPtr));       
	ListNode->next = NULL;
	ListNode->prev = NULL;	
	return ListNode;
}

 /*
 * 150  * SLDestroyIterator destroys a SortedListIterator pointed to by parameter 'iter'.
 * 151  *
 * 152  * SLDestroyIterator should destroy the SortedListIterator, but should NOT
 * 153  *  affect the list used to create the SortedListIterator in any way.
 * 154  */

void SLDestroyIterator(SortedListIteratorPtr iter)
{
				free(iter);	
}

/*
 * 163  * SLNextItem returns a pointer to the data associated with the
 * 164  *  next item in the SortedListIterator's list
 * 165  *
 * 166  * SLNextItem should return a NULL if all of iter's elements have
 * 167  *  been iterated through.
 * 168  *
 * 169  * NB: Be sure to check the length of the list that SortedListIterator holds
 * 170  *         before attempting to access and return an item from it.
 * 171  *         If an item is removed from the list, making it shorter, be careful not
 * 172  *         to try to read and return an item off the end of the list.
 * 173  */


void * SLNextItem(SortedListIteratorPtr iter)
{
SortedListIteratorPtr ptr;
	if(iter==NULL)
	{
		return NULL;
	}
	if(iter->next == NULL)
	{
		return NULL;
	}
	else{
		return iter->next->item;
	}
return ptr;
}


/*
 * 179  * SLGetItem should return a pointer to the current data item
 * 180  *   The current data item is the item that was most recently returned by SLNextItem
 * 181  *   SLGetItem should not alter the data item that SortedListIterator currently refers to
 * 182  *
 * 183  * SLGetItem should return a NULL pointer if the SortedListIterator has been advanced
 * 184  *  all the way through its list.
 * 185  *
 * 186  * NB: Be sure to check the length of the list that SortedListIterator holds
 * 187  *         before attempting to access and return an item from it.
 * 188  *         If an items are removed from the list, making it shorter, be careful not
 * 189  *         to try to read and return an item off the end of the list.
 * 190  */


void * SLGetItem( SortedListIteratorPtr iter )
{
void *  ptr;
if(iter ==NULL)
{
	return NULL;
}
if (SLNextItem(iter) ==NULL)
{
	return NULL;
}
else 
{
	return  SLNextItem(iter);
}
return ptr;
}



