#include <stdio.h>
#include "play.h"
#include "tab.h"
#include "utils.h"
//funcoes que auxiliam o jogo

/*******
 * int cell_has_piece(tabuleiro de jogo, coordenadas da peca, peca)
 * Retorna 1 se "piece" estiver na posição tab[x][y]
 * Retorna 0 caso contrario
 */
static int cell_has_piece(char **tab, struct coordinates place, char piece){
return tab[place.x][place.y]==piece ? 1 : 0;
}

/*******
 * bool is_inside(cordenadas de uma peca, numero de linhas e colunas)
 * retorna 1 se x e y estiverem dentro dos limites do tabuleiro
 * retorna 0 caso contrario
 */
static bool is_inside(struct coordinates place, int lin, int col){
return place.x<=lin && place.x>=1 && place.y<=col && place.y>=1 ? 1 : 0;
}



/**********
 * void update_player(tabuleiro do jogo, numero de linhas, numero de colunas, turno atual, jogador atual)
 * Percorre todo o tabuleiro e atualiza os membros da "struct plays" do "jogador a"
 * com um 0 ou 1
 * 0 indica que o jogador nao pode fazer essa jogada
 * 1 indica que o jogador pode fazer essa jogada
 ***********/ 
void update_player(char **tab, int lin, int col, int turn ,struct player *a){
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
if(turn>1)
  a->ability.k_interrupt=1;
}

/**********
 * void print_play(jogador atual)
 * Escreve na consola, todas as jogadas que o jogador atual pode realizar
 *********/ 
void show_plays(struct player a){
printf("\n\nAs jogadas que pode fazer sao:\n"
"%s%s%s",a.ability.green==1 ? "Adicionar uma peca verde numa celula vazia (G)\n" : "\0",
a.ability.yellow==1 ? "Trocar uma peca verde por uma amarela (Y)\n" : "\0",
a.ability.red==1 ? "Trocar uma peca amarela por uma vermelha (R)\n" : "\0");
if(a.ability.rock!=0)
  printf("Colocar uma pedra numa celula vazia (S) (%d restantes)\n",a.ability.rock);
if(a.ability.lc!=0)
  printf("Adicionar uma linha ou coluna (L ou C) (%d restantes) \n",a.ability.lc);
if(a.ability.k_interrupt!=0)
  printf("Ver as k jogadas anteriores(K)\n"
  "Interromper o jogo para ser ou nao retomado posteriormente(I)\n");
}

/**********
 *  int validate_play(jogador atual, carater pressionado pelo utilizador)
 *  Devolve:
 *    0 se o carater pressionado pelo utilizador for invalido, ou se ele nao puder 
 *    realizar essa jogada
 *    1 se a jogada é valida
 *********/ 
static int validate_play(struct player a,char play){
switch(play){
  case 'G':
    if(a.ability.green==0){
      printf(INVALiD_PLAY);
      return 0;
    }
  break;  
  case 'Y':
    if(a.ability.yellow==0){
      printf(INVALiD_PLAY);
      return 0;
    }
  break; 
  case 'R':
    if(a.ability.red==0){
      printf(INVALiD_PLAY);
      return 0;
    }
  break;
  case 'S':
    if(a.ability.rock==0){
      printf(INVALiD_PLAY);
      return 0;
    }
  break;

  case 'L' :
    if(a.ability.lc==0){
      printf(INVALiD_PLAY);
      return 0;
    }
  break;

  case 'C' :
    if(a.ability.lc==0){
      printf(INVALiD_PLAY);
      return 0;
    }
  break;
  case 'I' : 
  if(a.ability.k_interrupt==0){
      printf(INVALiD_PLAY);
      return 0;
  }
  break;
  case 'K' : 
    if(a.ability.k_interrupt==0){
      printf(INVALiD_PLAY);
      return 0;
    }
  break;
  default: 
    printf("Por favor digite um carater valido\n");
    return 0;
  break;
 }
return 1;
}


