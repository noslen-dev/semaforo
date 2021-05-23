#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "play.h"

char menu();
void init_jogo();
void game_2p();
void direct_new_game();
void game(bool game_mode, bool resume);
char menu();

#endif