#ifndef SNAKE_H
#define SNAKE_H //completar o .h

void printa_pontuacao(int i, int j);
void printa_fruta();
void printa_tela();
void printa_cobra();
void gera_fruta();
void cobra_come_fruta();
void cobra_bateu_parede();
void move_cobra();
void gera_poder();
void printa_poder();
void cobra_pega_poder();
void insere_poder_lista();
struct poder *gera_poder_lista(int posx, int posy); 
// alterna_poder();
// usa_poder();
// deleta_poder();

#endif

