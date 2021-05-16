#include <stdio.h>
#include <stdlib.h>
#include "tab.h"
#include "utils.h"

/*************
 * void init_lin(linha para inicializar, numero de colunas)
 * inicializa com ' ' a linha, apontada pelo parametro "linha"
 * 
 ***************/
void init_lin(char *lin, int col){
int i;
for(i=0; i<col; ++i)
  lin[i]=' ';
}

/*************
 * void init_col(tabuleiro de jogo, numero de linhas, numero da coluna para inicializar)
 * inicializa com ' ', o numero da coluna passada como argumento
 * 
 ***************/
void init_col(char **tab, int lin, int col){
int i;
for(i=0; i<lin; ++i)
  tab[i][col]=' ';
}


/*************
 *  char **create_tab(tabuleiro de jogo, numero de linhas, numero de colunas)
 *  cria um tabuleiro de jogo, com um numero aleatorio entre [3,5] de linhas.
 *  Aloca espaço de tal forma, que "tabuleiro" fica a apontar para um array dinamico
 *  de char * que apontam para um array dinamico de char em que cada um deles(array de char)
 *  representa uma linha.
 *  se a alocação de qualquer elemento falhar, devolve NULL, caso contrario 
 *  devolve o tabuleiro e altera o numero de linhas e colunas.
 ***************/
char **create_tab(char **tab, int *lin, int *col){
int i;
*lin=*col=intUniformRnd(3,5);
if( (tab=malloc(sizeof(char *)* *lin))==NULL ){
  fprintf(stderr,"Erro ao alocar espaço para o tabuleiro\n");
  *lin=*col=0;
  return NULL;
}
for(i=0; i<*lin; ++i)
  if( ( tab[i]=(char *)malloc(sizeof(char)* *lin) )==NULL ){
     fprintf(stderr,"Erro ao alocar espaço para o tabuleiro\n");
     while(--i && i>=0)
       free(tab[i]);
     free(tab);
     *lin=*col=0;
     return NULL;
  }
return tab;
}


/*************
 *  void draw_tab(tabuleiro de jogo, numero de linhas, numero de colunas)
 *  Desenha o tabuleiro do jogo, numa forma apropriada, que se adapta a um numero 
 *  variavel de linhas e colunas.
 ***************/
void draw_tab(char **tab, int lin, int col){
int i,j,aux;
for(i=0; i<lin; ++i){
  printf("  %d ",i); 
  for(j=0; j<col; ++j)
    printf(" %c %c",tab[i][j],j+1==col ? ' ': '|'); 
  if(i+1!=lin){
    printf("\n    ");
    for(aux=0; aux<col; ++aux)
      if(aux+1!=col)
        printf("----");
      else
        printf("---");
    putchar('\n');
  }
 }
printf("\n  ");
for(i=0; i<col; ++i)
  printf("   %d",i);
}


/*************
 *  void draw_tab(tabuleiro de jogo, numero de linhas, numero de colunas)
 *  utiliza a função "init_lin", para colocar todas as posições do tabuleiro com
 *  ' '
 ***************/
void init_tab(char **tab, int lin ,int col){
int i;
for(i=0; i<lin; ++i)
  init_lin(tab[i],col);
}



/*************
 *  void add_lin(tabuleiro de jogo, numero de linhas, numero de colunas)
 *  adiciona uma linha ao tabuleiro de jogo. Para isso aumenta o array de 
 *  ponteiros, inicializa esse ponteiro com uma linha, e preenche essa linha 
 *  com ' '
 *  Se o aumento do array de linhas falhar, devolve a tabela como estava antes
 *  Se o aumento do array for um sucesso, mas a inicialização do novo elemento falhar
 *  a função tenta voltar ao estado anterior do tabuleiro e devolve o tabuleiro como
 *  estava antes.
 *  Se nao conseguir repor o estado anterior do tabuleiro, retorna NULL.
 *  
 ***************/
