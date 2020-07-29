#include "unity.h"

#include "LinkedList.h"

void setUp(void)
{
}

void tearDown(void)
{
}

/*add item to head
before:
list
head---->NULL
tail---->NULL
count=1

scenario1:add item to head
	head ------->item2------>item1
				 next------>next----->NULL
	tail  NULL<--prev<------prev
count=2
*/

void test_DoubleLinkedList_add_item_to_head_given_item2_expext_item2_added_to_head_and_tail_still_points_to_item1_and_item1_next_and_item2_prev_point_to_NULL()
{
 ListItem item1 = {NULL, NULL, 14};
 ListItem item2 = {NULL, NULL, 17};
 DoubleLinkedList list = {&item1, &item1, 1};

 int count = DoubleLinkedListAddItemToHead(&list, &item2);
	//test the linked list
 TEST_ASSERT_EQUAL_PTR(&item1, list.tail);
 TEST_ASSERT_EQUAL_PTR(&item2, list.head);
 TEST_ASSERT_EQUAL_PTR(&item1, item2.next);
 TEST_ASSERT_EQUAL_PTR(&item2, item1.prev);
 TEST_ASSERT_EQUAL_PTR(NULL, item1.next);
 TEST_ASSERT_EQUAL_PTR(NULL, item2.prev);
 TEST_ASSERT_EQUAL(2, count);
 TEST_ASSERT_EQUAL(14, item1.data);
 TEST_ASSERT_EQUAL(17, item2.data);
}

/*scenario2:add item to tail
before:
list
head---->NULL
tail---->NULL
count=0

after:
count = 2
	head ------->item1----->item2
				 next------>next----->NULL
	tail  NULL<--prev<------prev
*/

void test_DoubleLinkedList_add_item_to_tail_given_item2_expext_item2_added_to_tail_and_head_still_points_to_item1_and_item2_next_and_item1prev_point_to_NULL()
{
 ListItem item1 = {NULL, NULL, 24};
 ListItem item2 = {NULL, NULL, 27};
 DoubleLinkedList list = {&item1, &item1, 1};
	//add item 2 to head
 int count = DoubleLinkedListAddItemToHead(&list, &item2);
	//test the linked list
 TEST_ASSERT_EQUAL_PTR(&item1, list.tail);
 TEST_ASSERT_EQUAL_PTR(&item2, list.head);
 TEST_ASSERT_EQUAL_PTR(&item2, item1.prev);
 TEST_ASSERT_EQUAL_PTR(&item1, item2.next);
 TEST_ASSERT_EQUAL_PTR(NULL, item1.next);
 TEST_ASSERT_EQUAL_PTR(NULL, item2.prev);
 TEST_ASSERT_EQUAL(2, count);
 TEST_ASSERT_EQUAL(24, item1.data);
 TEST_ASSERT_EQUAL(27, item2.data);
}

/*
before:
list
head --->NULL
tail --->NULL
count=0

after:
head --->NULL
tail --->NULL
count=0
*/

void test_DoubleLinkedList_remove_item_from_head_given_list_expected_nothing_to_be_remove_from_head_and_head_tail_point_to_NULL()
{
 ListItem          *rmv_Item;
 DoubleLinkedList	list ={NULL,NULL,0};
 rmv_Item = DoubleLinkedListRemoveItemFromHead(&list);
	//Test the double linked list
 TEST_ASSERT_EQUAL_PTR(NULL,list.head);
 TEST_ASSERT_EQUAL_PTR(NULL,list.tail);
 TEST_ASSERT_EQUAL(0,list.count);
}


/*
before:
list
head --->item1
        next--->NULL
tail --->NULL
        prev--->NULL
count=1

after:
list
head--->NULL
tail--->NULL
count=0
*/

