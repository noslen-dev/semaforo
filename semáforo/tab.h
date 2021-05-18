#ifndef TAB_H
#define TAB_H
#include <stdbool.h>
#include "play.h"

#define ALLOCATION_ERROR "O programa terminara devido a uma alocacao falhada\n"
char ** create_tab(char **tab, int *lin, int *col);
void draw_tab(char **tab, int lin, int col);
char ** add_lin(char **tab ,int *lin, int col);
char **add_col(char **tab ,int lin, int *col);
bool check_lin(char **tab, int lin, int col);
bool check_col(char **tab, int lin, int col);
bool check_diagonal(char **tab, int lin, int col);
#endif