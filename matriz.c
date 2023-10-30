#include "matriz.h"
#include <stdlib.h>
#include <stdio.h>

Matriz inicializaMatriz(int nlin, int ncol) {
    Matriz matriz;
    matriz.nlin = nlin;
    matriz.ncol = ncol;
    
    matriz.cabeca = (Celula *)malloc(sizeof(Celula));
    matriz.cabeca->linha = -1;
    matriz.cabeca->coluna = -1;
    matriz.cabeca->direita = matriz.cabeca;
    matriz.cabeca->abaixo = matriz.cabeca;
    matriz.cabeca->valor = 0.0;

    return matriz;
}

void insere(Matriz *matriz, int linha, int coluna, float valor) {
    Celula *novaCelula = (Celula *)malloc(sizeof(Celula));
    novaCelula->linha = linha;
    novaCelula->coluna = coluna;
    novaCelula->valor = valor;
    
    // Inserção na lista da linha
    Celula *linhaAtual = matriz->cabeca;
    while (linhaAtual->linha != linha) {
        linhaAtual = linhaAtual->abaixo;
    }
    novaCelula->direita = linhaAtual->direita;
    linhaAtual->direita = novaCelula;

    // Inserção na lista da coluna
    Celula *colunaAtual = matriz->cabeca;
    while (colunaAtual->coluna != coluna) {
        colunaAtual = colunaAtual->direita;
    }
    novaCelula->abaixo = colunaAtual->abaixo;
    colunaAtual->abaixo = novaCelula;
}

Matriz leMatriz(FILE *arquivo) {
    int m, n;
    fscanf(arquivo, "%d %d", &m, &n);
    Matriz matriz = inicializaMatriz(m, n);

    int linha, coluna;
    float valor;

    while (fscanf(arquivo, "%d %d %f", &linha, &coluna, &valor) == 3) {
        insere(&matriz, linha, coluna, valor);
    }

    return matriz;
}

void imprimeMatriz(Matriz matriz) {
    // Implemente a lógica de impressão da matriz, incluindo as células com valores diferentes de zero
}

Matriz somaMatrizes(Matriz A, Matriz B) {
    // Implemente a lógica de soma de matrizes, considerando que A e B têm as mesmas dimensões
}

Matriz multiplicaMatrizes(Matriz A, Matriz B) {
    // Implemente a lógica de multiplicação de matrizes, considerando as regras para multiplicação
}
