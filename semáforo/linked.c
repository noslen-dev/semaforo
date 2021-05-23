#include <stdlib.h>
#include <stdio.h>
#include "linked.h"
#include "tab.h"


/****
 * static void free_list(cabeca da lista)
 * Limpa todos os nos da lista e limpa a cabeca
 * Liberta a lista por completo
 */ 
static void free_list(struct list_head *head){
struct list_node *ptr, *next;
for(ptr=next=head->next; ptr!=NULL; ptr=next){
  next=ptr->next;
  free(ptr);
  }
free(head);
}


/****
 * void free_list_and_tab(cabeca da lista, numero de linhas do tabuleiro atual)
 * Limpa todos os nos da lista e limpa a cabeca e o seu tabuleiro
 * Liberta a lista por completo
 */ 
void free_list_and_tab(struct list_head *head, int lin){
struct list_node *ptr, *next;
for(ptr=next=head->next; ptr!=NULL; ptr=next){ //limpa os nos
  next=ptr->next;
  free(ptr);
  }
free_tab(head->tab,lin); //limpa o tabuleiro da cabeca
free(head); //limpa a cabeca
}

/***
 * bool reset_tab(cabeca da lista, ultimo no)
 * Faz com que o "tab" presente em head, volte ao estado em que estava antes de
 * comecar o jogo.
 * Se uma alocacao falhar limpa a lista e devolve 0
 * Se tudo correr bem devolve .
 */ 
bool reset_tab(struct list_head *head, struct list_node *curr){
char **aux;
if( ( aux=create_tab_fixed_lc(head->lin,head->col) )==NULL ){ //resetar a cabeca
  fprintf(stderr,ALLOCATION_ERROR_LINKED);
  free_list_and_tab(head,curr->lin); //as linhas podem ter sido alteradas
  return 0;
  }
head->tab=aux;
return 1;
}



/****
 * static void write_info(no atual)
 * Baseado na informacao do no escreve informacao sobre a jogada realizada
 */ 
static void write_info(struct list_node curr){
printf("Turno %d\n",curr.turn);
printf("O jogador %c ",curr.player_name);
if(curr.piece!='L' && curr.piece!='C')
  printf("colocou a peca %c na posicao %d %d\n",curr.piece,curr.place.x,curr.place.y);
else
  printf("adicionou uma %s\n",curr.piece=='C' ? "coluna": "linha");
}



/*****
 * struct list_head *create_head(numero de linhas, numero de colunas)
 * Cria a cabeca de linked list que ira guardar os estados do tabuleiro.
 * Inicializa os menbros da cabeca, faz o membro "tab" apontar ja para um
 * tabuleiro de dimensao lin x col.
 * Inicializa tambem o membro "game_mode" com o mode de jogo em questao.
 * Devolve a cabeca em caso de sucesso.
 * Devolve NULL em caso de erro
 */ 
struct list_head * create_head(int lin, int col, bool game_mode){
struct list_head * new_head;
if( ( new_head=malloc(sizeof(struct list_head)) )==NULL ){
  fprintf(stderr,ALLOCATION_ERROR_LINKED);
  return NULL;
  }
if( ( new_head->tab=create_tab_fixed_lc(lin,col) )==NULL ){
  fprintf(stderr,ALLOCATION_ERROR_LINKED);
  free(new_head);
  return NULL;
  }
new_head->game_mode=game_mode;
new_head->lin=lin; new_head->col=col;
new_head->next=NULL;
return new_head;
}


/*****
 * struct list_node add_node_in_head(cabeca da lista, linhas, colunas, nome do jogador, peca atual,
 * coordenadas do tabuleiro)
 * Adiciona e inicializa com informacao recebida por argumento um novo no.Este no e adcionado a cabeca da lista
 * Este no representa o turno 1.
 * Devolve NULL em caso de erro e o novo no em caso de sucesso.
 */ 
