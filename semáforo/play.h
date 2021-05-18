#ifndef PLAY_H
#define PLAY_H

#include <stdbool.h>

#define INVALiD_PLAY "Atualmente nao pode fazer essa jogada\n"

#define OCC_POS "Escolheu uma posicao do tabuleiro ja ocupada\n"

struct plays{
  bool green;
  bool yellow;
  bool red;
  int rock;
  int lc;
  bool k_interrupt;
};

struct player{
  char name;
  struct plays ability;
};

void update_player(char **tab, int lin, int col,int turn ,struct player *a);
void show_plays(struct player a);
char ask_play(struct player a);
int interpret_play(char **tab, int lin, int col, char play,int x, int y, struct player *a);
void ask_place(int *x, int *y,int lin, int col);
char **add_l_c(char ***tab, int *lin, int *col, char play, struct player *a);

#endif