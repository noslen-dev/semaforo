/*
 * Nome: Nelson Forte Simao
 * Numero: 2020132648 
 */

#ifndef UTILS_H
#define UTILS_H


// Inicializa o gerador de numeros aleatorios.
// Esta funcao deve ser chamada apenas uma vez no inicio da execucao do programa
void initRandom();

//Devolve um valor inteiro aleatorio distribuido uniformemente entre [a, b]
int intUniformRnd(int a, int b);

// Le carateres em stdin ate ate encontrar um '\n'
void clean_stdin();


#endif //UTILS_H