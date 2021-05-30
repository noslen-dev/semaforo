#include <stdio.h>
#include "play.h"
#include "bot.h"
#include "utils.h"



/***
 * static void shuffle_arr(array de carateres, dimensao do array)
 * Baralha o array recebido
 */ 
static void shuffle_arr(char *play_arr, int dim){
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
 * static void update_bot(tabuleiro do jogo, numero de linhas, numero de colunas, ponteiro para jogador automatico)
 * Percorre todo o tabuleiro e atualiza as habilidades do jogador automatico
 * com um 0 ou 1
 * 0 indica que o jogador nao pode fazer essa jogada
 * 1 indica que o jogador pode fazer essa jogada
 ***********/ 
static void update_bot(char **tab, int lin, int col,struct player *bot){
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

/**
 * static char choose_play(jogador automatico)
 * Analisa as habilidades do jogador, e constroi um array de carateres em que cada carater representa
 * uma jogada valida que o "jogador" pode fazer.
 * Baralha esse array e devolve um carater que representa a jogada a realizar.
 */ 
static char choose_play(struct player bot){
char play_arr[6]; //6 carateres possiveis
int i=0;
if(bot.ability.green==1)
  play_arr[i++]='G';

if(bot.ability.yellow==1)
  play_arr[i++]='Y';

if(bot.ability.red==1)
  play_arr[i++]='R';

if(bot.ability.lc!=0){
  play_arr[i++]='L';
  play_arr[i++]='C';
}
if(bot.ability.rock!=0)
  play_arr[i++]='S';
shuffle_arr(play_arr,i);
return play_arr[0];
}

/**
 * static int count_pieces(tabuleiro , numero de linhas, numero de colunas, peca)
 * Devolve o numero de "piece" que existem no tabuleiro
 */ 
static int count_pieces(char **tab, int lin, int col, char piece){
int i,j,cnt;
for(i=cnt=0; i<lin; ++i)
  for(j=0; j<col; ++j)
    if(tab[i][j]==piece)
      ++cnt;
return cnt;
}

/***
 * static int interpret_piece(tabuleiro de jogo, numero de linhas, numero de coulunas, peca, peca para ser 
 * substituida)
 * Conforme o valor presente em "piece" coloca em "replace_piece" o carater em que "piece" pode ser jogada
 * (ex: piece='G' entao replace_piece=' ').
 * Devolve o numero de "replace_piece" que existem no tabuleiro
 */ 
static int interpret_piece(char **tab, int lin, int col, char piece, char *replace_piece){
switch(piece){
  case 'G':
  *replace_piece=' ';
  return count_pieces(tab,lin,col,' ');

  case 'S':
  *replace_piece=' ';
  return count_pieces(tab,lin,col,' '); 

  case 'Y':
  *replace_piece='G';
  return count_pieces(tab,lin,col,'G');

  case 'R':
  *replace_piece='Y';
  return count_pieces(tab,lin,col,'Y');
  }
return 0;
}

/***
 * static void update_coord(tabuleiro, numero de linhas, numero de colunas, peca a ser substituida,
 * numero da peca a ser substituida, coordenadas )
 * Percorre o tabuleiro, encontra a "replace_piece" nº "n_piece" e guarda essa localizacao em "place".
 * Ex: se "replace_piece"=='G' e "n_piece"=='2', a funcao coloca em "place" as coordenadas da segunda
 * peca 'G'.
 */ 
static void update_coord(char **tab, int lin, int col, char replace_piece ,int n_piece,struct coordinates *place){
int i,j,cnt=0;
for(i=0; i<lin; ++i)
  for(j=0; j<col; ++j)
    if(tab[i][j]==replace_piece){
      ++cnt;   
      if(cnt==n_piece){
        place->x=i;
        place->y=j;
        return ;
        } 
      }
}

/***
 * bool bot_plays(tabuleiro de jogo, numero de linhas, numero de colunas, peca, coordenadas, 
 * ponteiro para jogador automatico)
 * Realiza uma jogada automaticamente.
 * Devolve 1 se a jogada foi feita com sucesso.
 * Devolve 0 caso contrario(alocacao de linhas ou colunas falhou)
 */ 
bool bot_plays(char ***tab, int *lin, int *col, char *piece, struct coordinates *place, struct player *bot){
int n_piece;
char replace_piece;
update_bot(*tab,*lin,*col,bot);
*piece=choose_play(*bot);
if(*piece!='L' && *piece!='C'){
  n_piece=interpret_piece(*tab, *lin, *col, *piece,&replace_piece);
  n_piece=intUniformRnd(1,n_piece); 
  update_coord(*tab, *lin, *col, replace_piece, n_piece, place);
  (*tab)[place->x][place->y]=*piece;
  if(*piece=='S')
    bot->ability.rock-=1;
    }
else
  if( add_l_c(tab, lin, col,*piece,bot)==NULL)
    return 0;
place->x+=1;
place->y+=1;
return 1; 
}

/***
 * void show_bot_play(jogador automatico, peca, coordenadas do tabuleiro em que a peca foi colocada)
 * Mostra a jogada o jogador automatico fez.
 */
void show_bot_play(struct player bot, char piece, struct coordinates place){
printf("O jogador %c ",bot.name);
if(piece!='L' && piece!='C')
  printf("colocou a peca %c na posicao %d %d\n",piece,place.x,place.y);
else
  printf("adicionou uma %s\n",piece=='C' ? "coluna": "linha");
}


