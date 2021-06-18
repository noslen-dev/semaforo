/*
 * Nome: Nelson Forte Simao
 * Numero: 2020132648 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tab.h"
#include "utils.h"


/*************
 * static void init_lin(ponteiro para uma linha do tabuleiro, numero de colunas do tabuleiro)
 * Inicializa com ' ' a linha apontada pelo parametro "lin"
 ***************/
static void init_lin(char *lin, int col){
    int i;
    for(i=0; i<col; ++i)
        lin[i]=' ';
}

/*************
 * static void init_col(tabuleiro de jogo, numero de linhas do tabuleiro,
 * indice de uma coluna do tabuleiro)
 * Inicializa com ' ', a coluna do tabuleiro que corresponde ao indice passado como argumento
 ***************/
static void init_col(char **tab, int lin, int col){
    int i;
    for(i=0; i<lin; ++i)
        tab[i][col]=' ';
}

/*************
 *  static void init_tab(tabuleiro de jogo, numero de linhas do tabuleiro, numero de colunas do tabuleiro)
 *  Utiliza a função "init_lin", para colocar todas as posições do tabuleiro com ' '
 ***************/
static void init_tab(char **tab, int lin ,int col){
    int i;
    for(i=0; i<lin; ++i)
        init_lin(tab[i],col);
}


/*************
 * void free_tab(tabuleiro de jogo, numero de linhas do tabuleiro)
 * Liberta o tabuleiro de jogo
 ***************/
void free_tab(char **tab, int lin){
    int i;
    for(i=0; i<lin; ++i)
        free(tab[i]);
    free(tab);
}

/*************
 *  Cria um tabuleiro de jogo, quadrado com um numero de linhas entre [3,5]
 *  e guarda as dimensoes do tabuleiro criado nos parametros correspondentes
 *  Preenche o tabuleiro com ' '
 *  Se todas as alocacoes correrem bem, devolve o tabuleiro criado
 *  Senao devolve NULL
 *  Esta funcao nao deixa memoria por limpar
 ***************/
char **create_tab(int *lin, int *col){
    char **tab;
    int i;
    *lin=*col=5;
    if( (tab=(char **)malloc(sizeof(char *)* *lin))==NULL ){
        fprintf(stderr,"Erro ao criar o tabuleiro\n");
        return NULL;
    }
    for(i=0; i<*lin; ++i)
        if( ( tab[i]=(char *)malloc(sizeof(char)* *lin) )==NULL ){
            fprintf(stderr,"Erro ao criar o tabuleiro\n");
            free_tab(tab,i);
            return NULL;
      }
    init_tab(tab,*lin,*col);
    return tab;
}


/*************
 *  void draw_tab(tabuleiro de jogo, numero de linhas do tabuleiro, numero de colunas do tabuleiro)
 *  Desenha o tabuleiro de jogo.
 ***************/
void draw_tab(char **tab, int lin, int col){
    int i,j,aux;
    printf("    ");
    for(i=0; i<col; ++i)
        if(i+1!=col)
            printf("----");
        else
            printf("-----");
        putchar('\n');
        
    for(i=0; i<lin; ++i){
        printf("  %d ",i+1);
        putchar('|'); 
        for(j=0; j<col; ++j)
            printf(" %c %c",tab[i][j],'|');
            printf("\n    ");
        for(aux=0; aux<col; ++aux)
            if(aux+1!=col)
                printf("----");
            else
                printf("-----");
        putchar('\n');
    }
    printf("      ");
    for(i=0; i<col; ++i)
        printf("%d   ",i+1);
}



/*************
 *  void add_lin(tabuleiro de jogo, ponteiro para o numero de linhas do tabuleiro, 
 *  numero de colunas do tabuleiro)
 *  Adiciona uma linha ao tabuleiro de jogo, e preenche a linha com ' '
 *  Incrementa o numero de linhas(recebido como argumento)
 *  Se a alocacao falhar, a função limpa o tabuleiro e retorna NULL
 *  Se tudo correr bem devolve o tabuleiro
 ***************/
char **add_lin(char **tab ,int *lin, int col){
    char **aux;
    if( (aux=(char**)realloc(tab,sizeof(char *)*(*lin+1)) )==NULL ){
        fprintf(stderr,"Erro ao adicionar uma linha ao tabuleiro\n");
        free_tab(tab,*lin);
        return NULL;
    }
    ++*lin;
    tab=aux;
    if( (tab[*lin-1]=(char *)malloc(sizeof(char)*col))==NULL ){
        fprintf(stderr,"Erro ao adicionar uma linha ao tabuleiro\n");
        free_tab(tab,*lin-1);
        return NULL;
    }
    init_lin(tab[*lin-1],col);
    return tab;
}



