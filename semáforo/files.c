#include <stdio.h>
#include "files.h"
#include "tab.h"

void ask_filename(char *filename){
printf("\nDigite o nome do ficheiro em que quer que o seu jogo seja guardado: ");
scanf("%[^\n]",filename);
}


/****
 * static void write_info_to_file(no atual)
 * Baseado na informacao do no escreve informacao sobre a jogada realizada
 * no ficheiro apontado por fp.
 * O ficheiro ja vem aberto
 */ 
static void write_info_to_file(struct list_node curr, FILE *fp){
fprintf(fp,"Turno %d\n",curr.turn);
fprintf(fp,"O jogador %c ",curr.player_name);
if(curr.piece!='L' && curr.piece!='C')
  fprintf(fp,"colocou a peca %c na posicao %d %d\n",curr.piece,curr.place.x,curr.place.y);
else
  fprintf(fp,"adicionou uma %s\n",curr.piece=='C' ? "coluna": "linha");
}


/*************
 *  void draw_tab_to:file(tabuleiro de jogo, numero de linhas, numero de colunas,
 *  ficheiro para escrita)
 *  Desenha o tabuleiro do jogo, numa forma apropriada, que se adapta a um numero 
 *  variavel de linhas e colunas no ficheiro apontado por fp.
 *  O ficheiro ja vem aberto
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



void export_states_txt(struct list_head *states){
char filename[10];
FILE *fp;
struct list_node *curr;
ask_filename(filename); //pedir o nome do ficheiro
if( ( fp=fopen(filename,"w") )==NULL ){
  fprintf(stderr,"Erro ao criar o ficheiro de nome %s\n",filename);
  return ;
  }
for(curr=states->next; curr!=NULL; curr=curr->next){
  write_info_to_file(*curr,fp);
  place_piece(states,*curr);
  draw_tab_to_file(states->tab,curr->lin,curr->col,fp);
  if(curr->next!=NULL) 
    fprintf(fp,"\n-----------------------------------------------\n");
  else //estamos no ultimo turno == vitoria
    fprintf(fp,"\n\nFim do jogo, vitoria do jogador %c\n",curr->player_name);
    
  }
fclose(fp);
}