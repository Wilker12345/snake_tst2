#include "cobra.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>

struct poder{ //sugestão struct poder
    int posx;
    int posy;
    struct poder* prox;
    struct poder* ant;
}

int tamx_tela=30,tamy_tela=30; //tamanho da tela (nesse caso) 30x30
int pontuacao=0;
int midx,midy;
int posx_cobra,posy_cobra;  //posicao inicial da minhoca eh o centro da tela (tamx_tela/2 = tamx_tela>>1);
int posx_fruta,posy_fruta;
int posx_poder,posy_poder;
int pontos_ganhos_por_fruta=10;
int gameover=0; //*trocar int por enum (bool)
char direcao='a';

//----------------parte_grafica---------------------------
void printa_pontuacao(int i,int j){
    if(!i && !j) printf("Pontuação: %d\n",pontuacao);
}

void printa_fruta(){
    gotoxy(posx_fruta,posy_fruta);
    printf("*"); //trocar por printa lista
    gotoxy(tamx_tela+100,0);
}

void printa_tela(){
    int i=0,j=0;
    for(i=0;i<tamy_tela;i++){
        for(j=0;j<tamx_tela;j++){
            if(!i || i==tamx_tela-1 || j==0 || j==tamx_tela-1) printf("#"); //printa borda superior e inferior
            else printf(" "); //printa espaco entre laterais
        }
        printf("\n");
    }
}

void printa_cobra(){
	// if(i==posy_cobra && j==posx_cobra) //versao anterior 
    //     printf("0"); //*trocar por printa lista
    //-------------testar com gotoxy
    // if(i==posy_cobra && j==posx_cobra) //versao anterior 
    int i=0,j=0;
    gotoxy(posx_cobra,posy_cobra);
    printf("0");
    gotoxy(tamx_tela+100,0);
}

//----------------parte_logica---------------------------

//-------Estrutura da cobra
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
      

void Empilha (Pilha *pilha)
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

void GameSetup (Pilha *pilha)
{
  Empilha(pilha);
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

//-------logica_cobra/fruta
void gera_fruta(){ //parece estar bugado
    srand(time(NULL)); //*trocar funcao rand por funcao melhor
    posx_fruta=rand()%(tamx_tela-2) + 2;
    if(posx_fruta==posx_poder) posx_fruta=tamx_tela-2;
    srand(time(NULL)); //*trocar funcao rand por funcao melhor
    posy_fruta=rand()%(tamy_tela-2) + 2;
    if(posy_fruta==posy_poder) posy_fruta=tamx_tela-2;
    //corrigir bug: cobra/fruta/poder nao podem aparecer no mesmo lugar
}

void cobra_come_fruta(){
     if(posx_cobra==posx_fruta && posy_cobra==posy_fruta){
        pontuacao+=pontos_ganhos_por_fruta;
        gera_fruta();
        printa_fruta();
    }
}

void cobra_bateu_parede(){
    if(posy_cobra==1||posy_cobra==tamy_tela || posx_cobra==1 || posx_cobra==tamx_tela) gameover=1;
}

void move_cobra(){
    if(kbhit()){
        gotoxy(posx_cobra,posy_cobra);
        printf(" ");
        char c = getch();
        if(c=='\033'){
            getch();
            switch(getch()){ 
                case 'D': 
                    posx_cobra--;
                    break;
                case 'C': 
                    posx_cobra++;
                    break;
                case 'B': 
                    posy_cobra++;
                    break;
                case 'A': 
                    posy_cobra--;
                    break;
            }
        }
        else{
            c=tolower(c);
            switch(c){ 
                case 'a':
                    posx_cobra--;
                    break;
                case 'd':
                    posx_cobra++;
                    break;
                case 's':
                    posy_cobra++;
                    break;
                case 'w':
                    posy_cobra--;
                    break;
                case 'x': 
                    gameover = 1;
                    break;
            }
        }
        gotoxy(posx_cobra,posy_cobra);
        printf("0");
        gotoxy(tamx_tela+100,0);
        printf(" ");
    }
}

//-----------logica_poderes---------------

void gera_poder(){ //parece estar bugado
    srand(time(NULL)); //*trocar funcao rand por funcao melhor
    posx_poder=rand()%(tamx_tela-2) + 2;
    if(posx_poder==posx_fruta) posx_poder=tamx_tela-2;
    srand(time(NULL)); //*trocar funcao rand por funcao melhor
    posy_poder=rand()%(tamy_tela-2) + 2;
    if(posy_poder==posy_fruta) posy_poder=tamy_tela-2;
    //corrigir bug: cobra/fruta/poder nao podem aparecer no mesmo lugar
}

void printa_poder(){
    gotoxy(posx_poder,posy_poder);
    printf("X");
    gotoxy(tamx_tela+100,0);
}

struct poder *gera_poder_lista(int posx, int posy){ 
    struct poder *poder = (struct poder*)malloc(sizeof(struct poder));
    poder->posx = posx;
    poder->posy = posy;
    poder->prox = NULL;
    poder->ant = NULL;
    return poder;
}

void insere_poder_lista(int posx, int posy, struct poder** lista) { //sugestão de incorporação poder na lista
    struct poder* novo = gera_poder_lista(posx, posy);
	struct poder* lista = *lista_ptr;
    if (lista == NULL) {
        novo->prox = novo;
        novo->ant = novo;
    } else {
        novo->prox = lista;
        novo->ant = lista->ant;
        lista->ant->prox = novo;
        lista->ant = novo;
    }
    *lista_ptr = novo;
}

void cobra_pega_poder(){
    if(posx_cobra==posx_poder && posy_cobra==posy_poder){
        gera_poder();
        printa_poder();
        insere_poder_lista();
    }
}

//-----------Pilha---------------

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
