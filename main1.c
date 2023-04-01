#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "deque.h"
#ifdef _WIN32
//bibliotecas windows
    #include <conio.h>
#else
//Linux bibliotecas
//Linux bibliotecas
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

//Linux Constants

//Linux Functions - These functions emulate some functions from the windows only conio header file
//Code: http://ubuntuforums.org/showthread.php?t=549023
void gotoxy(int x,int y)
{
printf("%c[%d;%df",0x1B,y,x);
}

//http://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html
int kbhit(void)
{
 struct termios oldt, newt;
 int ch;
 int oldf;

 tcgetattr(STDIN_FILENO, &oldt);
 newt = oldt;
 newt.c_lflag &= ~(ICANON | ECHO);
 tcsetattr(STDIN_FILENO, TCSANOW, &newt);
 oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
 fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

 ch = getchar();

 tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
 fcntl(STDIN_FILENO, F_SETFL, oldf);

 if(ch != EOF)
 {
ungetc(ch, stdin);
return 1;
 }

 return 0;
}

//http://www.experts-exchange.com/Programming/Languages/C/Q_10119844.html - posted by jos
char getch()
{
char c;
system("stty raw");
c= getchar();
system("stty sane");
//printf("%c",c);
return(c);
}

void clrscr()
{
system("clear");
return;
}
//End linux Functions

#endif
//------Nosso programa comeca aqui, antes eh so umas coisas que usam para escolher as bibliotecas e qual o sistema operacional e tals
int tamx_tela=30,tamy_tela=30; //tamanho da tela (nesse caso) 30x30
int pontuacao=0;
int midx,midy;
int posx_cobra,posy_cobra;//posicao inicial da minhoca eh o centro da tela (tamx_tela/2 = tamx_tela>>1);
int posx_corpo,posy_corpo;
int posx_fruta,posy_fruta;
int posx_poder,posy_poder;
int pontos_ganhos_por_fruta=10;
int gameover=0; //*trocar int por enum (bool)
char direcao='a';
char poder_printado; //poder que esta atualmente na tela
dq lista_poderes;

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
    gotoxy(46,1);
    printf("%c",194);
    gotoxy(35,2);
    printf("Poderes: ");
}

void printa_cobra(Pilha *pilha){
    // if(i==posy_cobra && j==posx_cobra) //versao anterior
    //     printf("0"); //*trocar por printa lista
    //-------------testar com gotoxy
    // if(i==posy_cobra && j==posx_cobra) //versao anterior
    int i=0,j=0;
    Node *aux=pilha->topo;
   
     do
    {
     if (aux->next == NULL)
     {
         gotoxy(aux->dados.x,aux->dados.y);
         
         printf("0");
     }
     
     else
     {
        gotoxy(aux->dados.x,aux->dados.y);
         
         printf("M"); 
     }

      aux=aux->next;
      
    } while (aux!= NULL);
         
         /*gotoxy(posx_cobra,posy_cobra);
         
         printf("0"); */  
        
    

    gotoxy(tamx_tela+100,0);
}

//----------------parte_logica---------------------------

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

void cobra_come_fruta(Pilha *pilha){
     if(pilha->cabeca->dados.x==posx_fruta && pilha->cabeca->dados.y==posy_fruta){
        pontuacao+=pontos_ganhos_por_fruta;
        Empilha(pilha, pilha->cabeca->dados.x-1, pilha->cabeca->dados.y-1);
        gera_fruta();
        printa_fruta();
    }
}

void cobra_bateu_parede(Pilha *pilha){
    if(pilha->cabeca->dados.y==1||pilha->cabeca->dados.y==tamy_tela || pilha->cabeca->dados.x==1 || pilha->cabeca->dados.x==tamx_tela) gameover=1;
}

void printa_lista_poderes(){
    if(deque_elemento_inicial(&lista_poderes)!=0){ //printa elemento inicial. ELemento que fica no meio da lista
        gotoxy(48,2);
        printf("%d",deque_elemento_inicial(&lista_poderes));
    }
    else{ //se nao tiver nao printa nada
        gotoxy(48,2);
        printf(" ");
    }
    if(deque_elemento_meio(&lista_poderes)!=0){ //printa proximo elemento depois do inicial. ELemento que fica no direita da lista
        gotoxy(50,2); //prita poder 1
        printf("%d",deque_elemento_meio(&lista_poderes));
    }
    else{
        gotoxy(50,2);
        printf(" ");
    }
    if(deque_elemento_final(&lista_poderes)!=0){ //printa proximo elemento antes do inicial. ELemento que fica no esquerda da lista
        gotoxy(46,2);
        printf("%d",deque_elemento_final(&lista_poderes));
    }
    else{
        gotoxy(46,2);
        printf(" ");
    }
    gotoxy(tamx_tela+100,0);
}

