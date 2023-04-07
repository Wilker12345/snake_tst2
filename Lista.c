#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

typedef int T;

void init_lista(lst *lista){
    node *sent=(node*) malloc(sizeof(node)); //init poder 1 e sentinela
    lista->sentinela=sent;
    
    node *n=(node*) malloc(sizeof(node)); //init poder 1 e sentinela
    lista->poder1=n;
    lista->poder1->data=0;
   
    node *n2=(node*) malloc(sizeof(node)); //init poder 2
    lista->poder2=n2;
    lista->poder2->data=0;
   
    node *n3=(node*) malloc(sizeof(node)); //init poder 3
    lista->poder3=n3;
    lista->poder3->data=0;
    
    lista->sentinela->prox=lista->poder1;
    lista->sentinela->ant=lista->poder3;
    
    lista->poder1->prox=lista->poder2;
    lista->poder1->ant=lista->poder3;
    lista->poder2->ant=lista->poder1;
    lista->poder2->prox=lista->poder3;
    lista->poder3->ant=lista->poder2;
    lista->poder3->prox=lista->poder1;
    
    lista->tamanho=0;
}

void insere_lista(T dado,lst *lista){
    if(lista->poder1->data==0) lista->poder1->data=dado;
    else if(lista->poder2->data==0) lista->poder2->data=dado;
    else if(lista->poder3->data==0) lista->poder3->data=dado;
    else return;
    lista->tamanho++;
}

void remove_lista(lst *lista){
    if(lista->sentinela->prox->data!=0){
        lista->sentinela->prox->data=0;
        lista->tamanho--;
    }
}

void gira_esquerda(lst *lista){
    node *aux=(node*) malloc(sizeof(node)); //obs.: d->sentinela->prox->prox => elemento do meio da lista 
    aux=lista->sentinela->ant;
    lista->sentinela->ant=lista->sentinela->prox;
    lista->sentinela->prox=lista->sentinela->prox->prox;
    lista->sentinela->prox->prox=aux;
}

void gira_direita(lst *lista){
    gira_esquerda(lista);
    gira_esquerda(lista);
}

int lista_elemento_inicial(lst *lista){
  return lista->sentinela->prox->data;
}

int lista_elemento_meio(lst *lista){
    return lista->sentinela->prox->prox->data;
}

int lista_elemento_final(lst *lista){
  return lista->sentinela->ant->data;
}

int lista_tamanho(lst *lista){
  return lista->tamanho;
}

int vazia(lst *lista){
  return lista->sentinela->prox==lista->sentinela;
}

int cheia(lst *lista,int limite){
  return lista_tamanho(lista)>=limite;
}