void test_DoubleLinkedList_remove_item_from_head_given_item1_expected_item1_to_be_removed_and_return_subsequently_head_and_tail_point_to_NULL()
{
 ListItem          *rmv_Item;
 ListItem			    item1={NULL,NULL,34};
 DoubleLinkedList	list={&item1,&item1,1};
 item1.next=NULL;
 item1.prev=NULL;
 rmv_Item = DoubleLinkedListRemoveItemFromHead(&list);
  //Test the double linked list
 TEST_ASSERT_EQUAL_PTR(NULL,list.head);
 TEST_ASSERT_EQUAL_PTR(NULL,list.tail);
 TEST_ASSERT_EQUAL_PTR(NULL,item1.next);
 TEST_ASSERT_EQUAL_PTR(NULL,item1.prev);
 TEST_ASSERT_EQUAL_PTR(34,rmv_Item->data);
 TEST_ASSERT_EQUAL(0,list.count);
}

/*
before:
list
head --->item2--->item1
        next--->next--->NULL
tail
        NULL<--prev<------prev
count=2

after:
list
head --->item1
        next--->NULL
tail
        NULL<--prev
count=1
*/

void test_DoubleLinkedList_remove_item_from_head_given_item2_expected_item2_to_be_removed_and_return_subsequently_and_head_tail_point_to_item1()
{
 ListItem          *rmv_Item;
 ListItem			    item1={NULL,NULL,16};
 ListItem			    item2={NULL,NULL,28};
 DoubleLinkedList	list={&item2,&item1,2};

 item1.next = NULL;
 item1.prev = &item2;
 item2.next = &item1;
 item2.prev = NULL;

 rmv_Item = DoubleLinkedListRemoveItemFromHead(&list);
  //Test the double linked list
 TEST_ASSERT_EQUAL_PTR(&item1,list.head);
 TEST_ASSERT_EQUAL_PTR(&item1,list.tail);
 TEST_ASSERT_EQUAL_PTR(NULL,item1.next);
 TEST_ASSERT_EQUAL_PTR(NULL,item1.prev);
 TEST_ASSERT_EQUAL(28, rmv_Item->data);
 TEST_ASSERT_EQUAL(1,list.count);
}

/*
before:
list
head --->item3--->item2--->item1
          next--->next--->next--->NULL
tail
          NULL<--prev<--prev<---prev
count=3

after:
list
head --->item2--->item1
          next--->next--->NULL
tail
          NULL<--prev<--prev
count=2
*/

void test_DoubleLinkedList_remove_item_from_head_given_item3_expected_item3_to_be_removed_and_return_subsequently_and_head_point_to_item2_and_tail_point_to_item1()
{
 ListItem          *rmv_Item;
 ListItem			    item1={NULL,NULL,15};
 ListItem			    item2={NULL,NULL,32};
 ListItem          item3={NULL,NULL,54};

 item1.next = NULL;
 item1.prev = &item2;
 item2.next = &item1;
 item2.prev = &item3;
 item3.next = &item2;
 item3.prev = NULL;

 DoubleLinkedList	list={&item3,&item1,3};
 rmv_Item = DoubleLinkedListRemoveItemFromHead(&list);
  //Test the double linked list
 TEST_ASSERT_EQUAL_PTR(&item1, list.tail);
 TEST_ASSERT_EQUAL_PTR(&item2, list.head);
 TEST_ASSERT_EQUAL_PTR(&item3, rmv_Item);
 TEST_ASSERT_EQUAL_PTR(NULL, item1.next);
 TEST_ASSERT_EQUAL_PTR(NULL, item2.prev);
 TEST_ASSERT_EQUAL_PTR(NULL, item3.next);
 TEST_ASSERT_EQUAL_PTR(NULL, item3.prev);
 TEST_ASSERT_EQUAL(54, rmv_Item->data);
 TEST_ASSERT_EQUAL(2, list.count);
}

/*
before:
list
head --->NULL
tail --->NULL
count=0

after:
head --->NULL
tail --->NULL
count=0
*/

void test_DoubleLinkedList_remove_item_from_tail_given_list_expected_nothing_to_be_remove_from_head_and_head_tail_point_to_NULL()
{
 ListItem          *rmv_Item;
 DoubleLinkedList	list ={NULL,NULL,0};
 rmv_Item = DoubleLinkedListRemoveItemFromTail(&list);
	//Test the double linked list
 TEST_ASSERT_EQUAL_PTR(NULL,list.head);
 TEST_ASSERT_EQUAL_PTR(NULL,list.tail);
 TEST_ASSERT_EQUAL(0,list.count);
}

