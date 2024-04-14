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

    } else{
        printf("Nao ha conexao entre o primeiro e o ultimo vertice!\n");
    }

    puts("Grau dos vertices");
// indentifica o grau de cada vertice
    int *grau = grau_vertices(matriz, tamanho);
    
    for(int i = 0; i < tamanho; i++){
        printf("%d ", grau[i]);
    }

    puts("\nvertices com maiores graus");

// indentifica qual os vertices tem o maior grau
    int quantidade_vertices;
    int *maiores_vertices = maior_vertice(grau, tamanho, &quantidade_vertices);
    for(int i = 0; i < quantidade_vertices; i++){
        printf("%d ", maiores_vertices[i]);
    }

    grau_arquivo(grau, tamanho);

    return 0;
}