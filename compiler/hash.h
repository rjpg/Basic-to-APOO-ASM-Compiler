#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SIZE 109

typedef struct Table
{
  char *symbol;
  int binding;
  int offset;
  struct Table *next;
}Hash;

void print_var(Hash *);
char *get_var(Hash *);
unsigned int hash(char *);
Hash make(char *,Hash *);
void insert(char *);
void *pesquisa(char *);
void pop(char *);

