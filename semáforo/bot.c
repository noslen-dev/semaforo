#include "bot.h"
#include "play.h"




/**********
 * void update_bot(tabuleiro do jogo, numero de linhas, numero de colunas, jogador atual)
 * Percorre todo o tabuleiro e atualiza os membros da "struct plays" do "jogador a"(jogador automatico)
 * com um 0 ou 1
 * 0 indica que o jogador nao pode fazer essa jogada
 * 1 indica que o jogador pode fazer essa jogada
 ***********/ 
void update_bot(char **tab, int lin, int col,struct player *a){
int i,j;
a->ability.green=a->ability.yellow=a->ability.red=0;
for(i=0; i<lin; ++i)
  for(j=0; j<col; ++j)
    switch(tab[i][j]){
      case ' ': 
        a->ability.green=1;
        break;
      case 'G':
        a->ability.yellow=1;
        break;
      case 'Y':
        a->ability.red=1;
        break;
    }
}