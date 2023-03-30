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


#endif // DEQUE_H_INCLUDED
