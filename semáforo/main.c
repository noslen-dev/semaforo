#include <stdio.h>
#include <unistd.h>
#include "utils.h"
#include "game.h"



int main(){
initRandom();
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
    if(game_mode==BOT_GAME) //contra computador
      game(game_mode,RESUME_GAME); //contra computador e resumir
    else
      game(game_mode,RESUME_GAME); //dois jogadores, continuar
    }
  else{ //oopcao==N
    fclose(fp);
    remove("jogo.bin");
    }
  }
if(op=='N'){ //se nao ha ficheiro ou nao quer continuar o jogo
  op=menu();
  if(op=='1')
    game(TWO_PLAYER_GAME,NEW_GAME); //dois jogadores sem continuacao
  else
    game(BOT_GAME,NEW_GAME); //computador sem resumir
  }
printf("\n\nObrigado por jogar o jogo do semaforo!!!\n\n");
return 0;
}

