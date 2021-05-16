#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "utils.h"
#include "tab.h"
#include "play.h"
#include "linked.h"


/*********
 * init_player(jogador a ser inicializado)
 * incializa as "abilidades especiais" do seu argumento
 * desnecessario inicializar o resto, pois a funcao "update_player" faz-lo
 * da tambem um nome ao jogador
 */ 
static void init_player(struct player *a, char name){
a->ability.rock=a->ability.lc=2;
a->ability.k_prev=1;
a->name=name;
}

static bool check_victory(char **tab, int lin, int col, struct player a){
if(check_lin(tab,lin,col)==1 || check_col(tab,lin,col)==1 || check_diagonal(tab,lin,col)==1){
  printf("O jogador %c venceu o jogo!!!\n\n",a.name);
  return 1;
  }
return 0;
}


static bool check_tie(char **tab, int lin, int col, struct player a){
update_player(tab,lin,col,&a);
return a.ability.green+a.ability.red+a.ability.yellow+a.ability.lc;
}


/*********
 * char menu
 * Apresenta ao utilizador um menu e pergunta se quer jogar contra outra pessoa ou contra
 * o programa
 * Devolve o carater inserido
 */ 
char menu(){
char op;
printf("Bem vindo ao jogo do semaforo!\n" "Escolha a sua opcao\n");
printf("Opcao 1: Jogar contra outro jogador(localmente)\n"
"Opcao 2: Jogar contra o computador\n");
do{
  printf("Opcao: ");
  scanf(" %c",&op);
  if(op!='1' && op!='2'){
    printf("Por favor selecione a opcao 1 ou opcao 2\n");
    clean_stdin();
  }
}while(op!='1' && op!='2');
return op;
}


char ** load_game(char **tab, int *lin, int *col, struct player *a, struct player *b){

}
char ** new_game(char **tab, int *lin, int *col){

}


void game_2p(char *filename){
char **tab,op=1;
int lin,col,turn;
struct player a,b,*aux;
struct d_list *sucessions;
if(filename==NULL){
  init_player(&a, 'A'); init_player(&b,'B'); turn=1;
  if( (tab=create_tab(tab,&lin,&col))==NULL ){
    printf("Nao foi possivel criar o tabuleiro, o programa terminara\n");
    return ;
    }
    init_tab(tab,lin,col);
  }
else{
  if( (tab=load_game(tab,&lin,&col,&a,&b))==NULL ){
    printf("Nao foi possivel criar o tabuleiro, o programa terminara\n");
    return ;
    }
  }
//inicio efetivo do jogo
while(check_victory(tab,lin,col,*aux)!=1 || check_tie(tab,lin,col,*aux)!=1){
  printf("Turno %d, vez do jogador %c\n\n",turn,turn%2==0 ? 'B' : 'A'); //impares B, pares A
  if(turn%2==0){
    aux=&b;
  }
  else{
    aux=&a;
  }
  draw_tab(tab,lin,col);
  update_player(tab,lin,col,aux);
  show_plays(*aux);
  op=ask_play(*aux);
  while(interpret_play(tab,lin,col,op,aux)==1) ;
  add_l_c(&tab, &lin, &col,op,aux);
  //export(sucessions)
  ++turn;
  }
}
