#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "utils.h"
#include "game.h"




int main(){
FILE *fp;
char op;
if( ( fp=fopen("jogo.bin","rb") )!=NULL ){
  printf("Foi encontrado um jogo nao acabado! Deseja retomar o jogo? s(sim) ou n(nao) "
  "ou q(sair)\n");
  do{
    printf("Opcao: ");
    scanf(" %c",&op);
    if(op!='s' && op!='n'){
      printf("Por favor digite ou 's' ou 'n'\n");
      clean_stdin();
    }
  }while(op!='s' && op!='n');
  if(op=='s'){
    //chamar funcao de abertura binaria que me devolva o tipo de jogo
    //chamar 2p_play ou bot_play com o nome do ficheiro
    return 0; //terminar
  }
  else{ //nao quer continuar
    fclose(fp);
    remove("jogo.bin");
  }
}
//o ficheiro nao pode ser aberto ou pressionou nao==jogo novo
op=menu();
if(op=='1')
  game_2p(NULL); //iniciar jogo de dois jogadores

else ;
  //bot_play(NULL);
  


return 0;
}