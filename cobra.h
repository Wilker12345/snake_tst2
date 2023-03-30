#ifndef SNAKE_H
#define SNAKE_H //completar o .h

#include <stdio.h>
#include <stdlib.h>

void printa_pontuacao(int i, int j);
void printa_fruta();
void printa_tela();
void printa_cobra();
void gera_fruta();
void cobra_come_fruta();
void cobra_bateu_parede();
void move_cobra();
void gera_poder();
void printa_poder();
void cobra_pega_poder();
void insere_poder_lista();
struct poder *gera_poder_lista(int posx, int posy); 
void InicializaPilha(Pilha *pilha);
void MostrarPilha (Pilha *pilha);
void Empilha (Pilha *pilha);
void Desempilha (Pilha *pilha);
void GameSetup (Pilha *pilha);
void PowerUp_hp (Pilha *pilha);
void PowerUp_metade (Pilha *pilha);

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


// alterna_poder();
// usa_poder();
// deleta_poder();

#endif