char **add_lin(char **tab ,int *lin, int col){
char **aux;
if( (aux=(char**)realloc(tab,sizeof(char *)*(*lin+1)) )==NULL ) {
  printf("Erro ao alocar espaço para o tabuleiro\n");
  return tab;
 }
++*lin;
tab=aux;
if( (tab[*lin-1]=malloc(sizeof(char)*col))==NULL ){
  printf("Erro ao adicionar uma linha\n");
  if( ( tab=realloc(tab,sizeof(char)* (*lin-1) ) )==NULL){ //reduzimos o array
  fprintf(stderr,"Erro fatal, o programa terminara\n");
  return NULL;
  }
  --*lin;
  return tab;
}
init_lin(tab[*lin-1],col);
return tab;
}



/*************
 *  void add_col(tabuleiro de jogo, numero de linhas, numero de colunas)
 *  adiciona uma linha ao tabuleiro, adicionando mais um elemento ao final de cada
 *  linha e inicializa essa coluna com ' '
 *  Se uma alocação falhar a função tenta voltar atrás e repor o tabuleiro ao seu
 *  estado original e retorna tab se o conseguir fazer.
 *  Caso nao consiga repor o tabuleiro ao seu estado original, retorna NULL.
 *  
 *  
 ***************/
char **add_col(char **tab ,int lin, int *col){
int i;
char *aux;
for(i=0; i<lin; ++i)
  if( ( aux=realloc(tab[i],sizeof(char)* (*col+1)) )==NULL ){
     fprintf(stderr,"Erro ao alocar espaço para o tabuleiro\n");
     while(--i && i>=0)
       if( (tab[i]=realloc(tab[i],sizeof(char)* *col) )==NULL){
         fprintf(stderr,"Erro fatal, o programa terminara\n");
         return NULL;
       }
     return tab;
  }
  else
    tab[i]=aux;
++*col;
init_col(tab,lin,*col-1);
return tab;
}


/*************
 *  bool check_lin(tabuleiro de jogo, numero de linhas, numero de colunas)
 *  Verifica, linha a linha, se uma linha tem so carateres iguais.
 *  Devolve 1 em caso afirmativo, e 0 em caso contrario
 ***************/
bool check_lin(char **tab, int lin, int col){
int i,j;
bool flag=0;
for(i=0; i<lin; ++i){
  for(j=flag=0; j<lin-1; ++j)
    if(tab[i][j]!=tab[i][j+1] || tab[i][j]==' ' || tab[i][j]=='S')
      flag=1;
  if(flag==0)
    return 1;
  }
return 0;
}

/*************
 *  bool check_col(tabuleiro de jogo, numero de linhas, numero de colunas)
 *  Verifica, coluna a coluna, se uma coluna tem so carateres iguais.
 *  Devolve 1 em caso afirmativo, e 0 em caso contrario
 ***************/
bool check_col(char **tab, int lin, int col){
int i,j;
bool flag=0;
for(i=0; i<col; ++i){
  for(j=flag=0; j<lin-1; ++j)
    if(tab[j][i]!=tab[j+1][i] || tab[i][j]==' ' || tab[i][j]=='S')
      flag=1;
  if(flag==0)
    return 1;
  }
return 0;
}


/*************
 *  bool check_diagonal(tabuleiro de jogo, numero de linhas, numero de colunas)
 *  Verifica se qualquer uma das diagonais contem carateres todos iguais exeto ' '
 *  e 'S'
 *  Devolve 1 em caso afirmativo, e 0 em caso contrario
 ***************/
bool check_diagonal(char **tab, int lin, int col){
if(lin!=col)
  return 0;
int i,j;
for(i=0; i<lin-1; ++i)
  if(tab[i][i]!=tab[i+1][i+1] || tab[i][j]==' ' || tab[i][j]=='S') 
    return 0;
for(i=0,j=lin; i<lin-1; ++i,--j)
  if(tab[i][j]!=tab[i+1][j-1] || tab[i][j]==' ' || tab[i][j]=='S')
    return 0;
}

