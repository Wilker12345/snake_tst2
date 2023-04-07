#include "pilha_sequencial.h"
#include <stdio.h>
#include <stdlib.h>

void init_barra_especial(barra_especial *especial,int limite){ 
    especial->inicio=0; //d->inicio e d->fim funcionam como indices. Ambos comecam em 0
    especial->fim=0;
    especial->tamanho=0;
    especial->tamanho_max_itens=limite;
    especial->itens=(int *) malloc(sizeof(int)*(especial->tamanho_max_itens)); //aloca a memoria necessaria
    //para o vetor
}

void insere_barra_especial(barra_especial *especial,int dado){
    if(!especial->tamanho){ //se o deque estiver vazio
        especial->inicio=especial->fim; //os indices se igualam/ reseta os indices
        especial->itens[especial->fim]=dado;
        especial->tamanho++;
        return;
    }
    if(especial->fim!=especial->tamanho_max_itens-1){ //se o indice d->fim nao for o ultimo (borda do vetor) insere o elemento normalmente
        especial->fim++;
        especial->itens[especial->fim]=dado;
    }
    else{
        especial->fim=0;//se for igual ao ultimo, como o vetor eh circular, logo, de 0 
        // vamos para o primeiro indice do vetor, o indice 0.
        especial->itens[especial->fim]=dado;
    }
    especial->tamanho++;
}

int barra_especial_tamanho(barra_especial *especial){
  return especial->tamanho;
}
