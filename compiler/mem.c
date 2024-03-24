#include "mem.h"

void *safemalloc(int size)
{
  void *p= (void *)malloc(size);
  if(p==NULL)
    {printf("no more memory\n");exit -1;}
  return p;
}
