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
    for (int i = 0; i < matriz.nlin; i++) {
        for (int j = 0; j < matriz.ncol; j++) {
            Celula *atual = matriz.cabeca->direita;
            int valor = 0;

            while (atual != matriz.cabeca) {
                if (atual->linha == i && atual->coluna == j) {
                    valor = atual->valor;
                    break;
                }
                atual = atual->direita;
            }
            
            printf("%d ", valor);
        }
        printf("\n");
    }
}


Matriz somaMatrizes(Matriz A, Matriz B) {
    if (A.nlin != B.nlin || A.ncol != B.ncol) {
        printf("As matrizes têm dimensões diferentes, não podem ser somadas.\n");
        exit(1);
    }

    Matriz resultado = inicializaMatriz(A.nlin, A.ncol);

    for (int i = 0; i < A.nlin; i++) {
        for (int j = 0; j < A.ncol; j++) {
            Celula *atualA = A.cabeca->direita;
            Celula *atualB = B.cabeca->direita;
            float valorA = 0.0;
            float valorB = 0.0;

            while (atualA != A.cabeca) {
                if (atualA->linha == i && atualA->coluna == j) {
                    valorA = atualA->valor;
                    break;
                }
                atualA = atualA->direita;
            }

            while (atualB != B.cabeca) {
                if (atualB->linha == i && atualB->coluna == j) {
                    valorB = atualB->valor;
                    break;
                }
                atualB = atualB->direita;
            }

            insere(&resultado, i, j, valorA + valorB);
        }
    }

    return resultado;
}


Matriz multiplicaMatrizes(Matriz A, Matriz B) {
    if (A.ncol != B.nlin) {
        printf("As matrizes não podem ser multiplicadas devido a dimensões inadequadas.\n");
        exit(1);
    }

    Matriz resultado = inicializaMatriz(A.nlin, B.ncol);

    for (int i = 0; i < A.nlin; i++) {
        for (int j = 0; j < B.ncol; j++) {
            float valor = 0.0;
            for (int k = 0; k < A.ncol; k++) {
                Celula *atualA = A.cabeca->direita;
                Celula *atualB = B.cabeca->abaixo;

                float valorA = 0.0;
                float valorB = 0.0;

                while (atualA != A.cabeca) {
                    if (atualA->linha == i && atualA->coluna == k) {
                        valorA = atualA->valor;
                        break;
                    }
                    atualA = atualA->direita;
                }

                while (atualB != B.cabeca) {
                    if (atualB->linha == k && atualB->coluna == j) {
                        valorB = atualB->valor;
                        break;
                    }
                    atualB = atualB->abaixo;
                }

                valor += valorA * valorB;
            }

            insere(&resultado, i, j, valor);
        }
    }

    return resultado;
}

