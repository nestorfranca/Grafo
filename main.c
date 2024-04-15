#include <stdio.h>
#include <stdlib.h>
#include "./geral/geral.c"


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


int main(void) {

    /* ===== GERA MATRIZ ===== */
    int i, **matriz, tamanho;
    matriz = importa_matriz("dados_matriz_teste.txt", matriz, &tamanho);
    // mostra_matriz(matriz, tamanho);
    
    /* ===== ANÁLISE DO GRAFO ===== */
    int var;
    do {
        var = menu_principal(matriz, tamanho);
    } while (var != '6');

    for (i = 0; i < tamanho; i++) {
        free(matriz[i]);
    }
    free(matriz);
    
    return 0;
}
