#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "utils.h"
#include "tab.h"
#include "play.h"
#include "linked.h"
#include "files.h"
#include "bot.h"


/*********
 * char menu()
 * Apresenta ao utilizador um menu e pergunta se quer jogar contra outra pessoa ou contra
 * o programa
 * Devolve o carater inserido
 */ 
char menu(){
    char op;
    printf("\n\nBem vindo ao jogo do semaforo!\n\n" "Escolha a sua opcao:\n\n");
    printf("Opcao 1: Jogar contra outro jogador(localmente)\n"
    "Opcao 2: Jogar contra o computador\nOpcao 3: Regras\nOpcao 4: Sair");
    do{
        printf("\n\nOpcao: ");
        scanf(" %c",&op);
        if(op!='1' && op!='2' && op!='3' && op!='4'){
            printf("Por favor selecione uma das opcoes listadas acima\n");
            clean_stdin();
        }
    }while(op!='1' && op!='2' && op!='3' && op!='4');
    return op;
}

void rules_to_txt(){
    FILE *fp;
    if(  (fp=fopen("regras.txt","w") )==NULL ){
        printf("Nao foi possivel criar um ficheiro para armazenar as regras\n");
        return;
    }
    fprintf(fp,"--------Regras--------\n\n");
    fprintf(fp,"O jogo do semaforo tem lugar num tabuleiro dividido em celulas. No inicio o tabuleiro esta vazio"
    " e os jogadores,\njogador A e jogador B, ao longo do jogo, alternadamente vao colocando pecas verdes(G)," 
    " amarelas(Y) ou vermelhas(R).\n"
    "Ganha o jogador que consiga formar uma linha ou coluna com pecas da mesma cor!\n"
    "\nAs jogadas validas relativamente a colocacao de pecas sao as seguintes:\n\n"
    "1.Colocar uma peca verde numa celula vazia\n"
    "2.Trocar uma peca verde por uma amarela\n"
    "3.Trocar uma peca amarela por uma vermelha\n");
    fprintf(fp,"O numero destas pecas e ilimitado");
    fprintf(fp,"\n\nExistem ainda 2 jogadas \"especiais\" que ambos os jogadores podem realizar:\n\n"
    "4.Colocar uma pedra numa celula vazia. Cada jogador pode no maximo colocar 1 pedra numa celula vazia"
    " por jogo.\nA colocacao desta pedra inviabiliza que o jogo possa terminar por preenchimento da linha,"
    " coluna e diagonal afetada\n"
    "5.Adicionar uma linha ou uma coluna vazia ao final do tabuleiro. Por jogo cada jogador pode realizar"
    " esta jogada 2 vezes.");
    fprintf(fp,"\n\nO jogo esta feito de forma a ser intuitivo e facil de jogar, por esse motivo, o programa"
    " ira indicar-lhe sempre quais as jogadas\nque podera realizar, basta carregar no carater associado"
    " a uma jogada(indicado pelo programa) e se for o caso, inserir as coordenadas\nem que quer que a"
    " sua peca seja inserida.\nO programa ira guia-lo em todos os seus pacos!");
    fprintf(fp,"\n\nEm termos de regras do jogo esta praticamente tudo dito, vale a pena salientar que,"
    "pode jogar contra outra pessoa(na mesma maquina)\nou jogar o jogo contra o computador(opcoes que"
    " pode escolher no menu principal)");
    fprintf(fp,"\n\nA meio do jogo podera tambem interromper o jogo para o poder continuar mais tarde,e se o fizer, o jogo sera guardado\n"
    "num ficheiro com o nome \"jogo.bin\", e desde que nao apague este ficheiro, podera fechar a aplicacao\n"
    "e, da proxima vez que a iniciar, o programa dar-lhe-a a opcao de retomar o seu jogo anterior");
    fprintf(fp,"\n\nNo final do jogo, desenhos do tabuleiro e informacao sobre as jogadas serao escritas"
    " num ficheiro .txt, para que possa rever o seu jogo");
    fclose(fp);
}



