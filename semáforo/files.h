#ifndef FILES_H
#define FILES_H

#include "linked.h"
#include "play.h"

bool export_states_txt(struct list_head *states);
bool export_states_bin(struct list_head states, struct player a, struct player b, int lin, int col);
#endif