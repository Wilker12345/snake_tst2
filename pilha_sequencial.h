#ifndef PILHA_SEQUENCIAL_H
#define PILHA_SEQUENCIAL_H

typedef int T;

typedef struct _node_pilha_sequencial{
    int data;
    struct _node *prox,*ant;
} node_pilha_sequencial;

typedef struct _dequeue{
    T *itens;
    int inicio,fim,tamanho_max_itens;
    unsigned int tamanho;
} barra_especial;


void init_barra_especial(barra_especial *,T);
int barra_especial_tamanho(barra_especial *);
void insere_barra_especial(barra_especial *,T dado);

#endif //PILHA_SEQUENCIAL_H_INCLUDED
