#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdio.h>  // Adiciona a inclusão da biblioteca stdio.h

typedef struct Celula {
    struct Celula *direita, *abaixo;
    int linha, coluna;
    float valor;
} Celula;

typedef struct {
    Celula *cabeca;
    int nlin, ncol;
} Matriz;

void imprimeMatriz(Matriz A);
Matriz leMatriz(FILE *arquivo);
Matriz somaMatrizes(Matriz A, Matriz B);
Matriz multiplicaMatrizes(Matriz A, Matriz B);
void insere(Matriz *matriz, int i, int j, float v);
void liberaMatriz(Matriz *matriz);

#endif
