#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "cobra.h"
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
	
# endif //esses bag de linux fica onde???

int main() {
    system("clear");
    int midx = tamx_tela >> 1, midy = tamy_tela >> 1;
    int posx_cobra = midx, posy_cobra = midy;
    int posx_fruta = midx - 3, posy_fruta = midy;
    int posx_poder = midx - 3, posy_poder = midy + 2;
    printa_tela();
    printa_cobra();
    printa_fruta();
    printa_poder();
    gotoxy(tamx_tela, tamy_tela);
    printf("A");
    gotoxy(0, 0);
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
                move_cobra(); //nao detecta a funcao kbhit, mesmo tendo inserido sua biblioteca (conio.h)
                cobra_come_fruta();
                cobra_bateu_parede();
            }
            //------------------------poderes---------------------------
            {
                cobra_pega_poder(); //se cobra pegar poder
            }
        }
        // alterna_poder();
        // usa_poder();
        // deleta_poder();
    }
    return 0;
}

int main(void) { //incorporar os 2 mains

  int comando;
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

  return 0;
}

