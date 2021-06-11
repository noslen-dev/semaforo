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

/***
 * static void rules_to_txt()
 * Cria um ficheiro de nome "regras.txt" e escreve nele as regras do jogo
 */ 
static void rules_to_txt(){
    FILE *fp;
    if(  (fp=fopen("regras.txt","w") )==NULL ){
        printf("Nao foi possivel criar um ficheiro para armazenar as regras\n");
        return;
    }
    fprintf(fp,"======== Regras ========\n\n");
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

/***
 * void rules()
 * Escreve na consola as regras do jogo, e pergunta ao utilizador se quer guardar as regras num
 * ficheiro .txt, se o utilizador inserir que sim ('S'), a funcao "rules_to_txt" e chamada.
 */ 
void rules(){
    char op;
    printf("\n\n======== Regras ========\n\n");
    printf("Bem vindo ao jogo do semaforo!!\n\n"
    "Nesta seccao iremos explicar as regras do jogo brevemente para que possa comecar a jogar o mais cedo"
    " possivel. Daqui a 3 minutos estara pronto para comecar a jogar!\n\n\n");
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
 * char menu()
 * Apresenta ao utilizador o menu incial com opcoes para escolher
 * Devolve o carater inserido
 */ 
char menu(){
    char op;
    printf("\n\n========== Jogo do semaforo ==========\n\n");
    printf("Bem vindo ao jogo do semaforo!\n\nEscolha uma opcao:\n\n");
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




/*********
 * static void init_player(ponteiro para jogador, carater que representa o nome do jogador)
 * Incializa as jogadas ,que nao dependem do estado do tabuleiro, do jogador recebido por referencia
 * Da tambem um nome ao jogador
 */ 
static void init_player(struct player *a, char name){
    a->ability.rock=1;
    a->ability.lc=2;
    a->ability.k_interrupt=0;
    a->name=name;
}


/*********
 * static bool check_victory(tabuleiro de jogo, numero de linhas do tabuleiro, 
 * numero de colunas do tabuleiro, jogador)
 * Verifica se o jogador passado como argumento venceu o jogo
 * Em caso de vitoria, retorna 1, caso contrario retorna 0
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
 * static int get_k(turno atual do jogo)
 * Obriga o utilizador a introduzir um numero de jogadas anteriores para visualizar valido(in [1, "turn"-1]).
 * devolve o numero inserido pelo utilizador.
 */ 
static int get_k(int turn){
    int k;
    bool flag=0;
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
return k;
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
        fprintf(stderr,"Nao foi possivel abrir o ficheiro \"jogo.bin\" que continha informacao para" 
        "retomar o jogo\n");
        return 0;
    }
    fseek(fp,sizeof(bool),SEEK_SET); //saltar o game_mode
    fread(a,sizeof(struct player),1,fp);
    fread(b,sizeof(struct player),1,fp);
    fclose(fp);
    return 1;
}

/***
 * Abre o ficheiro "jogo.bin" e, nas variaveis apontadas por cada um dos parametros, repoe 
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
        fprintf(stderr,"Nao foi possivel abrir o ficheiro \"jogo.bin\" que continha informacao para" 
        "retomar o jogo\n");
        return 0; 
    }

    //saltar o que nao interessa
    fseek(fp,sizeof(bool),SEEK_SET); fseek(fp,sizeof(struct player),SEEK_CUR); fseek(fp,sizeof(struct player),SEEK_CUR);

    fread(lin,sizeof(int),1,fp); fread(col,sizeof(int),1,fp);

    if ( ( *states=create_head(*lin,*col) )==NULL ){
        fclose(fp);
        return 0;
    }
    fread(&temp,sizeof(struct list_node),1,fp);
    if( ( add_node_in_head(*states,temp.lin,temp.col,temp.player_name,temp.piece,temp.place) )==0 ){
        fclose(fp);
        return 0;
    }
    curr=(*states)->next;
    if( place_piece_in_head_tab(*states,*curr)==0 ){
        fclose(fp);
        return 0;
    }

    while( fread(&temp,sizeof(struct list_node),1,fp) ==1 ){
        if( add_node_to_node(*states,curr,temp.lin,temp.col,temp.player_name,temp.piece,temp.place)==0 ){
            fclose(fp);
            return 0;
        }
        curr=curr->next; 
        if( place_piece_in_head_tab(*states,*curr)==0 ){
            fclose(fp);
            return 0; 
        }
    }

    *lin=curr->lin; *col=curr->col;
    *end=curr;

    if( ( *tab=create_tab_fixed_lc(*lin,*col) )==NULL ){
        free_head_and_tab_in_head(*states,curr->lin); //antes do reset o tab em states esta todo alterado
        fclose(fp);
        return 0;
    }
    tab_copy( (*states)->tab,*tab,*lin,*col);
    if(reset_tab_in_head(*states,*lin)==0 ){
        fclose(fp);
        return 0;
    }
    fclose(fp);
    return curr->turn+1; //estamos no turno em que o no ainda nao foi criado
}


/**
 * Funcao responsavel por pedir uma jogada ao utilizador, realiza-la, e atualizar o que necessita 
 * de ser alterado(tabuleiro, numero de linhas, habilidades do jogador, etc )
 * Devolve 1 em caso de sucesso (a jogada foi bem feita)
 * Devolve 0 se a realizacao da jogada falhou e limpa o tabuleiro de jogo
 */ 
bool player_plays(char ***tab, int *lin, int *col, struct coordinates *place, struct player *aux, int turn, char *piece){
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
            return 0;
return 1;
}


/****
 * void game(modo de jogo, se o jogo deve ser resumido )
 * Esta funcao executa o jogo e tudo relacionado com ele
 */
void game(bool game_mode, bool resume){
    char **tab,piece;
    int lin,col,turn,k;
    struct coordinates place;
    struct player a,b,*aux;
    struct list_head *states; 
    struct list_node *curr; 
    if(resume==RESUME_GAME){
        if( load_players(&a,&b)==0  || ( turn=load_tab_list(&tab,&lin,&col,&states,&curr) )==0 ){
            fprintf(stderr,"O programa ira terminar devido a impossibilidade de retomar o jogo\n");
            return ;
        }
    }
    else{ //comecar jogo do zero
        if( ( tab=create_tab(&lin,&col) )==NULL || ( states=create_head(lin,col) )==NULL ){
            printf("O programa ira terminar devido a impossibilidade de retomar o jogo\n");
            return ;
        }
        init_player(&a,'A'); init_player(&b,'B'); turn=1;
    }

    //inicio efetivo do jogo
    while(check_victory(tab,lin,col,*aux)!=1){
        printf("\n\nTurno %d, vez do jogador %c\n\n",turn,turn%2==0 ? 'B' : 'A'); //pares B, impares A
        if(turn%2==0)
            aux=&b;
        else
            aux=&a;
    
      if(game_mode==BOT_GAME && aux==&b){ //vez do bot
            if( bot_plays(&tab,&lin,&col,&piece,&place,aux)==0 ){ //falhamos a adicionar linhas ou colunas a tab
                free(tab);
                free_head_and_tab_in_head(states,curr->lin);
                return ;    
            }
            show_bot_play(*aux,piece,place);
            draw_tab(tab,lin,col);
            printf("\n\nPrima a tecla ENTER para fazer a sua jogada ");
            clean_stdin();
      }

      else{ //jogador humano
            if( player_plays(&tab,&lin,&col,&place,aux,turn,&piece)==0 ){
                free_head_and_tab_in_head(states,curr->lin);
                return ;
            }
            if(piece=='K'){
                k=get_k(turn);
                printf("\n\nAs %d jogadas anteriores foram: \n\n",k);
                if( show_k_prev(k,states,curr)==0 ){
                    free(tab); 
                    return ;
                }
                printf("Pressione a tecla ENTER para voltar ao jogo: ");
                clean_stdin();
                continue;
            }
            if(piece=='I'){
                printf("\nO jogo ira terminar mas sera guardado num ficheiro para o poder continuar"
                " posteriormente\n");
                if( export_bin(*states,a,b,states->lin,states->col,game_mode)==0 )
                    printf("O seu jogo nao sera guardado num ficheiro .bin\n");
                free_tab(tab,lin);
                free_head_and_tab_in_head(states,curr->lin); 
                return ;
            }
      }

      //operacoes na linked list
      if(turn==1){//criar o primeiro no
            if(add_node_in_head(states,lin,col,aux->name,piece,place)==0 ) {
                free_tab(tab,lin);
                return ;
            }
        curr=states->next;
      }
      else{ //estamos em qualquer outro turno
          if(add_node_to_node(states,curr,lin,col,aux->name,piece,place)==0 ){
            free_tab(tab,lin); 
            return ;
            }
          curr=curr->next;
      }
      ++turn;
    }
    //fim do jogo
    free_tab(tab,lin); //apagar o tabuleiro

    if(resume==RESUME_GAME)
        remove("jogo.bin"); //apagar o jogo anterior
        
    if( export_states_txt(states,game_mode)==0 )
        printf("O seu jogo nao sera guardado num ficheiro .txt\n");
    free_head_and_tab_in_head(states,curr->lin);
}

