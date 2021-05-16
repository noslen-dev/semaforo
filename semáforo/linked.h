#ifndef LINKED_H
#define LINKED_H

#include "play.h"

struct d_list{
  int lin,col,turn;
  char **tab;
  struct player a,b;
  char piece;
  int x,y;
  struct d_list *prev,*next;
};

struct d_list * create_list();
struct d_list * add_node(struct d_list *curr);


#endif