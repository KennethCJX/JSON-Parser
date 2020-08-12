#include "unity.h"
#include <stdio.h>
#include <malloc.h> 
#include "Memalloc.h"
#include "mock_Memalloc.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void test_memAlloc(void)
{
  int ptr = (int*)malloc(sizeof(int));
  memFree(ptr);
}