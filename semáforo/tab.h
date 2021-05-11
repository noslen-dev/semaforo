#ifndef TAB_H
#define TAB_H
#include "utils.h"
char ** create_tab(char **tabela, int *linhas, int *colunas);
void draw_tab(char **tabela, int linhas, int colunas);
void init_tab(char **tabela, int linhas, int colunas);
void play(char **tabuleiro, int linhas, int colunas ,struct jogador a);
char ** add_lin(char **tabela ,int *linhas, int colunas);
void **add_col(char **tabuleiro ,int linhas, int *colunas);
void init_lin(char *linha, int colunas);
void init_col(char **tabuleiro, int linhas, int colunas);
#endif