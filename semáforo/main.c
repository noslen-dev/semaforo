#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "utils.h"
#include "game.h"




int main(){
char op;
op=menu();
if(op=='1')
  game(1,1);


return 0;
}