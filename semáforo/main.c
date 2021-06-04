#include <stdio.h>
#include "utils.h"
#include "game.h"



int main(){
    initRandom();
    char op='N', save;
    bool game_mode;
    FILE *fp, *text_fp;
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
    if(op=='N') //novo jogo
        do{
            op=menu();
            if(op=='1')
                game(TWO_PLAYER_GAME,NEW_GAME); //dois jogadores sem continuacao
            if(op=='2')
                game(BOT_GAME,NEW_GAME); //computador sem resumir
            if(op=='3')
                rules();
        }while(op=='3');
    printf("\n\nObrigado por jogar o jogo do semaforo!!!\n\n");
    return 0;
}

