#include "pilha_encadeada.h"
#include <stdio.h>
#include <stdlib.h>

typedef int T;

void InicializaPilha(Pilha *pilha) {
  pilha->topo=NULL;
  pilha->cabeca=NULL;
  pilha->tamanho=0;

}

void MostrarPilha (Pilha *pilha)
{
  Node *aux;
  
  aux=pilha->topo;
  

  if (pilha->tamanho==0)
  {
    printf("\nPilha Vazia!\n");
    return;
  }
  do
    {
      printf("\nPOSICAO: %d\n", aux->dados.posicao);
      printf("hp: %d\n", aux->dados.hp);

      aux=aux->next;
      
    } while (aux!= NULL); 
 }
      

void Empilha (Pilha *pilha, int x, int y)
{
  Node *novo=malloc(sizeof(Node));

  if(pilha->tamanho==0) 
  {
    //Será percorrido durante a funcao GameSetup, que prepara a cobra para o jogo -> *cabeca sempre aponta para a cabeca da cobra.
    novo->next=NULL;
    pilha->cabeca=novo;
  }
  else
  { 
    novo->next=pilha->topo; 
  }
  
  novo->dados.hp = 1;
  novo->dados.posicao = pilha->tamanho;
  novo->dados.x=x;
  novo->dados.y=y;
  pilha->tamanho++;

  pilha->topo=novo;
  
}

void Desempilha (Pilha *pilha)
{

  if (pilha->tamanho==0)
  {
    printf("-----------------------------");
    printf("\nPilha vazia, nao eh possivel retirar elementos!\n");
    printf("-----------------------------");
    return;
  }
  else
  {
  Node *aux;
  Node *salvar;
  aux = pilha->topo;
  salvar = pilha->topo->next;

  free(aux);

  pilha->topo=salvar;
  pilha->tamanho--;
    
  }
}

void GameSetup (Pilha *pilha, int x, int y)
{
  Empilha(pilha, x, y);
}

void PowerUp_hp (Pilha *pilha)
{
  pilha->cabeca->dados.hp++;
}

void PowerUp_metade (Pilha *pilha)
{
  Node *aux=pilha->topo;

  int i=0;
  
  do
    {
      Desempilha(pilha);
      i++;
    } while(i<=(pilha->tamanho)/2);

}
