// main.c
#include "matriz.h"

int main(void) {
    Matriz A, B, C;
    FILE *arquivoA = fopen("matrizA.txt", "r");
    FILE *arquivoB = fopen("matrizB.txt", "r");

    if (arquivoA == NULL || arquivoB == NULL) {
        fprintf(stderr, "Erro ao abrir os arquivos de entrada.\n");
        return 1;
    }

    A = leMatriz(arquivoA);
    fclose(arquivoA);

    printf("Matriz A:\n");
    imprimeMatriz(A);

    B = leMatriz(arquivoB);
    fclose(arquivoB);

    printf("\nMatriz B:\n");
    imprimeMatriz(B);

    C = somaMatrizes(A, B);

    printf("\nMatriz Resultante (Soma de A e B):\n");
    imprimeMatriz(C);

    // Outros testes devem ser considerados aqui...

    liberarMatriz(&A);
    liberarMatriz(&B);
    liberarMatriz(&C);

    return 0;
}