void rules(){
    char op;
    printf("\n\n--------Regras--------\n\n");
    printf("Bem vindo ao jogo do semaforo!!\n\n"
    "Nesta seccao iremos explicar as regras do jogo brevemente para que possa comecar a jogar o mais cedo"
    " possivel. Daqui a 3 minutos estara pronto para comecar a jogar!\n");
    printf("O jogo do semaforo tem lugar num tabuleiro dividido em celulas. No inicio o tabuleiro esta vazio"
    " e os jogadores,\njogador A e jogador B, ao longo do jogo, alternadamente vao colocando pecas verdes(G)," 
    " amarelas(Y) ou vermelhas(R).\n"
    "Ganha o jogador que consiga formar uma linha ou coluna com pecas da mesma cor!\n"
    "\nAs jogadas validas relativamente a colocacao de pecas sao as seguintes:\n\n"
    "1.Colocar uma peca verde numa celula vazia\n"
    "2.Trocar uma peca verde por uma amarela\n"
    "3.Trocar uma peca amarela por uma vermelha\n");
    printf("O numero destas pecas e ilimitado");
    printf("\n\nExistem ainda 2 jogadas \"especiais\" que ambos os jogadores podem realizar:\n\n"
    "4.Colocar uma pedra numa celula vazia. Cada jogador pode no maximo colocar 1 pedra numa celula vazia"
    " por jogo.\nA colocacao desta pedra inviabiliza que o jogo possa terminar por preenchimento da linha,"
    " coluna e diagonal afetada\n"
    "5.Adicionar uma linha ou uma coluna vazia ao final do tabuleiro. Por jogo cada jogador pode realizar"
    " esta jogada 2 vezes.");
    printf("\n\nO jogo esta feito de forma a ser intuitivo e facil de jogar, por esse motivo, o programa"
    " ira indicar-lhe sempre quais as jogadas\nque podera realizar, basta carregar no carater associado"
    " a uma jogada(indicado pelo programa) e se for o caso, inserir as coordenadas\nem que quer que a"
    " sua peca seja inserida.\nO programa ira guia-lo em todos os seus pacos!");
    printf("\n\nEm termos de regras do jogo esta praticamente tudo dito, vale a pena salientar que,"
    "pode jogar contra outra pessoa(na mesma maquina)\nou jogar o jogo contra o computador(opcoes que"
    " pode escolher no menu principal)");
    printf("\n\nA meio do jogo podera tambem interromper o jogo para o poder continuar mais tarde,e se o fizer, o jogo sera guardado\n"
    "num ficheiro com o nome \"jogo.bin\", e desde que nao apague este ficheiro, podera fechar a aplicacao\n"
    "e, da proxima vez que a iniciar, o programa dar-lhe-a a opcao de retomar o seu jogo anterior");
    printf("\n\nNo final do jogo, desenhos do tabuleiro e informacao sobre as jogadas serao escritas"
    " num ficheiro .txt, para que possa rever o seu jogo");
    printf("\n\nAgora que ja sabe as regras esta pronto para jogar! Divirta-se!!!");
    printf("\n\n\nDeseja guardar estas regras num ficheiro de texto para as poder consultar a meio do jogo?\n");
    do{
        printf("\nS(sim) ou N(nao)\nOpcao: ");
        scanf(" %c",&op);
        if(op!='S' && op!='N'){
            printf("Por favor digite ou S ou N\n");
            clean_stdin();
        }
    }while(op!='S' && op!='N');
    if(op=='S')
        rules_to_txt();
}


/*********
 * init_player(ponteiro para jogador, carater que representa o nome do jogador)
 * Incializa as abilidades que nao dependem do estado do tabuleiro do jogador
 * Da tambem um nome ao jogador
 */ 
static void init_player(struct player *a, char name){
    a->ability.rock=1;
    a->ability.lc=2;
    a->ability.k_interrupt=0;
    a->name=name;
}


/*********
 * check_victory(tabuleiro de jogo, numero de linhas, numero de colunas, jogador que pode
 * ter vencido)
 * Verifica se o jogador 'a' venceu o jogo e em caso afirmativo retorna 1 e escreve uma 
 * mensagem, seguida de um desenho do tabuleiro
 * Em caso de nao vitoria retorna 0.
 */ 
static bool check_victory(char **tab, int lin, int col, struct player a){
    if(check_lins(tab,lin,col)==1 || check_cols(tab,lin,col)==1 || check_diagonals(tab,lin,col)==1){
        printf("\n\nO jogador %c venceu o jogo!!!\n\n",a.name);
        draw_tab(tab,lin,col);
        return 1;
    }
    return 0;
}

/*********
 * check_tie(tabuleiro de jogo, numero de linhas, numero de colunas, jogador a, jogador b)
 * Acede às habilidades do jogador 'a' e 'b' para determinar se houve um empate.
 * Devolve 1 e escreve uma mensagem seguida do tabuleiro em caso afirmativo
 * Devolve 0 se nao houve empate
 */ 
