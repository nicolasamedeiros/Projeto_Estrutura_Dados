#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

Matriz leMatriz(char* arquivo) {
    Matriz A;
    FILE* file = fopen(arquivo, "r");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        
    }

    fscanf(file, "%d %d", &A.l, &A.c);
    A.cabeca = NULL;

    int i, j;
    double valor;
    while (fscanf(file, "%d %d %lf", &i, &j, &valor) == 3) {
        No* novo = (No*)malloc(sizeof(No));
        novo->i = i;
        novo->j = j;
        novo->valor = valor;
        novo->prox = A.cabeca;
        A.cabeca = novo;
    }

    fclose(file);
    return A;
}

void imprimeMatriz(Matriz A) {
    for (int i = 0; i < A.l; i++) {
        for (int j = 0; j < A.c; j++) {
            No* atual = A.cabeca;
            while (atual != NULL) {
                if (atual->i == i && atual->j == j) {
                    printf("%.2f\t", atual->valor);
                    break;
                }
                atual = atual->prox;
            }
            if (atual == NULL) {
                printf("0.00\t");
            }
        }
        printf("\n");
    }
}

Matriz somaMatrizes(Matriz A, Matriz B) {
    Matriz C;
    C.l = A.l;
    C.c = A.c;
    C.cabeca = NULL;

    for (int i = 0; i < C.l; i++) {
        for (int j = 0; j < C.c; j++) {
            No* atualA = A.cabeca;
            No* atualB = B.cabeca;
            double soma = 0.0;

            while (atualA != NULL) {
                if (atualA->i == i && atualA->j == j) {
                    soma += atualA->valor;
                    break;
                }
                atualA = atualA->prox;
            }

            while (atualB != NULL) {
                if (atualB->i == i && atualB->j == j) {
                    soma += atualB->valor;
                    break;
                }
                atualB = atualB->prox;
            }

            if (soma != 0.0) {
                No* novo = (No*)malloc(sizeof(No));
                novo->i = i;
                novo->j = j;
                novo->valor = soma;
                novo->prox = C.cabeca;
                C.cabeca = novo;
            }
        }
    }

    return C;
}

void liberaMatriz(Matriz* matriz) {
    No* atual = matriz->cabeca;
    No* proximo;

    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    matriz->cabeca = NULL;
}

void imprimeSomaMatrizes(Matriz A, Matriz B) {
    Matriz C = somaMatrizes(A, B);

    printf("\nSoma das matrizes A e B:\n");
    imprimeMatriz(C);
    liberaMatriz(&C);
}
