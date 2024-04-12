#include <stdio.h>
#include <stdlib.h>
#include "grafo.c"

int main()
{
    int **matriz, tamanho;
    matriz = importa_matriz("dados_matriz_teste.txt", matriz, &tamanho);
    // mostra_matriz(matriz, tamanho);
    
    int *caminho = (int*)calloc(100, sizeof(int));
    caminho = conexao_vertices(matriz, caminho, 0, tamanho-1);

    if (caminho == NULL)
        printf("Nao ha conexao entre o primeiro e o ultimo vertice!\n");
    
    else {
        printf("%d ", caminho[0]);
        int i;
        for (i = 1; caminho[i] != 0; i++) {
            printf("-> %d ", caminho[i]);
        }
        printf("\n");
    }
    
    vertices_isolados(matriz, tamanho);
    
    return 0;
}