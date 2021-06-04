#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "linked.h"
#include "play.h"
#include "files.h"


/**
 * static void ask_filename(string)
 * Pede ao utilizador um nome e insere-o na string recebida como argumento
 * Le no maximo 10 carateres e coloca .txt no final.
 */
static void ask_filename(char *filename){
    printf("\n\nDigite o nome do ficheiro em que quer que o seu jogo seja guardado"
    ", insira um nome com 10 carateres no maximo: ");
    scanf(" %10[^\n]",filename);
    strcat(filename,".txt");
}


/****
 * static write_node_info_to_file(no atual)
 * Baseado na informacao do no escreve informacao sobre a jogada realizada
 * no ficheiro apontado por fp.
 * O ficheiro ja vem aberto e nao e fechado pela funcao
 */ 
static void write_node_info_to_file(struct list_node curr, FILE *fp){
    fprintf(fp,"Turno %d\n",curr.turn);
    fprintf(fp,"O jogador %c ",curr.player_name);
    if(curr.piece!='L' && curr.piece!='C')
        fprintf(fp,"colocou a peca %c na posicao %d %d\n\n",curr.piece,curr.place.x,curr.place.y);
    else
        fprintf(fp,"adicionou uma %s\n\n",curr.piece=='C' ? "coluna": "linha");
}


/*************
 *  void draw_tab_to_file(tabuleiro de jogo, numero de linhas, numero de colunas,
 *  ficheiro para escrita)
 *  Desenha o tabuleiro do jogo no ficheiro apontado por fp.
 *  O ficheiro ja vem aberto e nao e fechado
 ***************/
void draw_tab_to_file(char **tab, int lin, int col, FILE *fp){
    int i,j,aux;
    for(i=0; i<lin; ++i){
        fprintf(fp,"  %d ",i+1); 
        for(j=0; j<col; ++j)
            fprintf(fp," %c %c",tab[i][j],j+1==col ? ' ': '|'); 

        if(i+1!=lin){
            fprintf(fp,"\n    ");
            for(aux=0; aux<col; ++aux)
                if(aux+1!=col)
                    fprintf(fp,"----");
                else
                    fprintf(fp,"---");
                putc('\n',fp);
        }
    }

    fprintf(fp,"\n  ");
    for(i=0; i<col; ++i)
      fprintf(fp,"   %d",i+1);
}


/***
 * bool export_states_txt(cabeca da lista que contem os estados do tabuleiro)
 * Cria um ficheiro .txt com um nome indicado pelo utilizador e escreve nesse 
 * ficheiro uma mensagem a indicar o tipo de jogo(se e contra computador ou nao) e 
 * a sucessao de estados do tabuleiro.
 * Devolve 1 se conseguiu criar o ficheiro.
 * Devolve 0 caso contrario.
 */
bool export_states_txt(struct list_head *states, bool game_mode){
    char filename[15];
    FILE *fp;
    struct list_node *curr;
    ask_filename(filename); //pedir o nome do ficheiro
    if( ( fp=fopen(filename,"w") )==NULL ){
        fprintf(stderr,"Erro ao criar o ficheiro de nome %s\n",filename);
        return 0;
    }
    fprintf(fp,"%s",game_mode==0 ? "Jogo a dois jogadores\n\n" : "Jogo contra o computador\n\n" );
    for(curr=states->next; curr!=NULL; curr=curr->next){
        write_node_info_to_file(*curr,fp);
        place_piece_in_head_tab(states,*curr);
        draw_tab_to_file(states->tab,curr->lin,curr->col,fp);
        if(curr->next!=NULL) 
            fprintf(fp,"\n\n-----------------------------------------------\n\n");
        else //estamos no ultimo turno == vitoria
            fprintf(fp,"\n\nFim do jogo, vitoria do jogador %c",curr->player_name);
    }
    fclose(fp);
    return 1;
}


/**
 * bool export_states_bin(cabeca da lista que contem os estados do tabuleiro, jogador a, jogador b,
 * numero de linhas iniciais, numero de colunas iniciais, modo de jogo)
 * Escreve no ficheiro toda a informacao necessaria para retomar um jogo.
 * A disposicao do ficheiro ficara a seguinte:
 * 
 * |************************************************************************|
 * |modo de jogo | jogador a | jogador b | linhas iniciais| colunas iniciais|
 * |lista com as sucessoes do tabuleiro(exeto a cabeca)                     |
 * |************************************************************************
 * Devolve 1 se o ficheiro foi criado com sucesso.
 * Devolve 0 se o ficheiro nao pode ser criado
 */ 
bool export_bin(struct list_head states, struct player a, struct player b, int lin, int col, bool game_mode){
    FILE *fp;
    if( (fp=fopen("jogo.bin","wb"))==NULL ){
        fprintf(stderr,"Erro ao criar o ficheiro que iria guardar o jogo\n");
        return 0;
    }
    struct list_node *curr;
    //escrever os jogadores e as dimensoes do tabuleiro no inicio do ficheiro
    fwrite(&game_mode,sizeof(bool),1,fp);
    fwrite(&a,sizeof(struct player),1,fp);
    fwrite(&b,sizeof(struct player),1,fp);
    fwrite(&lin,sizeof(int),1,fp);
    fwrite(&col,sizeof(int),1,fp);

    for(curr=states.next; curr!=NULL; curr=curr->next)
        fwrite(curr,sizeof(struct list_node),1,fp);
    
    fclose(fp);
    return 1; //sucesso
}


