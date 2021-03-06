/*
 * Nome: Nelson Forte Simao
 * Numero: 2020132648 
 */

#include <stdio.h>
#include <string.h>
#include "linked.h"
#include "files.h"


/**
 * static void ask_filename(string)
 * Pede ao utilizador um nome e insere-o na string recebida como argumento
 * Le no maximo 10 carateres e coloca .txt no final da string
 */
static void ask_filename(char *filename){
    printf("\n\nDigite o nome do ficheiro em que quer que o seu jogo seja guardado"
    "\nInsira um nome com 10 carateres no maximo: ");
    scanf(" %10[^\n]",filename);
    strcat(filename,".txt");
}


/****
 * static void write_node_info_to_file(no da lista, ficheiro de texto aberto para escrita)
 * Baseado na informacao do no escreve informacao sobre a jogada realizada
 * no ficheiro recebido por referencia
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
 *  static void draw_tab_to_file(tabuleiro de jogo, numero de linhas do tabuleiro, 
 *  numero de colunas do tabuleiro, ficheiro de texto aberto para escrita)
 *  Desenha o tabuleiro do jogo no ficheiro recebido por referencia
 *  O ficheiro ja vem aberto e nao e fechado
 ***************/
static void draw_tab_to_file(char **tab, int lin, int col, FILE *fp){
    int i,j,aux;
    fprintf(fp,"    ");
    for(i=0; i<col; ++i)
        if(i+1!=col)
            fprintf(fp,"----");
        else
            fprintf(fp,"-----");
        putc('\n',fp);
    for(i=0; i<lin; ++i){
        fprintf(fp,"  %d ",i+1);
        putc('|',fp);; 
        for(j=0; j<col; ++j)
            fprintf(fp," %c %c",tab[i][j],'|');
            fprintf(fp,"\n    ");
        for(aux=0; aux<col; ++aux)
            if(aux+1!=col)
                fprintf(fp,"----");
            else
                fprintf(fp,"-----");
        putc('\n',fp);
    }
    fprintf(fp,"      ");
    for(i=0; i<col; ++i)
        fprintf(fp,"%d   ",i+1);
}


/***
 * bool export_states_txt(cabeca da lista, modo de jogo)
 * Cria um ficheiro .txt com um nome indicado pelo utilizador e escreve nesse 
 * ficheiro uma mensagem a indicar o tipo de jogo(se e contra o computador ou nao) e 
 * a sucessao de estados do tabuleiro.
 * Devolve 1 em caso de sucesso
 * Esta funcao utiliza a lista ligada e se falhar a abrir o ficheiro ou numa operacao com a lista
 * liberta a lista e o tabuleiro na cabeca e devolve 0
 */
bool export_states_txt(struct list_head *states, bool game_mode){
    char filename[15];
    FILE *fp;
    struct list_node *curr;
    ask_filename(filename); //pedir o nome do ficheiro
    if( ( fp=fopen(filename,"w") )==NULL ){
        fprintf(stderr,"\nErro ao criar o ficheiro de nome %s\n",filename);
        free_list_and_tab_in_head(states,states->lin); //tabuleiro esta resetado no final do jogo
        return 0;
    }
    fprintf(fp,"%s",game_mode==0 ? "Jogo a dois jogadores\n\n" : "Jogo contra o computador\n\n" );
    for(curr=states->next; curr!=NULL; curr=curr->next){
        write_node_info_to_file(*curr,fp);
        if( place_piece_in_head_tab(states,*curr)==0 ){
            fclose(fp);
            return 0; 
        }
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
 * bool export_bin(cabeca da lista, jogador a, jogador b, modo de jogo)
 * Cria um ficheiro chamado "jogo.bin" e escreve nele toda a informacao necessaria para retomar um jogo
 * A disposicao do ficheiro ficara a seguinte:
 * 
 * |************************************************************************|
 * |modo de jogo | jogador a | jogador b | linhas do tabuleiro da cabeca    | 
 * |colunas do tabuleiro da cabeca | lista ligada(exeto a cabeca)           |
 * |*************************************************************************
 * Devolve 1 se o ficheiro foi criado com sucesso.
 * Devolve 0 se o ficheiro nao pode ser criado
 */ 
bool export_bin(struct list_head states, struct player a, struct player b, bool game_mode){
    FILE *fp;
    if( (fp=fopen("jogo.bin","wb"))==NULL ){
        fprintf(stderr,"\n\nErro ao criar o ficheiro \"jogo.bin\" que iria guardar o jogo\n");
        return 0;
    }
    struct list_node *curr;
    //escrever os jogadores e as dimensoes do tabuleiro da cabeca no inicio do ficheiro
    fwrite(&game_mode,sizeof(bool),1,fp);
    fwrite(&a,sizeof(struct player),1,fp);
    fwrite(&b,sizeof(struct player),1,fp);
    fwrite(&states.lin,sizeof(int),1,fp);
    fwrite(&states.col,sizeof(int),1,fp);

    for(curr=states.next; curr!=NULL; curr=curr->next)
        fwrite(curr,sizeof(struct list_node),1,fp);
    fclose(fp);
    return 1; 
}


