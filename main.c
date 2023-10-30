#include "matriz.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    Matriz A, B, C;
    A = leMatriz(stdin);  // Ler a matriz A a partir da entrada padrão (stdin neste caso)
    B = leMatriz(stdin);  // Ler a matriz B a partir da entrada padrão

    // Verificar se as matrizes têm as mesmas dimensões antes de somar
    if (A.nlin != B.nlin || A.ncol != B.ncol) {
        printf("As matrizes têm dimensões diferentes, não podem ser somadas.\n");
        exit(1);
    }

    C = somaMatrizes(A, B);  // Somar as matrizes A e B
    printf("Matriz A:\n");
    imprimeMatriz(A);  // Imprimir a matriz A
    printf("Matriz B:\n");
    imprimeMatriz(B);  // Imprimir a matriz B
    printf("Matriz resultante C (A + B):\n");
    imprimeMatriz(C);  // Imprimir a matriz resultante C

    // Implemente outros testes e operações aqui, se desejar

    // Lembre-se de liberar a memória alocada para as matrizes A, B e C, se necessário
    // Libere a memória das células em cada matriz e, em seguida, libere a matriz.
    // Exemplo de liberação de memória:
    liberarMatriz(&A);
    liberarMatriz(&B);
    liberarMatriz(&C);

    return 0;
}
