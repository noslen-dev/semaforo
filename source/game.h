/*
 * Nome: Nelson Forte Simao
 * Numero: 2020132648 
 */

#ifndef GAME_H
#define GAME_H

#define TWO_PLAYER_GAME 0
#define BOT_GAME 1
#define RESUME_GAME 1
#define NEW_GAME 0


char menu();
void game(bool game_mode, bool resume);
void rules();

#endif //GAME_H