/*
before:
list
head --->item1
        next--->NULL
tail
        NULL<--prev
count=1

after:
list
head
        next--->NULL
tail
        NULL<--prev
count=0
*/

void test_DoubleLinkedList_remove_item_from_tail_given_item2_expected_item2_to_be_removed_and_return_subsequently_and_head_tail_point_to_NULL()
{
 ListItem          *rmv_Item;
 ListItem			    item1={NULL,NULL,16};
 item1.next=NULL;
 item1.prev=NULL;

 DoubleLinkedList	list={&item1,&item1,1};
 rmv_Item = DoubleLinkedListRemoveItemFromHead(&list);
  //Test the double linked list
 TEST_ASSERT_EQUAL_PTR(NULL,list.head);
 TEST_ASSERT_EQUAL_PTR(NULL,list.tail);
 TEST_ASSERT_EQUAL_PTR(NULL,item1.next);
 TEST_ASSERT_EQUAL_PTR(NULL,item1.prev);
 TEST_ASSERT_EQUAL_PTR(16,rmv_Item->data);
 TEST_ASSERT_EQUAL(0,list.count);
}

/*
before:
list
head --->item1--->item2
        next--->next--->NULL
tail
        NULL<--prev<------prev
count=2

after:
list
head --->item1
        next--->NULL
tail
        NULL<--prev
count=1
*/

void test_DoubleLinkedList_remove_item_from_tail_given_item2_expected_item2_to_be_removed_and_return_subsequently_and_head_tail_point_to_item1()
{
 ListItem            *rmv_Item;
 ListItem            item1 = {NULL, NULL, 29};
 ListItem            item2 = {NULL, NULL, 11};
 item1.next = &item2;
 item1.prev = NULL;
 item2.next = NULL;
 item2.prev = &item1;

 DoubleLinkedList list = {&item1, &item2, 2};

 rmv_Item = DoubleLinkedListRemoveItemFromTail(&list);
  //test linked ist

 TEST_ASSERT_EQUAL_PTR(&item1, list.tail);
 TEST_ASSERT_EQUAL_PTR(&item1, list.head);
 TEST_ASSERT_EQUAL_PTR(NULL,item1.next);
 TEST_ASSERT_EQUAL_PTR(NULL,item1.prev);
 TEST_ASSERT_EQUAL_PTR(NULL,item2.next);
 TEST_ASSERT_EQUAL_PTR(NULL,item2.prev);
 TEST_ASSERT_EQUAL(11, rmv_Item->data);
 TEST_ASSERT_EQUAL(1, list.count);
}

/*
before:
list
head --->item1--->item2--->item3
          next--->next--->next--->NULL
tail
          NULL<--prev<--prev<---prev
count=3

after:
list
head --->item1--->item2
          next--->next--->NULL
tail
          NULL<--prev<--prev
count=2
*/
void test_DoubleLinkedListRemoveItemFromTail_given_list_which_contains_item1_item2_and_item3_expect_function_return_itemRemoved_as_item3_and_head_points_to_item1_tail_points_to_item2() {
 ListItem            *rmv_Item;
 ListItem            item1 = {NULL, NULL, 1};
 ListItem            item2 = {NULL, NULL, 2};
 ListItem            item3 = {NULL, NULL, 3};

 item1.next = &item2;
 item1.prev = NULL;
 item2.next = &item3;
 item2.prev = &item1;
 item3.next = NULL;
 item3.prev = &item2;
 DoubleLinkedList list = {&item1, &item3, 3};

 rmv_Item = DoubleLinkedListRemoveItemFromTail(&list);
  //test linked list
 TEST_ASSERT_EQUAL_PTR(&item1, list.head);
 TEST_ASSERT_EQUAL_PTR(&item2, list.tail);
 TEST_ASSERT_EQUAL_PTR(&item3, rmv_Item);
 TEST_ASSERT_EQUAL_PTR(NULL, item1.prev);
 TEST_ASSERT_EQUAL_PTR(NULL, item2.next);
 TEST_ASSERT_EQUAL_PTR(NULL, item3.next);
 TEST_ASSERT_EQUAL_PTR(NULL, item3.prev);
 TEST_ASSERT_EQUAL(2, list.count);
 TEST_ASSERT_EQUAL(3, rmv_Item->data);
}