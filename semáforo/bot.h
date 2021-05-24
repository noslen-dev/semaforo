#ifndef BOT_H
#define BOT_H

#include "play.h"

bool bot_plays(char ***tab, int *lin, int *col, char *piece, struct coordinates *place, struct player *bot);
void show_bot_play(struct player bot, char piece, struct coordinates place);

#endif