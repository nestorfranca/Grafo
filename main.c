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

    return 0;
}