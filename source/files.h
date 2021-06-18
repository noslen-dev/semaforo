/*
 * Nome: Nelson Forte Simao
 * Numero: 2020132648 
 */

#ifndef FILES_H
#define FILES_H


bool export_states_txt(struct list_head *states, bool game_mode);
bool export_bin(struct list_head states, struct player a, struct player b, bool game_mode);

#endif //FILES_H