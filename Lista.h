#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

typedef int T;

typedef struct _node{
    T data;
    struct _node *prox,*ant;
} node;

typedef struct _list{
    node *sentinela;
    node *poder1,*poder2,*poder3;
    unsigned int tamanho;
} lst;

void init_lista(lst *);
int lista_elemento_inicial(lst *);
int lista_elemento_meio(lst *);
int lista_elemento_final(lst *);
int lista_tamanho(lst *);
void insere_lista(T dado,lst *);
void remove_lista(lst *);
void gira_esquerda(lst *);
void gira_direita(lst *);

#endif // LISTA_H_INCLUDED
