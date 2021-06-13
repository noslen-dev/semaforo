#ifndef PLAY_H
#define PLAY_H

#include <stdbool.h>

struct plays{ //cada membro representa uma jogada que um jogador pode realizar
  bool green;
  bool yellow;
  bool red;
  bool rock;
  int lc;
  bool k_interrupt;
};

struct player{ //estrutura jogador
  char name;
  struct plays ability;
};

struct coordinates{ //coordenadas de uma localizacao do tabuleiro
  int x,y;
};


void update_player(char **tab, int lin, int col,int turn ,struct player *a);
void show_plays(struct player a);
char ask_play(struct player a);
bool interpret_play(char **tab, int lin, int col, char play,struct coordinates place, struct player *a);
void ask_place(struct coordinates *place, int lin, int col);
char **add_l_c(char **tab, int *lin, int *col, char play, struct player *a);

#endif