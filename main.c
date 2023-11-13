#include "matriz.h"
#include <stdio.h>

int main(void) {
    Matriz A, B, C;
    FILE *arquivoA, *arquivoB;

    
    arquivoA = fopen("matrizA.txt", "r");
    arquivoB = fopen("matrizB.txt", "r");

    if (arquivoA == NULL || arquivoB == NULL) {
        fprintf(stderr, "Erro ao abrir os arquivos de entrada.\n");
        return 1;
    }

    
    A = leMatriz(arquivoA);
    B = leMatriz(arquivoB);

    
    printf("Matriz A:\n");
    imprimeMatriz(A);

    printf("\nMatriz B:\n");
    imprimeMatriz(B);

    
    C = somaMatrizes(A, B);
    printf("\nSoma das matrizes A e B:\n");
    imprimeMatriz(C);

    
    fclose(arquivoA);
    fclose(arquivoB);
    liberaMatriz(&A);
    liberaMatriz(&B);
    liberaMatriz(&C);

    return 0;
}
