#include <stdio.h>
#include "play.h"
#include "tab.h"
#include "utils.h"

#define INVALiD_PLAY "Atualmente nao pode fazer essa jogada\n"
#define OCC_POS "Escolheu uma posicao do tabuleiro ja ocupada\n"

/*******
 * static bool cell_has_piece(tabuleiro de jogo, peca de jogo, coordenadas de uma celula do tabuleiro)
 * Retorna 1 se "piece" estiver na posicao "place"
 * Retorna 0 caso contrario
 *******/
static bool cell_has_piece(char **tab, char piece ,struct coordinates place){
    return tab[place.x][place.y]==piece;
}

/*******
 * static bool is_valid_place(coordenadas de uma celula do tabuleiro, numero de linhas do tabuleiro, 
 * numero de colunas do tabuleiro)
 * Retorna 1 se "place" representar uma coordenada de uma celula do tabuleiro
 * Retorna 0 caso contrario
 */
static bool is_valid_place(struct coordinates place, int lin, int col){
    return place.x<=lin && place.x>=1 && place.y<=col && place.y>=1;
}

/**********
 *  static bool validate_play(jogador, carater que representa uma jogada)
 *  Retorna 0 se "play" nao representar uma jogada valida, ou se o jogador nao puder realizar essa jogada
 *  Retorna 1 se a jogada for valida
 *********/ 
static bool validate_play(struct player a, char play){
    switch(play){
        case 'G':
            if(a.ability.green==0){
                printf(INVALiD_PLAY);
                return 0;
            }
        break;

        case 'Y':
            if(a.ability.yellow==0){
                printf(INVALiD_PLAY);
                return 0;
            }
        break; 

        case 'R':
            if(a.ability.red==0){
                printf(INVALiD_PLAY);
                return 0;
            }
        break;

        case 'S':
            if(a.ability.rock==0){
                printf(INVALiD_PLAY);
                return 0;
            }
        break;

      case 'L' :
            if(a.ability.lc==0){
                printf(INVALiD_PLAY);
                return 0;
            }
      break;

      case 'C' :
            if(a.ability.lc==0){
                printf(INVALiD_PLAY);
                return 0;
            }
      break;

      case 'I' : 
            if(a.ability.k_interrupt==0){
                printf(INVALiD_PLAY);
                return 0;
            }
      break;

      case 'K' : 
            if(a.ability.k_interrupt==0){
                printf(INVALiD_PLAY);
                return 0;
            }
      break;

      default: 
            printf("Por favor digite um carater valido\n");
            return 0;
    }
    return 1;
}


/**********
 * void update_player(tabuleiro de jogo, numero de linhas do tabuleiro, numero de colunas do tabuleiro
 * turno do jogo, ponteiro para o jogador atual)
 * Percorre todo o tabuleiro e atualiza as jogadas do jogador recebido por referencia com um 0 ou 1
 * 0 indica que o jogador nao pode fazer essa jogada
 * 1 indica que o jogador pode fazer essa jogada
 ***********/ 
void update_player(char **tab, int lin, int col, int turn ,struct player *a){
    int i,j;
    a->ability.green=a->ability.yellow=a->ability.red=0;
    for(i=0; i<lin; ++i)
        for(j=0; j<col; ++j)
            switch(tab[i][j]){
                case ' ': 
                    a->ability.green=1;
                break;

                case 'G':
                a->ability.yellow=1;
                break;

                case 'Y':
                    a->ability.red=1;
                break;
            }
    if(turn>1)
        a->ability.k_interrupt=1;
}


/**********
 * void show_plays(jogador)
 * Escreve na consola, todas as jogadas que o jogador pode realizar
 *********/ 
void show_plays(struct player a){
    printf("\n\nAs jogadas que pode fazer sao:\n"
    "%s%s%s",a.ability.green==1 ? "Adicionar uma peca verde numa celula vazia (G)\n" : "\0",
    a.ability.yellow==1 ? "Trocar uma peca verde por uma amarela (Y)\n" : "\0",
    a.ability.red==1 ? "Trocar uma peca amarela por uma vermelha (R)\n" : "\0");
    if(a.ability.rock==1)
        printf("Colocar uma pedra numa celula vazia (S) (%d restantes)\n",a.ability.rock);
    if(a.ability.lc!=0)
        printf("Adicionar uma linha ou coluna (L ou C) (%d restantes) \n",a.ability.lc);
    if(a.ability.k_interrupt!=0)
        printf("Ver as k jogadas anteriores(K)\n"
        "Interromper o jogo para ser ou nao retomado posteriormente(I)\n");
}


