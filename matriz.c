// matriz.c
#include "matriz.h"
#include <stdlib.h>


void imprimeMatriz(Matriz matriz) {
    for (int i = 1; i <= matriz.nlin; i++) {
        for (int j = 1; j <= matriz.ncol; j++) {
            float valor = obtemValor(&matriz, i, j);
            printf("%.2f\t", valor);
        }
        printf("\n");
    }
    }

float obtemValor(Matriz *matriz, int linha, int coluna) {
    Celula *atual = matriz->cabeca->direita;

    while (atual != NULL) {
        if (atual->linha == linha && atual->coluna == coluna) {
            return atual->valor;
        }
        atual = atual->direita;
    }

    return 0.0;  // Valor padrão se a célula não for encontrada
}


Matriz leMatriz(FILE *arquivo) {
    Matriz matriz;
    int nlin, ncol;
    fscanf(arquivo, "%d, %d", &nlin, &ncol);

    matriz = inicializaMatriz(nlin, ncol);

    int linha, coluna;
    float valor;
    while (fscanf(arquivo, "%d, %d, %f", &linha, &coluna, &valor) == 3) {
        insere(&matriz, linha, coluna, valor);
    }

    return matriz;
}
Matriz inicializaMatriz(int nlin, int ncol) {
    Matriz matriz;
    matriz.nlin = nlin;
    matriz.ncol = ncol;

    matriz.cabeca = (Celula *)malloc(sizeof(Celula));
    matriz.cabeca->linha = -1;
    matriz.cabeca->coluna = -1;
    matriz.cabeca->valor = 0;
    matriz.cabeca->direita = matriz.cabeca;
    matriz.cabeca->abaixo = matriz.cabeca;

    for (int i = 0; i < nlin; i++) {
        Celula *novaLinha = (Celula *)malloc(sizeof(Celula));
        novaLinha->linha = i;
        novaLinha->coluna = -1;
        novaLinha->valor = 0;
        novaLinha->direita = novaLinha;
        novaLinha->abaixo = novaLinha;

        novaLinha->direita = matriz.cabeca->direita;
        matriz.cabeca->direita = novaLinha;

        for (int j = 0; j < ncol; j++) {
            Celula *novaColuna = (Celula *)malloc(sizeof(Celula));
            novaColuna->linha = -1;
            novaColuna->coluna = j;
            novaColuna->valor = 0;
            novaColuna->direita = novaColuna;
            novaColuna->abaixo = novaColuna;

            novaColuna->abaixo = matriz.cabeca->abaixo;
            matriz.cabeca->abaixo = novaColuna;
        }
    }

    return matriz;
}

 void insere(Matriz *matriz, int linha, int coluna, float valor) {
    Celula *novaCelula = (Celula *)malloc(sizeof(Celula));
    if (novaCelula == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a célula.\n");
        exit(EXIT_FAILURE);
    }

    novaCelula->linha = linha;
    novaCelula->coluna = coluna;
    novaCelula->valor = valor;

   
    novaCelula->direita = matriz->cabeca->direita;
    matriz->cabeca->direita = novaCelula;

  
    Celula *atual = matriz->cabeca;
    while (atual->abaixo != NULL) {
        atual = atual->abaixo;
    }
    novaCelula->abaixo = atual->abaixo;
    atual->abaixo = novaCelula;
}

Matriz somaMatrizes(Matriz A, Matriz B) {
    

    Matriz C;
    C.nlin = A.nlin;
    C.ncol = A.ncol;

   
    C.cabeca = (Celula *)malloc(sizeof(Celula));
    if (C.cabeca == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a célula cabeça de C.\n");
        exit(EXIT_FAILURE);
    }
    C.cabeca->linha = -1;
    C.cabeca->coluna = -1;
    C.cabeca->direita = NULL;
    C.cabeca->abaixo = NULL;

    for (int i = 1; i <= C.nlin; i++) {
        for (int j = 1; j <= C.ncol; j++) {
           
            insere(&C, i, j, 0.0);
        }
    }

    for (int i = 1; i <= A.nlin; i++) {
        for (int j = 1; j <= A.ncol; j++) {
            float valorA = obtemValor(&A, i, j);
            float valorB = obtemValor(&B, i, j);
            insere(&C, i, j, valorA + valorB);
        }
    }

    return C;
}

Matriz multiplicaMatrizes(Matriz A, Matriz B) {
    

    Matriz C;
    C.nlin = A.nlin;
    C.ncol = B.ncol;

    
    C.cabeca = (Celula *)malloc(sizeof(Celula));
    if (C.cabeca == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a célula cabeça de C.\n");
        exit(EXIT_FAILURE);
    }
    C.cabeca->linha = -1;
    C.cabeca->coluna = -1;
    C.cabeca->direita = NULL;
    C.cabeca->abaixo = NULL;

    for (int i = 1; i <= C.nlin; i++) {
        for (int j = 1; j <= C.ncol; j++) {
            
            insere(&C, i, j, 0.0);
        }
    }

    
    for (int i = 1; i <= A.nlin; i++) {
        for (int j = 1; j <= B.ncol; j++) {
            float soma = 0.0;
            for (int k = 1; k <= A.ncol; k++) {
                soma += obtemValor(&A, i, k) * obtemValor(&B, k, j);
            }
            insere(&C, i, j, soma);
        }
    }

    return C;
}

void liberarMatriz(Matriz *matriz) {
    
    Celula *atual, *proximo;

    for (int i = 1; i <= matriz->nlin; i++) {
        atual = matriz->cabeca->direita;
        while (atual != NULL) {
            proximo = atual->direita;
            free(atual);
            atual = proximo;
        }

        proximo = matriz->cabeca->abaixo;
        free(matriz->cabeca);
        matriz->cabeca = proximo;
    }
    

    
}