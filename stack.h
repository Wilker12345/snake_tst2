#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>



typedef struct dados {
  int posicao; //posicao=0 exclusivo da cabeca
  int hp;
} Dados;

typedef struct node {
  Dados dados; 
  struct node *next;

} Node;

typedef struct pilha {
  Node *topo;
  Node *cabeca;
  int tamanho;
} Pilha;

void InicializaPilha(Pilha *pilha);

void MostrarPilha (Pilha *pilha);

void Empilha (Pilha *pilha);

void Desempilha (Pilha *pilha);

void GameSetup (Pilha *pilha);

void PowerUp_hp (Pilha *pilha);

void PowerUp_metade (Pilha *pilha);

#endif