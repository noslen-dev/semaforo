#ifndef LINKED_H
#define LINKED_H

#include "play.h"

struct list_node{ //nos da lista, onde informacoes sobre as jogadas realizadas estarao
  int lin,col;
  int turn;
  char piece;
  struct coordinates place;
  char player_name;
  struct list_node *next;
};

struct list_head{ //cabeca da lista, onde o tabuleiro inicial estara
  char **tab;
  int lin,col;
  struct list_node *next;
};




#endif