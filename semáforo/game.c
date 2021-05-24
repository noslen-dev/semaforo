#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "utils.h"
#include "tab.h"
#include "play.h"
#include "linked.h"
#include "files.h"
#include "bot.h"






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

void ask_player(char ***tab, int *lin, int *col, struct coordinates *place, struct player *aux, int turn, char *piece){
draw_tab(*tab,*lin,*col);
update_player(*tab,*lin,*col,turn,aux);
show_plays(*aux);
*piece=ask_play(*aux);
if(*piece!='K' && *piece!='L' && *piece!='C' && *piece!='I') //carateres nao colocaveis
    do{
      ask_place(place,*lin,*col);  
    }while(interpret_play(*tab,*lin,*col,*piece,*place,aux)==1);
if(*piece=='L' || *piece=='C')
    if( add_l_c(tab, lin, col,*piece,aux)==NULL)
      return ;
}


/****
 * static bool load_players(jogador a, jogador b)
 * Abre o ficheiro "jogo.bin" e escreve e carrega os jogadores apontados por "a" e "b"
 * com os valores que tinham quando o jogo foi interrompido
 * Devolve 1 em caso de sucesso.
 * Devolve 0 em caso de erro.
 */
static bool load_players(struct player *a , struct player *b){
FILE *fp;
if( ( fp=fopen("jogo.bin","rb") )==NULL ){
  printf("Nao foi possivel abrir o ficheiro que continha informacao para retomar o jogo\n");
  return 0;
  }
fseek(fp,sizeof(bool),SEEK_SET); //saltar o game_mode
fread(a,sizeof(struct player),1,fp);
fread(b,sizeof(struct player),1,fp);
fclose(fp);
return 1;
}




/***
 * static bool load_tab_list(tabuleiro de jogo, numero de linhas, numero de colunas,
 * lista ligada com os estados do tabuleiro)
 * Abre o ficheiro "jogo.bin" e repoe o tabuleiro de jogo, as suas dimensoes, a lista ligada que contem
 * os estados do jogo, e o ponteiro que na funcao "game" aponta para o no "turn",
 * ao estado em que estavam antes de o jogo ser interrompido.
 * Devolve 1 em caso de sucesso.
 * Devolve 0 em caso de erro.
 */ 
static bool load_tab_list(char ***tab, int *lin, int *col, int *turn, struct list_head **states, struct list_node **end){
struct list_node temp, *curr;
FILE *fp;
if( ( fp=fopen("jogo.bin","rb") )==NULL ){
  printf("Nao foi possivel abrir o ficheiro que continha informacao para retomar o jogo\n");
  return 0;
  }
//saltar o que nao interessa
fseek(fp,sizeof(bool),SEEK_SET); fseek(fp,sizeof(struct player),SEEK_CUR); fseek(fp,sizeof(struct player),SEEK_CUR);
fread(lin,sizeof(int),1,fp); fread(col,sizeof(int),1,fp);

if ( ( *states=create_head(*lin,*col) )==NULL ){
  printf("O programa terminara\n");
  return 0;
  }
fread(&temp,sizeof(struct list_node),1,fp);
add_node_in_head(*states,temp.lin,temp.col,temp.player_name,temp.piece,temp.place);
curr=(*states)->next;
place_piece(*states,*curr);

while( fread(&temp,sizeof(struct list_node),1,fp) ==1 ){
  add_node_to_node(*states,curr,temp.lin,temp.col,temp.player_name,temp.piece,temp.place);
  curr=curr->next; 
  place_piece(*states,*curr); 
  }

*lin=curr->lin; *col=curr->col; *turn=curr->turn+1;
*end=curr;//atualizar o turno da lista

*tab=create_tab_fixed_lc(*lin,*col);
tab_copy( (*states)->tab,*tab,*lin,*col);
if(reset_tab(*states,curr)==0 ){
  printf("O programa ira terminar\n");
  return 0;
  }

return 1;
}


void show_k_prev_info(int turn, struct list_head *states, struct list_node *curr){
int k;
k=get_k(turn);
printf("As %d jogadas anteriores foram: \n",k);
show_k_prev(k,states,curr);
printf("Pressione qualquer tecla para voltar ao jogo: ");
scanf("*%c");
}


void game(bool game_mode, bool resume){
char **tab,piece=1;
int lin,col,turn,k;
struct coordinates place;
struct player a,b,*aux;
struct list_head *states; 
struct list_node *curr; 
if(resume==1){
  load_players(&a,&b);
  load_tab_list(&tab,&lin,&col,&k,&states,&curr);
  turn=k; //?????
  }
else{ //comecar jogo do zero
  if( ( tab=create_tab(&lin,&col) )==NULL ){
    printf("O programa terminara\n");
    return ;
    }
  if( ( states=create_head(lin,col) )==NULL   ){//criar linked list
    free_tab(tab,lin);
    printf("O programa ira terminar");
    return ;
    }
  init_player(&a,'A'); init_player(&b,'B'); turn=1;
  }

//inicio efetivo do jogo
while(check_victory(tab,lin,col,*aux)!=1 || check_tie(tab,lin,col,a,b)!=1){
  printf("Turno %d, vez do jogador %c\n\n",turn,turn%2==0 ? 'B' : 'A'); //impares B, pares A
  if(turn%2==0)
    aux=&b;
  else
    aux=&a;
  
  if(game_mode==1 && aux==&b){ //vez do bot
    bot_plays(&tab,&lin,&col,&piece,&place,aux);
    show_bot_play(*aux,piece,place);
    }

  else{ //jogador humano
    ask_player(&tab,&lin,&col,&place,aux,turn,&piece);
    if(piece=='K'){
      show_k_prev_info(turn,states,curr);
      continue;
      }
    if(piece=='I'){
      printf("O jogo ira terminar mas sera guardado num ficheiro para o poder continuar\n"
      "posteriormente\n");
      export_bin(*states,a,b,states->lin,states->col,game_mode);//lin e col iniciais
      free_tab(tab,lin);
      free_list_and_tab(states,curr->lin); 
      return ;
      }
    }
    
  //operacoes na linked list
  if(turn==1){//criar o primeiro no
    if(add_node_in_head(states,lin,col,aux->name,piece,place)==0 ) {
      free_tab(tab,lin); //a lista ja esta limpa
      return ;
    }
    curr=states->next;
  }
  else{ //estamos em qualquer outro turno
    if(add_node_to_node(states,curr,lin,col,aux->name,piece,place)==0 ){
      free_tab(tab,lin); //a lista ja esta limpa
      return ;
    }
    curr=curr->next;
    }
  ++turn;
  }
//fim do jogo
free_tab(tab,lin); //apagar o tabuleiro

if( reset_tab(states,curr)==0 ){
  fprintf(stderr,"Erro ao exportar os estados do tabuleiro para um ficheiro\n");
  return ; //a lista ja esta limpa
  }
export_states_txt(states);
free_list_and_tab(states,curr->lin);
}