/*************
 *  void add_col(tabuleiro de jogo, numero de linhas do tabuleiro, 
 *  ponteiro para o numero de colunas do tabuleiro)
 *  Adiciona uma coluna ao tabuleiro, e inicializa essa coluna com ' '
 *  Incrementa o numero de colunas(recebido como argumento)
 *  Se a alocacao falhar, a função limpa o tabuleiro e retorna NULL
 *  Se tudo correr bem devolve o tabuleiro
 ***************/
char **add_col(char **tab ,int lin, int *col){
    int i;
    char *aux;
    for(i=0; i<lin; ++i)
        if( ( aux=(char *)realloc(tab[i],sizeof(char)* (*col+1)) )==NULL ){
            fprintf(stderr,"Erro ao adicionar uma coluna ao tabuleiro\n");
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
 *  bool check_lins(tabuleiro de jogo, numero de linhas do tabuleiro, 
 *  numero de colunas do tabuleiro)
 *  Verifica, linha a linha, se uma linha tem so carateres iguais que nao sejam 'S' e ' '
 *  Devolve 1 em caso afirmativo, e 0 em caso contrario
 ***************/
bool check_lins(char **tab, int lin, int col){
    int i,j;
    bool flag=0;
    for(i=0; i<lin; ++i){
        for(j=flag=0; j<col-1 && !flag; ++j)
            if(tab[i][j]!=tab[i][j+1] || tab[i][j]==' ' || tab[i][j]=='S')
                flag=1;
        if(flag==0)
            return 1;
    }
    return 0;
}


/*************
 *  bool check_cols(tabuleiro de jogo, numero de linhas do tabuleiro, numero de colunas do tabuleiro)
 *  Verifica, coluna a coluna, se uma coluna tem so carateres iguais que nao sejam 'S' e ' '
 *  Devolve 1 em caso afirmativo, e 0 em caso contrario
 ***************/
bool check_cols(char **tab, int lin, int col){
    int i,j;
    bool flag=0;
    for(i=0; i<col; ++i){
        for(j=flag=0; j<lin-1 && !flag; ++j)
            if(tab[j][i]!=tab[j+1][i] || tab[j][i]==' ' || tab[j][i]=='S')
                flag=1;
        if(flag==0)
            return 1;
    }
return 0;
}


/*************
 *  bool check_diagonals(tabuleiro de jogo, numero de linhas do tabuleiro, 
 *  numero de colunas do tabuleiro)
 *  Verifica se qualquer uma das diagonais contem carateres todos iguais exeto ' ' e 'S'
 *  Devolve 1 em caso afirmativo, e 0 em caso contrario
 ***************/
bool check_diagonals(char **tab, int lin, int col){
    if(lin!=col)
        return 0;
    int i,j;
    bool flag;
    for(i=flag=0; i<lin-1 && !flag; ++i)
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
 *  Cria um tabuleiro de jogo "lin" x "col"
 *  Devolve o tabuleiro em caso de sucesso
 *  Devolve NULL em caso de erro
 *  Esta funcao nao deixa memoria por libertar
 ***************/
char **create_tab_fixed_lc(int lin, int col){
    char **tab;
    int i;
    if( (tab=malloc(sizeof(char *)* lin))==NULL ){
        fprintf(stderr,"Erro ao criar um tabuleiro de tamanho fixo\n");
        return NULL; 
    }
    for(i=0; i<lin; ++i)
        if( ( tab[i]=(char *)malloc(sizeof(char)* lin) )==NULL ){
            fprintf(stderr,"Erro ao criar um tabuleiro de tamanho fixo\n");
            free_tab(tab,i);
            return NULL;
        }
    init_tab(tab,lin,col);
    return tab;
}


/***
 * void tab_copy(tabuleiro original, tabuleiro destino, numero de linhas do tabuleiro original, 
 * numero de colunas do tabuleiro original)
 * Copia os conteudos de "orig" para "dest".
 */ 
void tab_copy(char **orig, char **dest, int lin, int col){
    int i,j;
    for(i=0; i<lin; ++i)
        for(j=0; j<col; ++j)
            dest[i][j]=orig[i][j];
}