static bool check_tie(char **tab, int lin, int col, struct player a, struct player b){
    //o ultimo jogador a jogar pode ter tornado impossivel continuar o jogo, logo precisamos
    //de atualizar os dois jogadores para ver se ainda  ha jogadas possiveis
    update_player(tab,lin,col,0,&a); update_player(tab,lin,col,0,&b); 
    return a.ability.green+a.ability.red+a.ability.yellow+a.ability.lc+
    b.ability.green+b.ability.red+b.ability.yellow+b.ability.lc;
}


/*********
 * int get_k(numero de linhas, numero de colunas, turno atual)
 * Obriga o utilizador a introduzir um numero de jogadas valido, k in [1, turn-1].
 * devolve o k inserido pelo utilizador.
 */ 
static int get_k(int turn){
    int k;
    int flag=0;
    printf("Digite o numero de jogadas que quer ver atras: ");
    do{
        if( ( flag=scanf("%d",&k) ) !=1){
            printf("Digite um numero por favor ");
            clean_stdin();
            continue;
        }
      if(k>=turn || k<=0)
          printf("Digite um k valido entre 1 e %d: ",turn-1);
      clean_stdin();
    }while(flag!=1 || k>=turn || k<=0 );
}

/****
 * static bool load_players(ponteiro para o jogador a, ponteiro para o jogador b)
 * Abre o ficheiro "jogo.bin" e extrai para os jogadores a e b, os valores que tinham 
 * quando o jogo foi interrompido
 * Devolve 1 em caso de sucesso.
 * Devolve 0 em caso de erro.
 */
static bool load_players(struct player *a , struct player *b){
    FILE *fp;
    if( ( fp=fopen("jogo.bin","rb") )==NULL ){
        printf("Nao foi possivel abrir o ficheiro que continha informacao para retomar o jogo\n");
        return 0;
    }
    fseek(fp,sizeof(bool),SEEK_SET); //saltar o game_mode
    fread(a,sizeof(struct player),1,fp);
    fread(b,sizeof(struct player),1,fp);
    fclose(fp);
    return 1;
}

/***
 * Abre o ficheiro "jogo.bin" e, nas variavies apontadas por cada um dos parametros, repoe 
 * os valores que tinham antes de o jogo ser interrompido.
 * Coloca em "*tab" o tabuleiro e atualiza "*lin" e "*col"(linhas e colunas)
 * Coloca "*states" a apontar para a cabeca da lista, e "*end" fica a apontar para o ultimo no da lista
 * Devolve o turno em que o jogo estava em caso de sucesso.
 * Devolve 0 em caso de erro.
 */ 
static int load_tab_list(char ***tab, int *lin, int *col, struct list_head **states, struct list_node **end){
    struct list_node temp, *curr;
    FILE *fp;
    if( ( fp=fopen("jogo.bin","rb") )==NULL ){
        printf("Nao foi possivel abrir o ficheiro que continha informacao para retomar o jogo\n");
        return 0;
    }
    //saltar o que nao interessa
    fseek(fp,sizeof(bool),SEEK_SET); fseek(fp,sizeof(struct player),SEEK_CUR); fseek(fp,sizeof(struct player),SEEK_CUR);

    fread(lin,sizeof(int),1,fp); fread(col,sizeof(int),1,fp);

    if ( ( *states=create_head(*lin,*col) )==NULL ){
        printf("O programa terminara\n");
        return 0;
    }
    fread(&temp,sizeof(struct list_node),1,fp);
    add_node_in_head(*states,temp.lin,temp.col,temp.player_name,temp.piece,temp.place);
    curr=(*states)->next;
    place_piece_in_head_tab(*states,*curr);

    while( fread(&temp,sizeof(struct list_node),1,fp) ==1 ){
        add_node_to_node(*states,curr,temp.lin,temp.col,temp.player_name,temp.piece,temp.place);
        curr=curr->next; 
        place_piece_in_head_tab(*states,*curr); 
    }

    *lin=curr->lin; *col=curr->col;
    *end=curr;//atualizar o turno da lista

    *tab=create_tab_fixed_lc(*lin,*col);
    tab_copy( (*states)->tab,*tab,*lin,*col);
    if(reset_tab_in_head(*states,curr)==0 ){
        printf("O programa ira terminar\n");
        return 0;
    }

    return curr->turn;
}


