#include "Memalloc.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void *memAlloc(int data_size){
  return malloc(data_size);
}
 
void memFree (void *ptr){
  free(ptr);
}
