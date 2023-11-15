#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int i, j;
    double valor;
    struct No* prox;
} No;

typedef struct {
    int l, c;
    No* cabeca;
} Matriz;

Matriz leMatriz(char* arquivo);
void imprimeMatriz(Matriz A);
Matriz somaMatrizes(Matriz A, Matriz B);
void liberaMatriz(Matriz* matriz);
void imprimeSomaMatrizes(Matriz A, Matriz B);


