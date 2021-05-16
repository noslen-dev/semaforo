#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "utils.h"
#include "play.h"

void initRandom(){
    srand(time(NULL));
}

int intUniformRnd(int a, int b){
    return a + rand()%(b-a+1);
}

int probEvento(float prob){
    return prob > ((float)rand()/RAND_MAX);
}

void clean_stdin(){
char ch;
  while( (ch=getchar() )!='\n' && ch!=EOF); //EOF so para ser seguro
}

void print_a(struct player a){
  printf("\n%d %d %d %d %d\n",a.ability.green,a.ability.yellow,a.ability.red,
  a.ability.rock,a.ability.lc);
}