bool add_node_in_head(struct list_head *head, int lin, int col, char name, char piece ,struct coordinates place){
struct list_node * new_node;
if( ( new_node=malloc(sizeof(struct list_node)) )==NULL ){
  fprintf(stderr,ALLOCATION_ERROR_LINKED);
  free_list_and_tab(head,head->lin); //liberta head e o seu tabuleiro
  return 0;
  }
new_node->lin=lin; new_node->col=col;
new_node->player_name=name;
new_node->piece=piece;
new_node->place=place;
new_node->turn=1; //sempre o turno 1
//ligacoes
head->next=new_node;
new_node->next=NULL;

return 1; //indica sucesso
}



/*****
 * bool add_node_in_head(cabeca da lista,no anterior, linhas, colunas, nome do jogador, peca atual,
 * coordenadas do tabuleiro)
 * Adiciona e inicializa com informacao recebida por argumento um novo no, este no e inserido noutro no.
 * Devolve 0 em caso de erro e limpa a lista.
 * Devolve 1 em caso de sucesso
 */ 
bool add_node_to_node(struct list_head *head,struct list_node *prev, int lin, int col, char name, char piece, struct coordinates place){
struct list_node * new_node;
if( ( new_node=malloc(sizeof(struct list_node)) )==NULL ){
  fprintf(stderr,ALLOCATION_ERROR_LINKED);
  free_list_and_tab(head,prev->lin); //o tabuleiro atual pode ter as linhas aumentadas
  return 0;
  }
new_node->lin=lin; new_node->col=col;
new_node->player_name=name;
new_node->piece=piece;
new_node->place=place;
new_node->turn=prev->turn+1; //sempre 1 a mais do que o anterior
//ligacoes
prev->next=new_node;
new_node->next=NULL;

return 1; //indica sucesso  
}



/***
 * bool place_piece(cabeca da lista, no atual)
 * Com a informacao presente em "curr", atualiza o tabuleiro da cabeca
 * Se alguma alocacao falhar, a funcao limpa a lista por completo.
 * Devolve 1 se as alocacoes foram um sucesso.
 * Devolve 0 se alguma alocacao falhou
 */ 
bool place_piece(struct list_head *head,struct list_node curr){
char **aux;
curr.place.x-=1; curr.place.y-=1;
if(curr.piece!='L' && curr.piece!='C')
  (head->tab)[curr.place.x][curr.place.y]=curr.piece;
else //inserir linha ou coluna
  if(curr.piece=='C'){
    --curr.col; // o numero ja esta certo
    if( ( add_col(head->tab,curr.lin,&curr.col) )==NULL ){
      fprintf(stderr,ALLOCATION_ERROR_LINKED);
      free_list(head); //libertar a lista, o tabuleiro ja esta limpo
      return 0;
      }
    }
  else{
    --curr.lin; //o numero ja esta certo
    if( (head->tab=add_lin(head->tab,&curr.lin,curr.col) )==NULL ){
      fprintf(stderr,ALLOCATION_ERROR_LINKED);
      free_list(head); //libertar a lista, o tabuleiro ja esta limpo
      return 0;
      }
    }
return 1; //sucesso
}


/**
 * bool show_k_prev(numero de jogadas anteriores, cabeca da lista, no atual)
 * O "k" que entra nesta funcao e sempre valido.
 * Mostra informacao e o tabuleiro nas k jogadas anteriores.
 * Devolve 0 caso uma alocacao falhe.
 * Devolve 1 em caso de sucesso
*/
bool show_k_prev(int k,struct list_head *head, struct list_node *end){
if( reset_tab(head,end)==0 )
  return 0; //erro ja esta escrito e lista ja esta limpa
struct list_node *curr;
for(curr=head->next; curr!=NULL  ;curr=curr->next){
  place_piece(head,*curr);
  if(end->turn+1-curr->turn<=k){
    write_info(*curr);
    draw_tab(head->tab,curr->lin,curr->col);
    printf("\n\n");
    }
  }
return 1;
}
