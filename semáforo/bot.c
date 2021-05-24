#include "bot.h"
#include "play.h"
#include "utils.h"
#include <stdio.h>

void static shuffle_arr(char *play_arr, int dim){
char tmp;
int i,index;
for(i=0; i<dim; ++i){
  index=intUniformRnd(0,dim-1);
  tmp=play_arr[i];
  play_arr[i]=play_arr[index];
  play_arr[index]=tmp;
  }
}



/**********
 * void update_bot(tabuleiro do jogo, numero de linhas, numero de colunas, jogador atual)
 * Percorre todo o tabuleiro e atualiza os membros da "struct plays" do player "bot"
 * com um 0 ou 1
 * 0 indica que o jogador nao pode fazer essa jogada
 * 1 indica que o jogador pode fazer essa jogada
 ***********/ 
void update_bot(char **tab, int lin, int col,struct player *bot){
int i,j;
bot->ability.green=bot->ability.yellow=bot->ability.red=0;
for(i=0; i<lin; ++i)
  for(j=0; j<col; ++j)
    switch(tab[i][j]){
      case ' ': 
        bot->ability.green=1;
        break;
      case 'G':
        bot->ability.yellow=1;
        break;
      case 'Y':
        bot->ability.red=1;
        break;
    }
}


char choose_play(struct player bot){
char play_arr[6]; //6 carateres possiveis
int i=0;
if(bot.ability.green==1)
  play_arr[i++]='G';

if(bot.ability.yellow==1)
  play_arr[i++]='Y';

if(bot.ability.red==1)
  play_arr[i++]='R';

if(bot.ability.lc==1){
  play_arr[i++]='L';
  play_arr[i++]='C';
}
if(bot.ability.rock==1)
  play_arr[i++]='S';

shuffle_arr(play_arr,i);

return play_arr[0];
}


bool bot_plays(char ***tab, int *lin, int *col, char *piece, struct coordinates *place, struct player *bot){
update_bot(*tab,*lin,*col,bot);
*piece=choose_play(*bot);
if(*piece!='K' && *piece!='L' && *piece!='C' && *piece!='I'){//carateres nao colocaveis
  place->x=intUniformRnd(0,*lin-1);
  place->y=intUniformRnd(0,*col-1);
  (*tab)[place->x][place->y]=*piece;
}
if(*piece=='L' || *piece=='C')
  if( add_l_c(tab, lin, col,*piece,bot)==NULL)
    return 0;
return 1;
}

void show_bot_play(struct player bot, char piece, struct coordinates place){
printf("O jogador %c ",bot.name);
if(piece!='L' && piece!='C')
  printf("colocou a peca %c na posicao %d %d\n",piece,place.x,place.y);
else
  printf("adicionou uma %s\n",piece=='C' ? "coluna": "linha");
}

