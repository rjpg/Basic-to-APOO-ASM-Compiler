#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "hash.h"
#include "mem.h"


struct Table *symboltable[SIZE];

int off = 0;

unsigned int hash(char *v)
{
  unsigned int h = 0;
  char *s;

  for(s = v; *s; s++)
    h = h*65599 + *s;

  return h;
}

Hash *mkHash(char *v,Hash *next){ 

  Hash *p = (Hash *)safemalloc(sizeof(Hash));

  p->symbol = v;
  off+=1;
  p->offset = off;
  p->next   = p;
  
  return p;
}

void insert(char *v)
{
  
  int index = hash(v) % SIZE;
  
  symboltable[index] = mkHash(v,symboltable[index]);
  
  //print_var(symboltable[index]);
}

void insert_val(char *v,int val)
{
  
  int index = hash(v) % SIZE;
 
  symboltable[index]->binding = val; 
 
}

//procura variavel na tabela de simbolos
void *pesquisa(char *v)
{
  
  int index = hash(v) % SIZE;
  Hash *s;
  for(s = symboltable[index]; s; s = s->next)
    if(0 == strcmp(v, s->symbol))
      return s;
  
  return NULL;
}

void pop(char *v)
{
  int index = hash(v) % SIZE;
  
  symboltable[index] = symboltable[index]->next;
}

char *get_var(Hash *n){
  return n->symbol;
}
int get_val(Hash *n){
  return n->binding;
}

int get_off(Hash *n){
  return n->offset;
}

void print_var(Hash *s){
  printf("Variable: %s\n", get_var(s));
}

