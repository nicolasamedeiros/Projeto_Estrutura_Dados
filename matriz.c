#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>

Celula *criaCelula(int linha, int coluna, float valor) {
    Celula *novaCelula = (Celula *)malloc(sizeof(Celula));
    if (novaCelula == NULL) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        exit(EXIT_FAILURE);
    }

    novaCelula->direita = novaCelula;
    novaCelula->abaixo = novaCelula;
    novaCelula->linha = linha;
    novaCelula->coluna = coluna;
    novaCelula->valor = valor;

    return novaCelula;
}

void insereCelula(Matriz *matriz, Celula *celula) {
    Celula *atual = matriz->cabeca;
    while (atual->abaixo != matriz->cabeca && atual->abaixo->linha < celula->linha) {
        atual = atual->abaixo;
    }

    while (atual->direita != matriz->cabeca && atual->direita->coluna < celula->coluna) {
        atual = atual->direita;
    }

    celula->abaixo = atual->abaixo;
    atual->abaixo = celula;

    celula->direita = atual->direita;
    atual->direita = celula;
}

void imprimeCelula(Celula *celula) {
    printf("(%d, %d): %.2f\t", celula->linha, celula->coluna, celula->valor);
}

void imprimeMatriz(Matriz A) {
    for (int i = 1; i <= A.nlin; i++) {
        for (int j = 1; j <= A.ncol; j++) {
            Celula *atual = A.cabeca->direita;
            int encontrou = 0;

            while (atual != A.cabeca) {
                if (atual->linha == i && atual->coluna == j) {
                    imprimeCelula(atual);
                    encontrou = 1;
                    break;
                }
                atual = atual->direita;
            }

            if (!encontrou) {
                printf("(0, 0): 0.00\t");
            } else {
                encontrou = 0;
            }
        }
        printf("\n");
    }
}

Matriz leMatriz(FILE *arquivo) {
    Matriz matriz;
    int m, n;
    fscanf(arquivo, "%d, %d", &m, &n);

    matriz.nlin = m;
    matriz.ncol = n;
    matriz.cabeca = criaCelula(-1, -1, 0.0);

    int i, j;
    float valor;
    while (fscanf(arquivo, "%d, %d, %f", &i, &j, &valor) == 3) {
        insereCelula(&matriz, criaCelula(i, j, valor));
    }

    return matriz;
}

Matriz somaMatrizes(Matriz A, Matriz B) {
    if (A.nlin != B.nlin || A.ncol != B.ncol) {
        fprintf(stderr, "Erro: As matrizes têm dimensões diferentes.\n");
        exit(EXIT_FAILURE);
    }

    Matriz C;
    C.nlin = A.nlin;
    C.ncol = A.ncol;
    C.cabeca = criaCelula(-1, -1, 0.0);

    for (int i = 1; i <= A.nlin; i++) {
        for (int j = 1; j <= A.ncol; j++) {
            float soma = 0.0;

            Celula *celulaA = A.cabeca->direita;
            Celula *celulaB = B.cabeca->direita;

            while (celulaA != A.cabeca || celulaB != B.cabeca) {
                if (celulaA->linha == i && celulaA->coluna == j) {
                    soma += celulaA->valor;
                    celulaA = celulaA->direita;
                } else if (celulaB->linha == i && celulaB->coluna == j) {
                    soma += celulaB->valor;
                    celulaB = celulaB->direita;
                } else {
                    if (celulaA->linha == i) {
                        celulaA = celulaA->direita;
                    }
                    if (celulaB->linha == i) {
                        celulaB = celulaB->direita;
                    }
                }
            }

            if (soma != 0.0) {
                insereCelula(&C, criaCelula(i, j, soma));
            }
        }
    }

    return C;
}


Matriz multiplicaMatrizes(Matriz A, Matriz B) {
    if (A.ncol != B.nlin) {
        fprintf(stderr, "Erro: Número de colunas de A não é igual ao número de linhas de B.\n");
        exit(EXIT_FAILURE);
    }

    Matriz C;
    C.nlin = A.nlin;
    C.ncol = B.ncol;
    C.cabeca = criaCelula(-1, -1, 0.0);

    for (int i = 1; i <= A.nlin; i++) {
        for (int j = 1; j <= B.ncol; j++) {
            float produto = 0.0;

            for (int k = 1; k <= A.ncol; k++) {
                Celula *celulaA = A.cabeca->direita;
                Celula *celulaB = B.cabeca->direita;

                while (celulaA != A.cabeca && celulaA->coluna <= k) {
                    if (celulaA->linha == i) {
                        while (celulaB != B.cabeca && celulaB->linha <= k) {
                            if (celulaB->coluna == j) {
                                produto += celulaA->valor * celulaB->valor;
                            }
                            celulaB = celulaB->abaixo;
                        }
                    }
                    celulaA = celulaA->direita;
                }
            }

            if (produto != 0.0) {
                insereCelula(&C, criaCelula(i, j, produto));
            }
        }
    }

    return C;
}

void insere(Matriz *matriz, int i, int j, float v) {
    insereCelula(matriz, criaCelula(i, j, v));
}

void liberaMatriz(Matriz *matriz) {
    Celula *atual = matriz->cabeca->abaixo;

    while (atual != matriz->cabeca) {
        Celula *proximaLinha = atual->abaixo;
        Celula *celulaAtual = atual->direita;

        while (celulaAtual != atual) {
            Celula *proximaCelula = celulaAtual->direita;
            free(celulaAtual);
            celulaAtual = proximaCelula;
        }

        free(atual);
        atual = proximaLinha;
    }

    free(matriz->cabeca);
    matriz->cabeca = NULL;
}
