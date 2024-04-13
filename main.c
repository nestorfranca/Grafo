#include <stdio.h>
#include <stdlib.h>
#include "grafo.c"

int main()
{
    /* ===== GERA MATRIZ ===== */
    int **matriz, tamanho;
    matriz = importa_matriz("dados_matriz_teste.txt", matriz, &tamanho);
    // mostra_matriz(matriz, tamanho);
    
    /* ===== VERTICES ISOLADOS ===== */
    int *isolados = (int*)malloc(tamanho*sizeof(int));
    if (isolados == NULL) exit(1);

    int num_isolados;
    isolados = vertices_isolados(matriz, isolados, tamanho, &num_isolados);
    
    if (isolados != NULL) {
        printf("Vertices isolados (sem arestas conectadas a outros vertices):\n");
        for (int i = 0; i < num_isolados; i++) {
            printf("%d ", isolados[i]);
        }
        printf("\n");

    } else {
        printf("Nao ha vertices isolados!\n");
    }

    /* ===== VERIFICA CAMINHO ENTRE VERTICES ===== */
    int *caminho = (int*)malloc(tamanho*sizeof(int));
    if (caminho == NULL) exit(1);

    caminho = conexao_vertices(matriz, caminho, 0, tamanho-1);

    if (caminho != NULL) {
        printf("Caminho entres os vertices %d e %d:\n", 0, tamanho-1);
        printf("%d ", caminho[0]);
        int i;
        for (i = 1; caminho[i] != 0; i++) {
            printf("-> %d ", caminho[i]);
        }
        printf("\n");

    } else
        printf("Nao ha conexao entre o primeiro e o ultimo vertice!\n");

    return 0;
}