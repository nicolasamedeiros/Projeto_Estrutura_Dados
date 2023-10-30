#ifndef MATRIZ_H
#define MATRIZ_H

typedef struct Celula {
    struct Celula *direita;
    struct Celula *abaixo;
    int linha;
    int coluna;
    float valor;
} Celula;

typedef struct {
    Celula *cabeca;
    int nlin;
    int ncol;
} Matriz;

Matriz inicializaMatriz(int nlin, int ncol);
void insere(Matriz *matriz, int linha, int coluna, float valor);
Matriz leMatriz(FILE *arquivo);
void imprimeMatriz(Matriz matriz);
Matriz somaMatrizes(Matriz A, Matriz B);
Matriz multiplicaMatrizes(Matriz A, Matriz B);

#endif