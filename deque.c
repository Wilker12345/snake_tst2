#include "deque.h"
#include <stdio.h>
#include <stdlib.h>

typedef int T;

void init_deque(dq *d){
    node *sent=(node*) malloc(sizeof(node)); //init poder 1 e sentinela
    d->sentinela=sent;
    
    node *n=(node*) malloc(sizeof(node)); //init poder 1 e sentinela
    d->poder1=n;
    d->poder1->data=0;
   
    node *n2=(node*) malloc(sizeof(node)); //init poder 2
    d->poder2=n2;
    d->poder2->data=0;
   
    node *n3=(node*) malloc(sizeof(node)); //init poder 3
    d->poder3=n3;
    d->poder3->data=0;
    
    d->sentinela->prox=d->poder1;
    d->sentinela->ant=d->poder3;
    
    d->poder1->prox=d->poder2;
    d->poder1->ant=d->poder3;
    d->poder2->ant=d->poder1;
    d->poder2->prox=d->poder3;
    d->poder3->ant=d->poder2;
    d->poder3->prox=d->poder1;
    
    d->tamanho=0;
}

void insereI(int dado,dq *d){
    if(d->poder1->data==0) d->poder1->data=dado;
    else if(d->poder2->data==0) d->poder2->data=dado;
    else if(d->poder3->data==0) d->poder3->data=dado;
    else return;
    d->tamanho++;
}

void insereF(int dado,dq *d){
    node *n = (node*) malloc(sizeof(node));
    n->data=dado;
    n->prox=d->sentinela;
    n->ant=d->sentinela->ant;
    d->sentinela->ant=n;
    n->ant->prox=n;
    d->tamanho++;
}

void removeI(dq *d){
    if(d->tamanho){
      node *n=d->sentinela->prox;
      d->sentinela->prox=n->prox;
      n->prox->ant=d->sentinela;
      free(n);
      d->tamanho--;
    }
}

void removeF(dq *d){
    if(d->tamanho){
      node *n=d->sentinela->ant;
      d->sentinela->ant = n->ant;
      n->ant->prox = d->sentinela;
      free(n);
      d->tamanho--;
    }
}

void gira_esquerda(dq *d){
    node *aux=(node*) malloc(sizeof(node)); //obs.: d->sentinela->prox->prox => elemento do meio da lista 
    aux=d->sentinela->ant;
    d->sentinela->ant=d->sentinela->prox;
    d->sentinela->prox=d->sentinela->prox->prox;
    d->sentinela->prox->prox=aux;
}

void gira_direita(dq *d){
    node *aux2=(node*) malloc(sizeof(node)); //obs.: d->sentinela->prox->prox => elemento do meio da lista 
    aux2=d->sentinela->prox->prox;
    d->sentinela->prox->prox=d->sentinela->prox;
    d->sentinela->prox=d->sentinela->ant;
    d->sentinela->ant=aux2;
}


int deque_elemento_inicial(dq *deque){
  return deque->sentinela->prox->data;
}

int deque_elemento_meio(dq *deque){
    return deque->sentinela->prox->prox->data;
}

int deque_elemento_final(dq *deque){
  return deque->sentinela->ant->data;
}

int deque_tamanho(dq *deque){
  return deque->tamanho;
}

int vazia(dq *d){
  return d->sentinela->prox==d->sentinela;
}

int cheia(dq *d,int limite){
  return deque_tamanho(d)>=limite;
}
