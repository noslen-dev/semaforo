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
a->ability.k_interrupt=0;
a->name=name;
}


/*********
 * check_victory(tabuleiro de jogo, numero de linhas, numero de colunas, jogador que pode
 * ter vencido)
 * Verifica se o jogador 'a' venceu o jogo e em caso afirmativo retorna 1 e escreve uma 
 * mensagem, seguida de um desenho do tabuleiro
 * Em caso de nao vitoria retorna 0.
 */ 
static bool check_victory(char **tab, int lin, int col, struct player a){
if(check_lin(tab,lin,col)==1 || check_col(tab,lin,col)==1 || check_diagonal(tab,lin,col)==1){
  printf("O jogador %c venceu o jogo!!!\n\n",a.name);
  draw_tab(tab,lin,col);
  return 1;
  }
return 0;
}

/*********
 * check_tie(tabuleiro de jogo, numero de linhas, numero de colunas, jogadores)
 * Acede às habilidades do jogador 'a' e 'b' para determinar se houve um empate.
 * Devolve 1 e escreve uma mensagem seguida do tabuleiro em caso afirmativo
 * Devolve 0 se nao houve empate
 */ 
static bool check_tie(char **tab, int lin, int col, struct player a, struct player b){
update_player(tab,lin,col,0,&a);
return a.ability.green+a.ability.red+a.ability.yellow+a.ability.lc+
b.ability.green+b.ability.red+b.ability.yellow+b.ability.lc;
}


/*********
 * int get_k(numero de linhas, numero de colunas, turno atual)
 * Obriga o utilizador a introduzir um numero de jogadas valido para ver.
 * k in [1, turn-1].
 * devolve o k inserido pelo utilizador.
 */ 
static int get_k(int turn){
int k;
int flag=0;
printf("Digite o numero de jogadas que quer ver atras: ");
do{
  if( ( flag=scanf("%d",&k) ) !=1){
    printf("Digite um numero por favor ");
    clean_stdin();
    continue;
  }
  if(k>=turn || k<=0)
    printf("Digite um k valido entre 1 e %d: ",turn-1);
  clean_stdin();
 }while(flag!=1 || k>=turn || k<=0 );
}

/*********
 * char menu()
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



void game_2p(char *filename){
char **tab,op=1;
int lin,col,turn,x,y,k;
struct player a,b,*aux;
struct d_list *sucessions;
if(filename==NULL){
  init_player(&a, 'A'); init_player(&b,'B'); turn=1;
  if( (tab=create_tab(tab,&lin,&col))==NULL ){
    printf("Nao foi possivel criar o tabuleiro, o programa terminara\n");
    return ;
    }
    if( (sucessions=create_list() )==NULL){
      //
    }
      
  }
else{
  if( (tab=load_game(tab,&lin,&col,&a,&b))==NULL ){ //load_tab, load players, load_list
    printf("Nao foi possivel criar o tabuleiro, o programa terminara\n");
    return ;
    }
  }
//inicio efetivo do jogo
while(check_victory(tab,lin,col,*aux)!=1 || check_tie(tab,lin,col,a,b)!=1){
  printf("Turno %d, vez do jogador %c\n\n",turn,turn%2==0 ? 'B' : 'A'); //impares B, pares A
  if(turn%2==0){
    aux=&b;
  }
  else{
    aux=&a;
  }
  draw_tab(tab,lin,col);
  update_player(tab,lin,col,turn,aux);
  show_plays(*aux);
 start: op=ask_play(*aux);
  if(op!='K' && op!='L' && op!='C' && op!='I') //carateres nao colocaveis
    do{
      ask_place(&x,&y,lin,col);  
    }while(interpret_play(tab,lin,col,op,x,y,aux)==1); 
  else
    if(op=='L' || op=='C'){
      if( add_l_c(&tab, &lin, &col,op,aux)==NULL)
        return ;
      }
    else{ //K e I
      printf("Escolheu carateres especiais\n");
      goto start;
    }
  ++turn;
  }
}