/**********
 *  char ask_play(jogador atual)
 *  Pede por um carater ao utilizador até ele digitar um carater valido,
 *  ou seja, uma jogada que o jogador atual possa fazer no momento
 *  Devolve o carater inserido
 *********/ 
char ask_play(struct player a){
    char play;
    bool valid;
    printf("\n\nDigite uma jogada das listadas acima: ");
        do{
            scanf(" %c",&play);
            if( ( valid=validate_play(a,play) )==0 ){
                printf("Por favor digite uma jogada das listadas acima: ");
                clean_stdin();
            }
        }while(valid==0);
        clean_stdin();
        return play;
}


/*******
 * void ask_place(ponteiro para coordenadas de uma celula do tabuleiro, numero de linhas do tabuleiro, 
 * numero de colunas do tabuleiro)
 * Obriga o utilizador a introduzir coordenadas que estejam dentro do tabuleiro
 * Coloca as coordenadas introduzidas em "place"
 */
void ask_place(struct coordinates *place, int lin, int col){
    int n_inputs=0, valid_place=0;
    printf("Digite as coordenadas do tabuleiro em que quer inserir a peca: ");
    do{
        if( ( n_inputs=scanf("%d%d",&place->x,&place->y) ) !=2){
            printf("Digite as coordenadas no formato certo x y: ");
            clean_stdin();
            continue; 
        }
        if( ( valid_place=is_valid_place(*place,lin,col) ) ==0)
            printf("Digite coordenadas validas: ");
      clean_stdin();
    }while(n_inputs!=2 || valid_place==0);
}


/*******
 * bool interpret_play(tabuleiro de jogo, numero de linhas do tabuleiro, numero de colunas do tabuleiro
 * ,carater que representa uma jogada, coordenadas de uma celula do tabuleiro, ponteiro para jogador)
 * Se "play" for uma jogada valida coloca no tabuleiro, na posicao "place", a peca que corresponde a essa jogada 
 * e atualiza as jogadas que o jogador pode realizar, se for necessario
 * Retorna 1 se a jogada for valida
 * Retorna 0 a jogada for invalida.
 */
bool interpret_play(char **tab, int lin, int col, char play, struct coordinates place, struct player *a){
    --place.x; --place.y; //coordenadas foram introduzidas pelo utilizador
    switch(play){
        case 'G': 
            if(cell_has_piece(tab,' ',place)==0){ //se nao tiver ' ' nao se pode meter verde
                printf(OCC_POS);
                return 0;
            }
            tab[place.x][place.y]='G';
        break;

        case 'Y' : 
            if(cell_has_piece(tab,'G',place)==0){
                printf("Nessa posicao nao esta uma peca verde para ser trocada\n");
                return 0;
            }
            tab[place.x][place.y]='Y';
        break;

        case 'R': 
            if(cell_has_piece(tab,'Y',place)==0){
                printf("Nessa posicao nao esta uma peca amarela para ser trocada\n");
                return 0;
            }
            tab[place.x][place.y]='R';
        break;

        case 'S': 
            if(cell_has_piece(tab,' ',place)==0){
                printf(OCC_POS);
                return 0; 
            }
            tab[place.x][place.y]='S';
            a->ability.rock=0;
        break;
      }
    return 1;
}


/*******
 * char ** add_l_c(tabuleiro de jogo, ponteiro para o numero de linhas do tabuleiro,
 * ponteiro para o numero de colunas do tabuleiro, jogada , ponteiro para jogador)
 * Conforme o valor de "play"('C' ou 'L'), adiciona uma linha ou uma coluna ao tabuleiro de jogo, atualizando
 * tambem as linhas ou as colunas(recebidas por referencia), dependendo do valor de "play"
 * Decrementa a habilidade de inserir linhas ou colunas do jogador recebido por referencia
 * Em caso de sucesso devolve o tabuleiro do jogo com dimensoes aumentadas.
 * Em caso de erro limpa o tabuleiro de jogo e retorna NULL
 */
char **add_l_c(char **tab, int *lin, int *col, char play, struct player *a){
    if(play=='C'){
        if( add_col(tab,*lin,col)==NULL)
            return NULL;
        a->ability.lc-=1;
    }
    else{ 
        if( ( tab=add_lin(tab,lin,*col) )==NULL)
            return NULL;
        a->ability.lc-=1;
    }
return tab;
}