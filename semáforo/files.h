#ifndef FILES_H
#define FILES_H


bool export_states_txt(struct list_head *states);
bool export_bin(struct list_head states, struct player a, struct player b, int lin, int col, bool game_mode);

#endif