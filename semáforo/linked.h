#ifndef LINKED_H
#define LINKED_H

#include "play.h"

struct list_node{
  int lin,col;
  int turn;
  char piece;
  int x,y;
  struct player a;
};

struct list_head{
  char **tab;
  int lin,col;
  int turn;
  char piece;
  int x,y;
  struct player a;
  struct lis_node *next;
};







#endif