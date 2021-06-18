/*
 * Nome: Nelson Forte Simao
 * Numero: 2020132648 
 */

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "utils.h"

void initRandom(){
    srand(time(NULL));
}

int intUniformRnd(int a, int b){
    return a + rand()%(b-a+1);
}


void clean_stdin(){
char ch;
  while( (ch=getchar() )!='\n' && ch!=EOF); //EOF so para ser seguro
}

