#include "matriz.h"
#include <stdio.h>

int main(void) {
    Matriz A, B, C;
    FILE *arquivoA, *arquivoB;

    // Abra os arquivos de entrada
    arquivoA = fopen("matrizA.txt", "r");
    arquivoB = fopen("matrizB.txt", "r");

    if (arquivoA == NULL || arquivoB == NULL) {
        fprintf(stderr, "Erro ao abrir os arquivos de entrada.\n");
        return 1;
    }

    // Leia as matrizes a partir dos arquivos
    A = leMatriz(arquivoA);
    B = leMatriz(arquivoB);

    // Imprima as matrizes lidas
    printf("Matriz A:\n");
    imprimeMatriz(A);

    printf("\nMatriz B:\n");
    imprimeMatriz(B);

    // Calcule a soma das matrizes e imprima o resultado
    C = somaMatrizes(A, B);
    printf("\nSoma das matrizes A e B:\n");
    imprimeMatriz(C);

    // Outros testes devem ser considerados aqui...

    // Feche os arquivos e libere a memória alocada para as matrizes
    fclose(arquivoA);
    fclose(arquivoB);
    liberaMatriz(&A);
    liberaMatriz(&B);
    liberaMatriz(&C);

    return 0;
}
