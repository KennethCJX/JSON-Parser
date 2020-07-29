#include "LinkedList.h"
#include <stdio.h>


int DoubleLinkedListAddItemToHead(DoubleLinkedList *list, ListItem *Item)
{
	Item->next = list->head;
	((list->head)->prev) = Item;
	list->head = Item;
	Item->prev = NULL;
	list->count = list->count+1;

	return list->count;
}

int DoubleLinkedListAddItemToTail(DoubleLinkedList *listPtr, ListItem *ItemPtr)
{
	ItemPtr->prev = listPtr->tail;
	((listPtr->head)->next) = ItemPtr;
	listPtr-> tail = ItemPtr;
	ItemPtr->next = NULL;
	listPtr->count = listPtr->count+1;
	return listPtr->count;
}	

ListItem* DoubleLinkedListRemoveItemFromHead(DoubleLinkedList *rmvList)
{
ListItem* Item_last;

	if(rmvList->head == NULL) 
{			                
	return NULL;					        
}
  else
{
  Item_last = rmvList->head;			        
  rmvList->head = Item_last->next;		                
	if(rmvList->head == NULL)			        
		rmvList->tail = NULL;
	else
    (rmvList->head)->prev = NULL;
    Item_last->next = NULL;				        
    Item_last->prev = NULL;
    rmvList->count  = rmvList->count-1;				        
}
 return Item_last;					        
}

ListItem* DoubleLinkedListRemoveItemFromTail(DoubleLinkedList *rmvList)
{
	ListItem* Item_last;

	if(rmvList->tail == NULL) 
{			                
	return NULL;					        
}
  else
{
  Item_last = rmvList->tail;			        
  rmvList->tail = Item_last->prev;		                
	if(rmvList->tail == NULL)			        
		rmvList->head = NULL;
	else
    ((rmvList->tail)->next) = NULL;
    Item_last->next = NULL;				        
    Item_last->prev = NULL;
    rmvList->count  = rmvList->count-1;						        
	}
 return Item_last;					        
}

