#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct dados {
  int posicao; // posicao 0 = cabeca, resto eh corpo
  int hp;
  int info2;
} Dados;

typedef struct node {
  Dados dados; 
  struct node *next;

} Node;

typedef struct pilha {
  Node *topo;
  int tamanho;
} Pilha;

void InicializaPilha(Pilha *pilha) {

  pilha->topo=NULL;
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
      /*printf("\n A cobra possui %d unidades de corpo (1 cabeca e %d corpos)\n", pilha->tamanho, pilha->tamanho-1);*/
      printf("\nPOSICAO: %d\n", aux->dados.posicao);
      printf("hp: %d\n", aux->dados.hp);
      printf("info2: %d\n", aux->dados.info2);

      aux=aux->next;
      
    } while (aux!= NULL); 
    }
      

void Empilha (Pilha *pilha)
{
  Node *novo=malloc(sizeof(Node));

  if(pilha->tamanho==0) //quer dizer que estamos colocando o primeiro elemento (cabeca)
  {
    novo->next=NULL;
  }
  else
  { 
    novo->next=pilha->topo; 
  }
  
  novo->dados.hp = 1;
  novo->dados.posicao = pilha->tamanho;
  pilha->tamanho++;
  novo->dados.info2 = rand() % 11;

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

void GameSetup (Pilha *pilha)
{
  Empilha(pilha);
}


int main(void) {

  int comando;
  int comeco = 0;
  int pos = 0;
  Pilha *pilha = malloc(sizeof(Pilha));
  srand(time(NULL));

  InicializaPilha(pilha);

  printf("Iniciar Jogo?\n1-SIM\n2-NAO\n\n");
  scanf("%d", &comando);

  if (comando==1)
  {
    GameSetup(pilha);
  }
  else return 0;
  do {
    printf("\n\n\n0 - Sair\n1 - Empilhar\n2 -  Desempilhar\n3 - Mostra o tamanho da pilha\n4 -  Mostrar pilha\n\n "
           "Escolha o número de uma operação: ");

    scanf("%d", &comando);

    switch (comando) {

      case (1):
        {
          Empilha(pilha);
          break;
        }

      case (2):
      {
        Desempilha(pilha);
        break;
      }
      
      case (3):
      printf("-----------------------------");
      printf("\n1 cabeca mais %d unidades de corpo\n", pilha->tamanho-1);
      printf("-----------------------------");
      break;

    case (4): {
      printf("-----------------------------");
      MostrarPilha(pilha);
      printf("-----------------------------");
      break;
    }
  }

  } while (comando != 0);

  printf("%d", pos);
  return 0;
}