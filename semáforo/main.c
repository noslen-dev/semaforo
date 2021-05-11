#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "tab.h"



int main(){
int linhas, colunas;
struct jogador a;
initRandom();
char **tabela=create_tab(tabela,&linhas,&colunas);
init_tab(tabela,linhas,colunas);
draw_tab(tabela,linhas,colunas);

add_col(tabela,linhas,&colunas);
add_col(tabela,linhas,&colunas);
printf("\n\n");
tabela[2][2]='X';
draw_tab(tabela,linhas,colunas);




return 0;
}