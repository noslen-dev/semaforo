#include <stdio.h>
#include <stdlib.h>
#include "tab.h"
#include "utils.h"

/*************
 * void init_lin(linha para inicializar, numero de colunas)
 * inicializa com ' ' a linha, apontada pelo parametro "linha"
 * 
 ***************/
void init_lin(char *linha, int colunas){
int i;
for(i=0; i<colunas; ++i)
  linha[i]=' ';
}

/*************
 * void init_col(tabuleiro de jogo, numero de linhas, numero da coluna para inicializar)
 * inicializa com ' ', o numero da coluna passada como argumento
 * 
 ***************/
void init_col(char **tabuleiro, int linhas, int coluna){
int i;
for(i=0; i<linhas; ++i)
  tabuleiro[i][coluna]=' ';
}


/*************
 *  void init_col(tabuleiro de jogo, numero de linhas, numero de colunas)
 *  cria um tabuleiro de jogo, com um numero aleatorio entre [3,5] de linhas.
 *  Aloca espaço de tal forma, que "tabuleiro" fica a apontar para um array dinamico
 *  de char * que apontam para um array dinamico de char em que cada um deles(array de char)
 *  representa uma linha.
 *  se a alocação de qualquer elemento falhar, devolve NULL, caso contrario 
 *  devolve o tabuleiro e altera o numero de linhas e colunas.
 ***************/
char **create_tab(char **tabuleiro, int *linhas, int *colunas){
int i;
*linhas=*colunas=intUniformRnd(3,5);
if( (tabuleiro=malloc(sizeof(char *)* *linhas))==NULL ){
  fprintf(stderr,"Erro ao alocar espaço para o tabuleiro\n");
  *linhas=*colunas=0;
  return NULL;
}
for(i=0; i<*linhas; ++i)
  if( ( tabuleiro[i]=(char *)malloc(sizeof(char)* *linhas) )==NULL ){
     fprintf(stderr,"Erro ao alocar espaço para o tabuleiro\n");
     while(--i && i>=0)
       free(tabuleiro[i]);
     free(tabuleiro);
     *linhas=*colunas=0;
     return NULL;
  }
return tabuleiro;
}


void draw_tab(char **tabela, int linhas, int colunas){
int i,j,aux;
for(i=0; i<linhas; ++i){
  printf("  %d ",i); 
  for(j=0; j<colunas; ++j)
    printf(" %c %c",tabela[i][j],j+1==colunas ? ' ': '|'); 
  if(i+1!=linhas){
    printf("\n    ");
    for(aux=0; aux<colunas; ++aux)
      if(aux+1!=colunas)
        printf("----");
      else
        printf("---");
    putchar('\n');
  }
 }
printf("\n  ");
for(i=0; i<colunas; ++i)
  printf("   %d",i);
}



void init_tab(char **tabela, int linhas ,int colunas){
int i;
for(i=0; i<linhas; ++i)
  init_lin(tabela[i],colunas);
}



char **add_lin(char **tabela ,int *linhas, int colunas){
char **aux;
if( (aux=(char**)realloc(tabela,sizeof(char *)*(*linhas+1)) )==NULL ) {
  printf("Erro ao alocar espaço para o tabuleiro\n");
  return tabela;
 }
++*linhas;
tabela=aux;
if( (tabela[*linhas-1]=malloc(sizeof(char)*colunas))==NULL ){
  printf("Erro ao adicionar uma linhas\n");
  free(tabela[*linhas-1]);
  tabela=realloc(tabela,sizeof(char)* *linhas);
  return tabela;
}
init_lin(tabela[*linhas-1],colunas);
return tabela;
}


void **add_col(char **tabuleiro ,int linhas, int *colunas){
int i;
char *aux;
for(i=0; i<linhas; ++i)
  if( ( aux=realloc(tabuleiro[i],sizeof(char)* (*colunas+1)) )==NULL ){
     fprintf(stderr,"Erro ao alocar espaço para o tabuleiro\n");
     while(--i && i>=0)
       tabuleiro[i]=realloc(tabuleiro[i],sizeof(char)* *colunas);
     return NULL;
  }
  else
    tabuleiro[i]=aux;
++*colunas;
init_col(tabuleiro,linhas,*colunas-1);
}



void play(char **tabuleiro, int linhas, int colunas ,struct jogador a){
int i,j;
a.habilidade.verde=a.habilidade.amarelo=a.habilidade.vermelho=0;
for(i=0; i<linhas; ++i)
  for(j=0; j<colunas; ++j)
    switch(tabuleiro[i][j]){
      case ' ': 
        a.habilidade.verde=1;
        break;
      case 'V':
        a.habilidade.amarelo=1;
      case 'A':
        a.habilidade.vermelho=1;
        break;
    }
printf("%d",a.habilidade.verde);

}
