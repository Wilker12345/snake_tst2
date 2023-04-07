#include "deque.h"
#include <stdio.h>
#include <stdlib.h>

typedef int T;

void InicializaDeque(Deque *deque) {

  deque->inicio=NULL;
  deque->fim=NULL;
  deque->total_elementos=0;
}

void PoeI (int x, int y, Deque *deque)
{

  No *novo = malloc(sizeof(No));

 
  novo->dados.x=x;
  novo->dados.y=y;

   if (deque->total_elementos==0)
  {
    deque->inicio=novo;
    deque->fim=novo;
  }

  else
   {
  novo->next=deque->inicio;
  novo->prev=NULL;
  deque->inicio->prev=novo;
  deque->inicio=novo;
   }
  
    deque->total_elementos++;
  
}

void PoeF (int x, int y, Deque*deque)
{
    No *novo=malloc(sizeof(No));

  novo->dados.x=x;
  novo->dados.y=y;

  if (deque->total_elementos==0)
  {
    deque->inicio=novo;
    deque->fim=novo;
  }

  else
  {
   novo->next=NULL;
  novo->prev=deque->fim;
  deque->fim->next=novo;
  deque->fim=novo; 
  }

    deque->total_elementos++;

}

void TiraI (Deque *deque)
{
  if (deque->total_elementos==1)
  {
    deque->inicio->next=NULL;
    deque->inicio=NULL;
    deque->total_elementos=0;
  }

  else 
  {
  No *aux;
  No* salvar;
  aux=deque->inicio;
  salvar=deque->inicio->next;
  deque->inicio->next->prev=NULL;


    free(aux);
  
    deque->inicio=salvar;
    deque->total_elementos--;
  }

}

void TiraF (Deque *deque)
{

  if (deque->total_elementos==1)
  {
    deque->fim->prev=NULL;
    deque->fim=NULL;
    deque->total_elementos=0;
  }
  else{
    No *aux;
  No* salvar;
  aux=deque->fim;
  salvar=deque->fim->prev;
  deque->fim->prev->next=NULL;


  free(aux);
  deque->fim=salvar;
    deque->total_elementos--;
  }
}
