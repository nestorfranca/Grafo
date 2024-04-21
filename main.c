#include <stdio.h>
#include <stdlib.h>
#include "./geral/geral.c"


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


int main(void) {

    /* ===== GERA MATRIZ ===== */
    int i, **matriz = NULL, tamanho;
    matriz = le_matriz("dados_matriz.txt", matriz, &tamanho);
    // printf("%d", verifica_simetria(matriz, tamanho)); delay(3000);
    // mostra_matriz(matriz, tamanho);
    
    /* ===== ANÁLISE DO GRAFO ===== */
    if (tamanho > 0) {
        int var;
        do {
            var = menu_principal(matriz, tamanho);
        } while (var != '6');
    }

    for (i = 0; i < tamanho; i++) {
        free(matriz[i]);
    }
    free(matriz);
    
    return 0;
}
