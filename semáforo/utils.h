#ifndef UTILS_H
#define UTILS_H

struct jogadas{
  int verde;
  int amarelo;
  int vermelho;
  int pedra;
  int lc;
};

struct jogador{
  char nome;
  struct jogadas habilidade;
};

// Inicializa o gerador de numeros aleatorios.
// Esta funcao deve ser chamada apenas uma vez no inicio da execucao do programa
void initRandom();

//Devolve um valor inteiro aleatorio distribuido uniformemente entre [a, b]
int intUniformRnd(int a, int b);

// Devolve o valor 1 com probabilidade prob. Caso contrario, devolve 0
int probEvento(float prob);


#endif /* UTILS_H */