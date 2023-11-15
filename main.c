#include <stdio.h>
#include "matriz.h"

int main() {
    Matriz A = leMatriz("matrizA.txt");
    Matriz B = leMatriz("matrizB.txt");

    printf("Matriz A:\n");
    imprimeMatriz(A);

    printf("\nMatriz B:\n");
    imprimeMatriz(B);

    imprimeSomaMatrizes(A, B);

    liberaMatriz(&A);
    liberaMatriz(&B);

    return 0;
}