/**
 * Funcao responsavel por pedir uma jogada ao utilizador, realiza-la, e atualizar o que necessita 
 * de ser alterado(tabuleiro, numero de linhas, habilidades do jogador, etc)
 */ 
void player_plays(char ***tab, int *lin, int *col, struct coordinates *place, struct player *aux, int turn, char *piece){
    draw_tab(*tab,*lin,*col);
    update_player(*tab,*lin,*col,turn,aux);
    show_plays(*aux);
    *piece=ask_play(*aux);
    if(*piece!='K' && *piece!='L' && *piece!='C' && *piece!='I') //carateres nao colocaveis
        do{
            ask_place(place,*lin,*col);  
        }while(interpret_play(*tab,*lin,*col,*piece,*place,aux)==1);
    if(*piece=='L' || *piece=='C')
        if( add_l_c(tab, lin, col,*piece,aux)==NULL)
            return ;
}


/**
 * static void show_k_prev_info(turno atual, cabeca da lista, no atual da lista)
 * Pede por um numero de jogadas anteriores para serem visualizadas e apresenta informacao e o
 * estado do tabuleiro nas k, jogadas anteriores
 */ 
static void show_k_prev_info(int turn, struct list_head *states, struct list_node *curr){
    int k;
    k=get_k(turn);
    printf("\n\nAs %d jogadas anteriores foram: \n\n",k);
    show_k_prev(k,states,curr);
    printf("Pressione a tecla ENTER para voltar ao jogo: ");
    clean_stdin();
}


void game(bool game_mode, bool resume){
    char **tab,piece=1;
    int lin,col,turn,k;
    struct coordinates place;
    struct player a,b,*aux;
    struct list_head *states; 
    struct list_node *curr; 
    if(resume==RESUME_GAME){
        load_players(&a,&b);
        turn=load_tab_list(&tab,&lin,&col,&states,&curr);
    }
    else{ //comecar jogo do zero
        if( ( tab=create_tab(&lin,&col) )==NULL ){
            printf("O programa terminara\n");
            return ;
        }
        if( ( states=create_head(lin,col) )==NULL   ){//criar linked list
            free_tab(tab,lin);
            printf("O programa ira terminar");
            return ;
        }
        init_player(&a,'A'); init_player(&b,'B'); turn=1;
    }

    //inicio efetivo do jogo
    while(check_victory(tab,lin,col,*aux)!=1 || check_tie(tab,lin,col,a,b)!=1){
        printf("\n\nTurno %d, vez do jogador %c\n\n",turn,turn%2==0 ? 'B' : 'A'); //pares B, impares A
        if(turn%2==0)
            aux=&b;
        else
            aux=&a;
    
      if(game_mode==BOT_GAME && aux==&b){ //vez do bot
            bot_plays(&tab,&lin,&col,&piece,&place,aux);
            show_bot_play(*aux,piece,place);
            draw_tab(tab,lin,col);
            printf("\n\nPrima a tecla ENTER para fazer a sua jogada ");
            clean_stdin();
      }

      else{ //jogador humano
            player_plays(&tab,&lin,&col,&place,aux,turn,&piece);
            if(piece=='K'){
                show_k_prev_info(turn,states,curr);
                continue;
            }
            if(piece=='I'){
                printf("\nO jogo ira terminar mas sera guardado num ficheiro para o poder continuar"
                " posteriormente\n");
                export_bin(*states,a,b,states->lin,states->col,game_mode);//lin e col iniciais
                free_tab(tab,lin);
                free_head_and_tab_in_head(states,curr->lin); 
                return ;
            }
      }

      //operacoes na linked list
      if(turn==1){//criar o primeiro no
            if(add_node_in_head(states,lin,col,aux->name,piece,place)==0 ) {
                free_tab(tab,lin); //a lista ja esta limpa
                return ;
            }
        curr=states->next;
      }
      else{ //estamos em qualquer outro turno
          if(add_node_to_node(states,curr,lin,col,aux->name,piece,place)==0 ){
            free_tab(tab,lin); //a lista ja esta limpa
            return ;
            }
          curr=curr->next;
      }
      ++turn;
    }
    //fim do jogo
    free_tab(tab,lin); //apagar o tabuleiro

    if( reset_tab_in_head(states,curr)==0 ){
        fprintf(stderr,"Erro ao exportar os estados do tabuleiro para um ficheiro\n");
        return ; //a lista ja esta limpa
    }
    export_states_txt(states,game_mode);
    free_head_and_tab_in_head(states,curr->lin);
}

