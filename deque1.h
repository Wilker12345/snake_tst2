#ifndef DEQUE_H_INCLUDED
#define DEQUE_H_INCLUDED

typedef int T;
typedef struct _node{
    int data;
    struct _node *prox,*ant;
} node;

typedef struct _dequeue{
    node *sentinela;
    node *poder1,*poder2,*poder3;
    unsigned int tamanho;
} dq;

typedef struct dados {
  int posicao; //posicao=0 exclusivo da cabeca
  int x;
  int y;
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
void init_deque(dq *);
int deque_elemento_inicial(dq *);
int deque_elemento_meio(dq *);
int deque_elemento_final(dq *);
int cheia(dq *,T );
int vazia(dq *);
int deque_tamanho(dq *);
void insereI(T dado,dq *);
void insereF(T dado,dq *);
void removeI(dq *);
void removeF(dq *);
void gira_esquerda(dq *);
void gira_direita(dq *);

void InicializaPilha(Pilha *pilha);
void MostrarPilha (Pilha *pilha);
void Empilha (Pilha *pilha, int x, int y);
void Desempilha (Pilha *pilha);
void GameSetup (Pilha *pilha, int x, int y);
void PowerUp_hp (Pilha *pilha);
void PowerUp_metade (Pilha *pilha);




// alterna_poder();
// usa_poder();
// deleta_poder();


#endif // DEQUE_H_INCLUDED
