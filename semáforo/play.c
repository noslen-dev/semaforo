#include <stdio.h>
#include "play.h"
#include "tab.h"
#include "utils.h"
//funcoes que auxiliam o jogo

//diz se uma posição do tabuleiro tem uma certa peça
static int cell_has_piece(char **tab, int x, int y, char piece){
return tab[x][y]==piece ? 1 : 0;
}


//interpreta a jogada, é sempre um carater valido
int interpret_play(char **tab, int lin, int col, char play, struct player *a){
int x,y;
switch(play){
  case 'G': //inserir peça verde
    ask_place(&x,&y,lin,col);
    if(cell_has_piece(tab,x,y,' ')==0){ //se nao tiver ' ' nao se pode meter verde
      printf(OCC_POS);
      return 1;
    }
    tab[x][y]='G';
    break;
  case 'Y' : //trocar verde por amarela
    ask_place(&x,&y,lin,col);
    if(cell_has_piece(tab,x,y,'G')==0){
      printf("Nessa posicao nao esta uma peca verde para ser trocada\n");
      return 1;
    }
    tab[x][y]='Y';
    break;
  case 'R': //inserir pedra
    ask_place(&x,&y,lin,col);
    if(cell_has_piece(tab,x,y,'Y')==0){
      printf("Nessa posicao na esta uma peca amarela para ser trocada\n");
      return 1;
    }
    tab[x][y]='R';
    break;

    case 'S': //inserir pedra
    ask_place(&x,&y,lin,col);
    if(cell_has_piece(tab,x,y,' ')==0){
      printf(OCC_POS);
      return 1; 
    }
    tab[x][y]='S';
    a->ability.rock-=1;
    break;
  }
return 0;
}

/**********
 * void play(tabuleiro do jogo, numero de linhas, numero de colunas, jogador atual)
 * Percorre todo o tabuleiro e atualiza os membros da "structt plays" do "jogador a"
 * com um 0 ou 1
 * 0 indica que o jogador nao pode fazer essa jogada
 * 1 indica que o jogador pode fazer essa jogada
 ***********/ 
void update_player(char **tab, int lin, int col ,struct player *a){
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


/**********
 * void print_play(jogador atual)
 * Escreve na consola, todas as jogadas que o jogador atual pode realizar
 *********/ 
void show_plays(struct player a){
printf("\n\nAs jogadas que pode fazer sao:\n"
"%s%s%s%s%s%s", a.ability.green==1 ? "Adicionar uma peca verde numa celula vazia (G)\n" : "\0",
a.ability.yellow==1 ? "Trocar uma peca verde por uma amarela (Y)\n" : "\0",
a.ability.red==1 ? "Trocar uma peca amarela por uma vermelha (R)\n" : "\0",
a.ability.rock!=0 ? "Colocar uma pedra numa celula vazia (S)\n" : "\0",
a.ability.lc!=0 ? "Adicionar uma linha ou coluna (L || C)\n" : "\0",
a.ability.k_prev!=0 ? "Ver as k jogadas anteriores(K)\n" : '\0');
printf("Interromper o jogo para ser ou nao retomado posteriormente(I)\n");
}


/**********
 *  char ask_play(jogador em questao)
 *  pede por um carater ao utilizador até ele digitar um carater válido,
 *  ou seja, uma jogada que possa fazer no momento
 * devolve essa jogada
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


/**********
 *  int validate_play(jogador atual, carater pressionado pelo utilizador)
 *  Devolve:
 *    0 se o carater pressionado pelo utilizador for invalido, ou se ele nao puder 
 *    realizar essa jogada
 *    1 se a jogada é valida
 *********/ 
int validate_play(struct player a,char play){
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
  case 'I' : break;
  default: 
    printf("Por favor digite um carater valido\n");
    return 0;
  break;
 }
return 1;
}

static bool is_inside(int x, int y, int lin, int col){
return x<=lin-1 && x>=0 && y<=col-1 && y>=0 ? 1 : 0;
}

void ask_place(int *x, int *y,int lin, int col){
int flag=0;
*x=*y=-1;
printf("Digite as coordenadas do tabuleiro em que quer inserir a peca: ");
do{
  if( ( flag=scanf("%d%d",x,y) ) !=2){
    printf("Digite as coordenadas no formato certo x y: ");
    clean_stdin();
    continue;
  }
  if(is_inside(*x,*y,lin,col)==0)
    printf("Digite coordenadas validas: ");
  clean_stdin();
 }while(flag!=2 || is_inside(*x,*y,lin,col)==0);
}



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