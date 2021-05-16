#ifndef TAB_H
#define TAB_H
#include <stdbool.h>
#include "play.h"

char ** create_tab(char **tab, int *lin, int *col);
void draw_tab(char **tab, int lin, int col);
void init_tab(char **tab, int lin, int col);
void play(char **tab, int lin, int col ,struct player *a);
char ** add_lin(char **tab ,int *lin, int col);
char **add_col(char **tab ,int lin, int *col);
void init_lin(char *lin, int col);
void init_col(char **tab, int lin, int col);
bool check_lin(char **tab, int lin, int col);
bool check_col(char **tab, int lin, int col);
bool check_diagonal(char **tab, int lin, int col);
#endif