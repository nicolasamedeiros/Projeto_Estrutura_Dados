#include <stdio.h>
#include "matriz.h"

int main() {
    Matriz A, B, C;
    A = leMatriz(stdin);  // Ler a matriz A a partir do arquivo de entrada (stdin neste caso)
    B = leMatriz(stdin);  // Ler a matriz B a partir do arquivo de entrada
    C = somaMatrizes(A, B);  // Somar as matrizes A e B
    imprimeMatriz(C);  // Imprimir a matriz resultante C

    // Implemente outros testes e operações aqui

    return 0;
}
