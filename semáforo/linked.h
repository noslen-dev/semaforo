#ifndef LINKED_H
#define LINKED_H

#include "play.h"

struct d_list{
  int lin,col,turn;
  struct player a; //jogador que fez a ultima jogada
  char piece; //ultima peca colocada pelo jogador
  int x,y; //coordenadas em que essa peca foi inserida
  struct d_list *prev,*next; 
};

struct d_list * create_list();
struct d_list * add_node(struct d_list *curr);


#endif