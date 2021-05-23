#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "utils.h"
#include "game.h"

//game_mode==0--> P1 vs P2
//game_mode==1--> P1 vs PC

//resume==1-->continuar jogo
//resume==0-->comecar novo jogo


int main(){
char op='N';
bool game_mode;
FILE *fp;
if( ( fp=fopen("jogo.bin","rb") )!=NULL ){
  printf("Encontramos um jogo ainda nao acabado, deseja retomar esse jogo?\n"
  "S (sim) ou N(nao)");
  do{
    printf("Opcao: ");
    scanf(" %c",&op);
    if(op!='S' && op!='N'){
      printf("Por favor digite ou S(sim) ou N(nao)\n");
      clean_stdin();
      }
    }while(op!='S' && op!='N');

  if(op=='S'){
    fread(&game_mode,sizeof(bool),1,fp);
    fclose(fp);
    if(game_mode==1) //contra computador
      game(game_mode,1); //contra computador e resumir
    else
      game(game_mode,1); //dois jogadores, sem resumir
    }
  else{ //oopcao==N
    fclose(fp);
    remove("jogo.bin");
    }
  }
if(op=='N'){ //se nao ha ficheiro ou nao quer continuar o jogo
  op=menu();
  if(op=='1')
    game(0,0); //dois jogadores sem continuacao
  else
    game(1,0); //computador sem resumir
  }
printf("\n\nObirgado por jogar o jogo do semaforo!!!\n\n");
return 0;
}

