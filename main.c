#include <stdio.h>
#include <stdlib.h>
#include "./geral/geral.c"

int main()
{
    /* ===== GERA MATRIZ ===== */
    int **matriz, tamanho;
    matriz = importa_matriz("dados_matriz_teste.txt", matriz, &tamanho);
    // mostra_matriz(matriz, tamanho);
    
    /* ===== ANÁLISE DO GRAFO ===== */
    int var;
    do {
        var = menu_principal(matriz, tamanho);
    } while (var != '6');

   


    int **subgrafo = subgrafo_induzido(matriz, tamanho, "dados_grafo_gerador.txt");
if (subgrafo == NULL) {
    fprintf(stderr, "Erro ao criar o subgrafo induzido.\n");
    liberar_matriz(matriz, tamanho);
    return 1;
}
liberar_matriz(matriz, tamanho);

   
    return 0;
}

