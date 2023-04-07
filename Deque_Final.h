#ifndef DEQUE_H_INCLUDED
#define DEQUE_H_INCLUDED

typedef int T;

typedef struct dados {
  int posicao; //posicao=0 exclusivo da cabeca
  int x;
  int y;
  int hp;
} Dados;

typedef struct no {
    Dados dados;
  struct no *next;
   struct no *prev;

} No;

typedef struct 
{
  No *inicio;
  No *fim;
  int total_elementos;
} Deque;

void InicializaDeque(Deque *deque);

void PoeI (int x, int y, Deque *deque);

void PoeF (int x, int y, Deque*deque);

void TiraI (Deque *deque);

void TiraF (Deque *deque);

#endif // DEQUE_H_INCLUDED
