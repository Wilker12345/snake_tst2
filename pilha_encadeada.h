#ifndef PILHA_ENCADEADA_H_INCLUDED
#define PILHA_ENCADEADA_H_INCLUDED

typedef struct dados_pilha {
  int posicao; //posicao=0 exclusivo da cabeca
  int x;
  int y;
  int hp;
} Dados_pilha;

typedef struct node {
  Dados_pilha dados; 
  struct node *next;

} Node;

typedef struct pilha {
  Node *topo;
  Node *cabeca;
  int tamanho;
} Pilha;


void InicializaPilha(Pilha *pilha);
void MostrarPilha (Pilha *pilha);
void Empilha (Pilha *pilha, int x, int y);
void Desempilha (Pilha *pilha);
void GameSetup (Pilha *pilha, int x, int y);
void PowerUp_hp (Pilha *pilha);
void PowerUp_metade (Pilha *pilha);

#endif //PILHA_ENCADEADA_H_INCLUDED
