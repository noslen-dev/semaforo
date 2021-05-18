#include "linked.h"
#include <stdlib.h>
#include <stdio.h>

struct d_list * create_list(){
struct d_list *head;
if( ( head=malloc(sizeof(struct d_list)) )==NULL ){
  fprintf(stderr,"Erro ao criar a lista que iria guardar os estados do tabuleiro\n"
  "Podera continuar a jogar, mas nao tera este recurso indisponivel\n");
  return NULL;
  }
head->next=head->prev=NULL;
return head;
}

struct d_list * add_node(struct d_list *curr){
struct d_list *new_node;
if( ( new_node=malloc(sizeof(struct d_list)) )==NULL ){
  fprintf(stderr,"Erro ao criar a lista que iria guardar os estados do tabuleiro\n"
  "Podera continuar a jogar, mas nao tera este recurso indisponivel\n");
  return NULL;
  //limpar lista
  }
curr->next=new_node;
new_node->prev=curr;
new_node->next=NULL;
}

void print_linked(struct d_list *curr){
for(; curr!=NULL; curr=curr->next)
  printf("%c \n",curr->piece);
}



