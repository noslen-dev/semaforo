#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "tab.h"
#include "linked.h"

#define ALLOCATION_ERROR_LINKED  "Erro ao criar a sucessao dos estados do tabuleiro\n"


/****
 * static void free_head_and_nodes(cabeca da lista)
 * Liberta todos os nos da lista e a sua cabeca
 * Nao liberta o tabuleiro que esta na cabeca da lista
 */ 
static void free_head_and_nodes(struct list_head *head){
    struct list_node *curr, *next;
    for(curr=next=head->next; curr!=NULL; curr=next){
        next=curr->next;
        free(curr);
    }
    free(head);
}


/****
 * void free_list_and_tab_in_head(cabeca da lista, linhas do tabuleiro presente na cabeca da lista)
 * Limpa todos os nos da lista e limpa a cabeca e o seu tabuleiro
 */ 
void free_list_and_tab_in_head(struct list_head *head, int lin){
    struct list_node *curr, *next;
    for(curr=next=head->next; curr!=NULL; curr=next){ //limpa os nos
        next=curr->next;
        free(curr);
    }
    free_tab(head->tab,lin); //limpa o tabuleiro da cabeca
    free(head); //limpa a cabeca
}


/****
 * static void write_info(no que representa o turno atual do jogo)
 * Com a informacao presente no no, escreve informacao sobre a jogada realizada nesse turno
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
 * struct list_head *create_head(numero de linhas do tabuleiro de jogo inicial, 
 * numero de colunas do tabuleiro de jogo inicial)
 * Cria a cabeca da lista ligada
 * Faz o membro "tab" apontar para um
 * tabuleiro de dimensao "lin" x "col" e guarda as dimensoes desse tabuleiro nos membros respetivos da cabeca
 * Devolve a cabeca em caso de sucesso.
 * Devolve NULL em caso de erro
 * Esta funcao nao deixa memoria por libertar
 */ 
struct list_head * create_head(int lin, int col){
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
    new_head->lin=lin; new_head->col=col;
    new_head->next=NULL;
    return new_head;
}


/*****
 * bool add_node_in_head(cabeca da lista, linhas do tabuleiro de jogo atual, colunas do tabuleiro de jogo atual, 
 * nome do jogador atual, peca colocada, coordenadas em que a peca foi colocada)
 * Adiciona e inicializa com informacao recebida por argumento um novo no 
 * Este no e adicionado a cabeca da lista
 * Este no representa o turno 1.
 * Limpa a lista e o tabuleiro da cabeca e devolve 0 em caso de erro 
 * Devolve 1 em caso de sucesso.
 */ 
bool add_node_in_head(struct list_head *head, int lin, int col, char name, char piece ,struct coordinates place){
    struct list_node * new_node;
    if( ( new_node=malloc(sizeof(struct list_node)) )==NULL ){
        fprintf(stderr,ALLOCATION_ERROR_LINKED);
        free_list_and_tab_in_head(head,head->lin); //a meio do jogo o tab na cabeca esta sempre igual ao tab inicial
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

    return 1; 
}



/*****
 * bool add_node_to_node(cabeca da lista, no anterior, linhas do tabuleiro de jogo atual, colunas do tabuleiro de jogo atual, 
 * nome do jogador atual, peca colocada, coordenadas da peca colocada)
 * Adiciona e inicializa com informacao recebida por argumento um novo no, este no e inserido apos o no anterior("prev")
 * Devolve 0 em caso de erro e limpa a lista e o tabuleiro da cabeca.
 * Devolve 1 em caso de sucesso
 */ 
bool add_node_to_node(struct list_head *head,struct list_node *prev, int lin, int col, char name, char piece, struct coordinates place){
    struct list_node * new_node;
    if( ( new_node=malloc(sizeof(struct list_node)) )==NULL ){
        fprintf(stderr,ALLOCATION_ERROR_LINKED);
        free_list_and_tab_in_head(head, prev->lin); //o tab em head esta sempre resetado a meio do jogo 
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

return 1;   
}


/***
 * bool place_piece_in_head_tab(cabeca da lista, no da lista)
 * Realiza a jogada presente em "curr" alterando assim o tabuleiro da cabeca da lista
 * Se alguma alocacao falhar, a funcao limpa a lista e o tabuleiro da cabeca
 * Devolve 1 se as alocacoes foram um sucesso
 * Devolve 0 se alguma alocacao falhou
 */ 
bool place_piece_in_head_tab(struct list_head *head, struct list_node curr){
    char **aux;
    curr.place.x-=1; curr.place.y-=1; //as coordenadas foram introduzidas pelo utilizador
    if(curr.piece!='L' && curr.piece!='C')
        (head->tab)[curr.place.x][curr.place.y]=curr.piece;
    else //inserir linha ou coluna
        if(curr.piece=='C'){
            --curr.col; // o numero ja esta certo, porem "add_col" ira aumentar curr.col
            if( ( add_col(head->tab,curr.lin,&curr.col) )==NULL ){
                fprintf(stderr,"Erro ao realizar uma jogada na cabeca da lista\n");
                free_head_and_nodes(head); //libertar a lista, o tabuleiro ja esta limpo
                return 0;
            }
        }
        else{
            --curr.lin; //o numero ja esta certo, porem "add_lin" ira aumentar curr.lin
            if( (head->tab=add_lin(head->tab,&curr.lin,curr.col) )==NULL ){// se falhar, head->tab ficara limpo
            fprintf(stderr,"Erro ao realizar uma jogada na cabeca da lista\n");
            free_head_and_nodes(head);
            return 0;
        }
      }
    return 1; 
}

/***
 * bool reset_tab_in_head(cabeca da lista, linhas do tabuleiro presente na cabeca da lista)
 * Faz com que o tabuleiro presente na cabeca da lista, volte ao estado em que estava antes de
 * comecar o jogo
 * Se uma alocacao falhar limpa a lista e o tabuleiro da cabeca e devolve 0
 * Se tudo correr bem devolve 1
 */ 
bool reset_tab_in_head(struct list_head *head, int lin){
    char **aux;
    if( ( aux=create_tab_fixed_lc(head->lin,head->col) )==NULL ){ //resetar a cabeca
        fprintf(stderr,ALLOCATION_ERROR_LINKED);
        free_list_and_tab_in_head(head,lin);  //o tabuleiro pode estar alterado, temos de passar as linhas atuais para o limpar
        return 0;
    }
    free_tab(head->tab,lin); //limpar o tabuleiro que ja esta na cabeca
    head->tab=aux;//atualizar esse tabuleiro
    return 1;
}


/**
 * bool show_k_prev(numero de jogadas anteriores, cabeca da lista, no que representa o turno atual do jogo)
 * O "k" que entra nesta funcao e sempre valido
 * Mostra como estava o tabuleiro e informacao sobre cada jogada realizada, nos "k" turnos anteriores
 * Devolve 0 caso uma alocacao falhe e limpa a lista e o tabuleiro da cabeca 
 * Devolve 1 em caso de sucesso
*/
bool show_k_prev(int k, struct list_head *head, struct list_node *end){
    struct list_node *curr;
    for(curr=head->next; curr!=NULL  ;curr=curr->next){
        if( place_piece_in_head_tab(head,*curr)==0 )
            return 0;
        if(end->turn+1-curr->turn<=k){
            write_info(*curr);
            draw_tab(head->tab,curr->lin,curr->col);
            printf("\n\n");
        }
    }
    if( reset_tab_in_head(head,end->lin)==0 ) //voltar a por o tabuleiro como estava
        return 0; 
    return 1;
}