void move_cobra(Pilha *pilha){
    if(kbhit()){
        char c = getch();
        //move lista
        if(c=='J' || c=='j'){
           gira_esquerda(&lista_poderes);
           printa_lista_poderes();
        }
        else if(c=='K' || c=='k'){
            gira_direita(&lista_poderes);
            printa_lista_poderes();
        }
        //move cobra
        
        Node *aux1, *aux2;
  
        aux1=pilha->topo;
        aux2=pilha->topo;
        int savex, savey;
        savex=aux1->dados.x;
        savey=aux1->dados.y;
  
 int k=0;
  if (pilha->tamanho>1)
  {
      gotoxy(savex,savey);
    printf(" ");
    
    for (k=0;k<(pilha->tamanho-1);k++)
    {
    aux1->dados.x=aux1->next->dados.x;
    aux1->dados.y=aux1->next->dados.y;

    aux1=aux1->next;
      
    }  
  }  
  
        gotoxy(pilha->cabeca->dados.x,pilha->cabeca->dados.y);
        printf(" ");
        if(c=='\033'){
            getch();
            switch(getch()){ // pega as setinhas como entrada
                case 'D': //arrow left
                    pilha->cabeca->dados.x--;
                    break;
                case 'C': // arrow right
                    pilha->cabeca->dados.x++;
                    break;
                case 'B': // arrow down
                    pilha->cabeca->dados.y++;
                    break;
                case 'A': //arrow up
                    pilha->cabeca->dados.y--;
                    break;
            }
        }
        else{
            c=tolower(c);
            switch(c){ //pega as wasd como entrada
                case 'a':
                    pilha->cabeca->dados.x--;
                    break;
                case 'd':
                    pilha->cabeca->dados.x++;
                    break;
                case 's':
                    pilha->cabeca->dados.y++;
                    break;
                case 'w':
                    pilha->cabeca->dados.y--;
                    break;
                case 'x': //*trocar para esc
                    gameover = 1;
                    break;
            }
        }
        gotoxy(pilha->cabeca->dados.x,pilha->cabeca->dados.y);
        printf("0");
        
        //printa corpo da cobra
        for (k=0;k<((pilha->tamanho)-1);k++)
        {
         gotoxy(aux2->dados.x,aux2->dados.y);
         printf("M");   
            aux2=aux2->next;
        }
        
        //colisao com corpo = gameover
        if (pilha->tamanho>0)
        {
          Node *aux=pilha->topo;
        for (k=0;k<(pilha->tamanho);k++)
        {
            if ((aux->dados.x==pilha->cabeca->dados.x) && (aux->dados.y==pilha->cabeca->dados.y) && (aux != pilha->cabeca))
            {
                gameover = 1;
            }
            aux=aux->next;  
        }  
        }
        
        gotoxy(tamx_tela+100,0);
        printf(" ");
        //BUG: ao rotacionar poderes, a cobra vai perdendo corpo
    }
}


//-----------logica_poderes---------------
void gera_poder(){ //parece estar bugado
    srand(time(NULL)); //*trocar funcao rand por funcao melhor
    poder_printado=(rand()%3)+1;
    srand(time(NULL));
    posx_poder=rand()%(tamx_tela-2) + 2;
    if(posx_poder==posx_fruta) posx_poder=tamx_tela-2;
    srand(time(NULL)); //*trocar funcao rand por funcao melhor
    posy_poder=rand()%(tamy_tela-2) + 2;
    if(posy_poder==posy_fruta) posy_poder=tamy_tela-2;
    //corrigir bug: cobra/fruta/poder nao podem aparecer no mesmo lugar
   
}

void printa_poder_tela(){
    gotoxy(posx_poder,posy_poder);
    if(poder_printado==1) printf("X");
    else if(poder_printado==2) printf("Y");
    else if(poder_printado==3) printf("Z");
    gotoxy(tamx_tela+100,0);
}

void insere_poder_lista(){
    if(deque_tamanho(&lista_poderes)<=3) insereI(poder_printado,&lista_poderes); //pode ter no maximo tres poderes
}

void printa_tela_dos_poderes(){
    gotoxy(46,1);
    printf("_____");
    gotoxy(45,2);
    printf("|");
    gotoxy(47,2);
    printf("|");
    gotoxy(49,2);
    printf("|");
    gotoxy(51,2);
    printf("|");
    gotoxy(46,3);
    printf("_____");
}

void cobra_pega_poder(Pilha * pilha){
    if(pilha->cabeca->dados.x==posx_poder && pilha->cabeca->dados.y==posy_poder){
        insere_poder_lista();
        gera_poder();
        printa_poder_tela();
        printa_lista_poderes();
    }
}

int main(){
    Pilha *pilha = malloc(sizeof(Pilha));
    InicializaPilha(pilha);
    system("clear");
    midx=tamx_tela>>1,midy=tamy_tela>>1,posx_cobra=midx,posy_cobra=midy,posx_fruta=midx-3,posy_fruta=midy,posx_poder=midx-3,posy_poder=midy+2;
    GameSetup (pilha, midx, midy);
    init_deque(&lista_poderes);
    gera_poder();
    printa_tela();
    printa_cobra(pilha);
    printa_fruta();
    printa_poder_tela();
    printa_tela_dos_poderes();
    printa_lista_poderes();
    gotoxy(tamx_tela,tamy_tela);
    printf("A");
    gotoxy(0,0);
    while(!gameover){
        // clrscr(); //da clear na janela
        // clrscr();
        //---------------parte visual---------------
        {
            // printa_pontuacao(i,j); /arrumar isto caso necessario (vamos usar a funcao de window como interface grafica, entao a tela atual nao ser precisa)
           
           
        }
        //---------------logica---------------
        {
            //------------------------cobra---------------------------
            {
                move_cobra(pilha); //nao detecta a funcao kbhit, mesmo tendo inserido sua biblioteca (conio.h)
                cobra_come_fruta(pilha);
                cobra_bateu_parede(pilha);
            }
            //------------------------poderes---------------------------
            {
                cobra_pega_poder(pilha); //se cobra pegar poder
            }
        }
        // alterna_poder();
        // usa_poder();
        // deleta_poder();
    }
    return 0;
}
