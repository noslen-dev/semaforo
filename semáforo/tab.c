#include <stdio.h>
#include <stdlib.h>
#include "tab.h"
#include "utils.h"



/*************
 * void free_tab(tabuleiro de jogo, numero de linhas)
 * Liberta um tabuleiro de jogo
 ***************/
void free_tab(char **tab, int lin){
int i;
for(i=0; i<lin; ++i)
  free(tab[i]);
free(tab);
}


/*************
 * void init_lin(linha para inicializar, numero de colunas)
 * inicializa com ' ' a linha, apontada pelo parametro "linha"
 ***************/
static void init_lin(char *lin, int col){
int i;
for(i=0; i<col; ++i)
  lin[i]=' ';
}

/*************
 * void init_col(tabuleiro de jogo, numero de linhas, numero da coluna para inicializar)
 * inicializa com ' ', o numero da coluna passada como argumento
 ***************/
static void init_col(char **tab, int lin, int col){
int i;
for(i=0; i<lin; ++i)
  tab[i][col]=' ';
}

/*************
 *  void draw_tab(tabuleiro de jogo, numero de linhas, numero de colunas)
 *  utiliza a função "init_lin", para colocar todas as posições do tabuleiro com
 *  ' '
 ***************/
static void init_tab(char **tab, int lin ,int col){
int i;
for(i=0; i<lin; ++i)
  init_lin(tab[i],col);
}

/*************
 *  char **create_tab(numero de linhas, numero de colunas)
 *  Cria um tabuleiro de jogo, com um numero aleatorio entre [3,5] de linhas.
 *  Aloca espaço de tal forma, que "tabuleiro" fica a apontar para um array dinamico
 *  de char * que apontam para um array dinamico de char em que cada um deles(array de char)
 *  representa uma linha. Basicamente cria uma matriz linhas*colunas na heap
 *  Inicializa o tabuleiro criado com ' '
 *  Se a alocação de qualquer elemento falhar, devolve NULL, caso contrario 
 *  devolve o tabuleiro e altera o numero de linhas e colunas.
 *  Limpa a memoria antes de retornar NULL.
 ***************/
char **create_tab(int *lin, int *col){
char **tab;
int i;
initRandom();
*lin=*col=intUniformRnd(3,5);
if( (tab=malloc(sizeof(char *)* *lin))==NULL ){
  printf("Erro ao alocar espaço para o tabuleiro\n");
  fprintf(stderr,ALLOCATION_ERROR);
  *lin=*col=0;
  return NULL;
}
for(i=0; i<*lin; ++i)
  if( ( tab[i]=(char *)malloc(sizeof(char)* *lin) )==NULL ){
     printf("Erro ao alocar espaço para o tabuleiro\n");
     fprintf(stderr,ALLOCATION_ERROR);
     while(--i && i>=0)
       free(tab[i]);
     free(tab);
     *lin=*col=0;
     return NULL;
  }
init_tab(tab,*lin,*col);
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
  printf("  %d ",i+1); 
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
  printf("   %d",i+1);
}



/*************
 *  void add_lin(tabuleiro de jogo, numero de linhas, numero de colunas)
 *  adiciona uma linha ao tabuleiro de jogo. Para isso aumenta o array de 
 *  ponteiros. 
 *  Inicializa esse ponteiro com uma linha, e preenche essa linha com ' '
 *  Se a alocacao falhar, a função limpa o tabuleiro e retorna NULL
 *  Se tudo correr bem devolve o tabuleiro
 ***************/
char **add_lin(char **tab ,int *lin, int col){
char **aux;
if( (aux=(char**)realloc(tab,sizeof(char *)*(*lin+1)) )==NULL ) {
  printf("Erro ao adicionar uma linha\n");
  fprintf(stderr,ALLOCATION_ERROR);
  free_tab(tab,*lin);
  return NULL;
 }
++*lin;
tab=aux;
if( (tab[*lin-1]=malloc(sizeof(char)*col))==NULL ){
  printf("Erro ao adicionar uma linha\n");
  fprintf(stderr,ALLOCATION_ERROR);
  --*lin;
  free_tab(tab,*lin);
  return NULL;
}
init_lin(tab[*lin-1],col);
return tab;
}



/*************
 *  void add_col(tabuleiro de jogo, numero de linhas, numero de colunas)
 *  Adiciona uma coluna ao tabuleiro, adicionando mais um elemento ao final de cada
 *  linha e inicializa essa coluna com ' '
 *  Se a alocacao falhar, a função limpa o tabuleiro e retorna NULL
 *  Se tudo correr bem devolve o tabuleiro
 ***************/
char **add_col(char **tab ,int lin, int *col){
int i;
char *aux;
for(i=0; i<lin; ++i)
  if( ( aux=realloc(tab[i],sizeof(char)* (*col+1)) )==NULL ){
    printf("Erro ao adicionar uma linha\n");
     fprintf(stderr,ALLOCATION_ERROR);
     free_tab(tab,lin);
     return NULL;
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
    if(tab[j][i]!=tab[j+1][i] || tab[j][i]==' ' || tab[j][i]=='S')
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
 *  O tabuleiro tem de ser quadrado
 *  Devolve 1 em caso afirmativo, e 0 em caso contrario
 ***************/
bool check_diagonal(char **tab, int lin, int col){
if(lin!=col)
  return 0;
int i,j;
bool flag;
for(i=flag=0; i<lin-1; ++i)
  if(tab[i][i]!=tab[i+1][i+1] || tab[i][i]==' ' || tab[i][i]=='S')
    flag=1;
if(flag==0) //se nao ficou a 1 e porque correu tudo bem
  return 1;

for(i=0,j=lin-1; i<lin-1 ; ++i,--j)
  if(tab[i][j]!=tab[i+1][j-1] || tab[i][j]==' ' || tab[i][j]=='S')
    return 0; //como nao ha mais nada para ver, retornamos logo 0
return 1;
}


/*************
 *  char **create_tab_fixed_lc(numero de linhas, numero de colunas)
 *  Faz o mesmo que a funcao "create tab" mas em vez de criar um tabuleiro
 *  como um numero aleatorio de linhas, crias um tabuleiro com as dimensoes
 *  que recebeu como parametros
 ***************/
char **create_tab_fixed_lc(int lin, int col){
char **tab;
int i;
if( (tab=malloc(sizeof(char *)* lin))==NULL ){
  printf("Erro ao alocar espaco para o tabuleiro\n");
  fprintf(stderr,ALLOCATION_ERROR);
  return NULL;
}
for(i=0; i<lin; ++i)
  if( ( tab[i]=(char *)malloc(sizeof(char)* lin) )==NULL ){
     printf("Erro ao alocar espaço para o tabuleiro\n");
     fprintf(stderr,ALLOCATION_ERROR);
     while(--i && i>=0)
       free(tab[i]);
     free(tab);
     return NULL;
  }
init_tab(tab,lin,col);
return tab;
}


/***
 * void tab_copy(tabuleiro original, tabuleiro destino, numero de linhas, numero de colunas)
 * Os tabuleiro tem de ter o mesmo numero de linhas e colunas.
 * Copia dest para orig.
 */ 
void tab_copy(char **orig, char **dest, int lin, int col){
int i,j;
for(i=0; i<lin; ++i)
  for(j=0; j<col; ++j)
    dest[i][j]=orig[i][j];
}