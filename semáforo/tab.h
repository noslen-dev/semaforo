#ifndef TAB_H
#define TAB_H

#define ALLOCATION_ERROR "O programa terminara devido a uma alocacao falhada\n"

void free_tab(char **tab, int lin);
char ** create_tab(int *lin, int *col);
void draw_tab(char **tab, int lin, int col);
char ** add_lin(char **tab ,int *lin, int col);
char **add_col(char **tab ,int lin, int *col);
bool check_lins(char **tab, int lin, int col);
bool check_cols(char **tab, int lin, int col);
bool check_diagonals(char **tab, int lin, int col);
char **create_tab_fixed_lc(int lin, int col);
void tab_copy(char **orig, char **dest, int lin, int col);
#endif