/**********
 *  char ask_play(jogador em questao)
 *  pede por um carater ao utilizador até ele digitar um carater válido,
 *  ou seja, uma jogada que possa fazer no momento
 *  devolve essa jogada
 *********/ 
char ask_play(struct player a){
char play;
bool flag;
printf("\n\nDigite uma jogada das listadas acima: ");
do{
  scanf(" %c",&play);
  if( ( flag=validate_play(a,play) )==0 ){
    printf("Por favor digite uma jogada das listadas acima: ");
    clean_stdin();
  }
}while(flag==0);
clean_stdin();
return play;
}


/*******
 * void ask_place(cordenadas de uma celula do tabuleiro, numero de linhas e colunas)
 * Obriga o utilizador a introduzir coordenadas dentro do tabuleiro e num formato valido
 * Coloca as coordenadas inseridas nos parametros "x" e "y".
 */
void ask_place(struct coordinates *place, int lin, int col){
int flag=0;
place->x=place->y=-1;
printf("Digite as coordenadas do tabuleiro em que quer inserir a peca: ");
do{
  if( ( flag=scanf("%d%d",&place->x,&place->y) ) !=2){
    printf("Digite as coordenadas no formato certo x y: ");
    clean_stdin();
    continue;
  }
  if(is_inside(*place,lin,col)==0)
    printf("Digite coordenadas validas: ");
  clean_stdin();
 }while(flag!=2 || is_inside(*place,lin,col)==0);
}


/*******
 * int interpret_play(tabuleiro de jogo, numero de linhas, numero de colunas
 * ,peca, coordenadas dessa pessa, jogador a ser alterado)
 * Recebe uma peca "play" e se for valida coloca-a no tabuleiro e decrementa as
 * habilidades do jogador, se for necessario.
 * Retorna 0 se a jogada for valida
 * Retorna 1 e exibe uma mensagem de erro se a jogada for invalida.
 */
int interpret_play(char **tab, int lin, int col, char play,struct coordinates place, struct player *a){
--place.x; --place.y;
switch(play){
  case 'G': //inserir peça verde
    if(cell_has_piece(tab,place,' ')==0){ //se nao tiver ' ' nao se pode meter verde
      printf(OCC_POS);
      return 1;
    }
    tab[place.x][place.y]='G';
    break;
  case 'Y' : //trocar verde por amarela
    if(cell_has_piece(tab,place,'G')==0){
      printf("Nessa posicao nao esta uma peca verde para ser trocada\n");
      return 1;
    }
    tab[place.x][place.y]='Y';
    break;
  case 'R': //inserir pedra
    if(cell_has_piece(tab,place,'Y')==0){
      printf("Nessa posicao nao esta uma peca amarela para ser trocada\n");
      return 1;
    }
    tab[place.x][place.y]='R';
    break;

    case 'S': //inserir pedra
    if(cell_has_piece(tab,place,' ')==0){
      printf(OCC_POS);
      return 1; 
    }
    tab[place.x][place.y]='S';
    a->ability.rock-=1;
    break;
  }
return 0;
}


/*******
 * char ** add_l_c(endereco do tabuleiro de jogo, ponteiro para o numero de linhas e colunas,
 * peca, jogador a ser alterado)
 * conforme o valor de "play"('C' ou 'L'), adiciona uma linha ou uma colunas e decrementa
 * a habilidade de inserir linhas ou colunas num utilizador.
 * Se inserir uma linha atualiza o tabuleiro do jogo.
 * Em caso de sucesso devolve o tabuleiro do jogo.
 * Em caso de erro retorna NULL
 */
char **add_l_c(char ***tab, int *lin, int *col, char play, struct player *a){
char **aux;
if(play=='C'){
  if( ( aux=add_col(*tab,*lin,col) )==NULL)
    return NULL;
  a->ability.lc-=1;
 }
if(play=='L'){
  if( ( aux=add_lin(*tab,lin,*col) )==NULL)
    return NULL;
  *tab=aux;
  a->ability.lc-=1;
}
return *tab;
}