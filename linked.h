#ifndef LINKED_H
#define LINKED_H

#include "play.h"


struct list_node{ //nos da lista, onde informacoes sobre as jogadas realizadas estarao
  int turn;
  int lin,col;
  char piece;
  struct coordinates place;
  char player_name;
  struct list_node *next;
};

struct list_head{ //cabeca da lista, onde o tabuleiro inicial estara
  char **tab;
  int lin,col; //as dimensoes do tabuleiro apenas serao alteradas quando um jogo e retomado, a meio do jogo permanecem sempre os mesmos
  struct list_node *next;
};

void free_list_and_tab_in_head(struct list_head *head, int lin);
struct list_head * create_head(int lin, int col);
bool add_node_in_head(struct list_head *head, int lin, int col, char name, char piece ,struct coordinates place);
bool add_node_to_node(struct list_head *head,struct list_node *prev, int lin, int col, char name, char piece, struct coordinates place);
bool reset_tab_in_head(struct list_head *head, int lin);
bool show_k_prev(int k,struct list_head *head, struct list_node *end);
bool place_piece_in_head_tab(struct list_head *head,struct list_node curr);

#endif //LINKED_H