#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "grafo.h"

void delay(double milissegundos)
{
    // Armazenando tempo inicial:
    clock_t tempo_inicial = clock();
    
    // looping till required time is not achieved
    while (milissegundos > clock() - tempo_inicial);
}

int **importa_matriz(char *nome_arquivo, int **matriz, int *tamanho)
{
    FILE *arquivo;
    char *linha, *token;
    int tamanho_matriz, tamanho_linha;
    int i, j;

    arquivo = fopen(nome_arquivo, "rt");
    
    fscanf(arquivo, "%d", &tamanho_matriz); /* lê o tamanho da matriz */
    tamanho_linha = 2*tamanho_matriz+2; /* tamanho da linha */

    matriz = (int**)malloc(tamanho_matriz*sizeof(int*));
    if (matriz == NULL) exit(1);
    for (i = 0; i < tamanho_matriz; i++) {
        matriz[i] = (int*)malloc(tamanho_matriz*sizeof(int));
        if (matriz[i] == NULL) exit(1);
    }
    
    linha = (char*)malloc(tamanho_linha*sizeof(char));
   
    linha = fgets(linha, (tamanho_linha), arquivo); /* pula o restante da primeira linha */
    
    i = 0;
    while (i < tamanho_matriz) {
        linha = fgets(linha, (tamanho_linha), arquivo);
        token = strtok(linha, " "); /* divide o conteúdo da linha, utilizando o " " como delimitador */
        
        j = 0;
        while (j < tamanho_matriz) {
            matriz[i][j] = atoi(token);
            token = strtok(NULL, " ");
            j++;
        }
        i++;
    }
    free(linha);
    fclose(arquivo);

    (*tamanho) = tamanho_matriz;
    return matriz;
}

void mostra_matriz(int **matriz, int tamanho)
{
    int i, j;
    for (i = 0; i < tamanho; i++) {
        for (j = 0; j < tamanho; j++) {
            printf(" %i ", matriz[i][j]);
        }
        printf("\n");
    }
}

int verifica_simetria(int **matriz) {
    int i, j;
    for (i = 0; i < 20; i++) {
        for (j = 0; j < 20; j++) {
            if (matriz[i][j] != matriz[j][i])
                return 0;
        }
        
    }
    return 1;
}



int *conexao_vertices(int **matriz, int *caminho, int vertice_ini, int vertice_fim)
{
    static int id_caminho = 0;
    int id_caminho_ant = 0;

    if (matriz == NULL) /* matriz vazia */
        return NULL;

    caminho[id_caminho++] = vertice_ini; /* adiciona vértice no caminho */
    id_caminho_ant = id_caminho;    /* salva o vértice de origem dessa recursão */

    if (vertice_fim+1 == 1) /* só há um vértice na matriz */
        return caminho;

    if (matriz[vertice_ini][vertice_fim] == 1) { /* há conexão direta entre o primeiro e o último vértice */
        caminho[id_caminho++] = vertice_fim;
        return caminho;
    }

    /* verifica, por recursão, se há alguma vértice conectado ao primeiro,
       que se ligue ao último
    */
    int i, *caminho_temp;
    for (i = vertice_ini+1; i <= vertice_fim; i++) {
        if (matriz[vertice_ini][i] == 1) {
            caminho_temp = conexao_vertices(matriz, caminho, i, vertice_fim);

            if (caminho_temp != NULL) { /* encontrou uma conexão */
                caminho = caminho_temp;
                caminho = (int*)realloc(caminho, (id_caminho+1)*sizeof(int));
                if (caminho == NULL) exit(1);

                caminho[id_caminho] = 0;  /* marcador de parada no fim */
                return caminho;         /* finaliza busca */
            } 

            else { /* entrou numa ramificação que não se conecta ao último vértice */
                /* busca continua */
                caminho[id_caminho] = 0;        /* limpa o ramo errado do caminho */
                id_caminho = id_caminho_ant;    /* índice retorna ao vértice de origem do ramo */
            }
        }
    }
    
    /* Não há um caminho ligando o primeiro e o último vértice */
    return NULL;

}

int *vertices_isolados(int **matriz, int *vertice_arr, int tamanho, int *num_vertices)
{
    int i, j, vertice_isolado, *vertice;
    int vertice_count = 0;

    // Verifica cada vértice na matriz
    for (i = 0; i < tamanho; i++) {
        vertice_isolado = 1; /* Assume que o vértice é isolado inicialmente */

        // Verifica a linha correspondente ao vértice na matriz
        for (j = 0; j < tamanho; j++) {
            if (matriz[i][j] == 1) {    /* não é isolado */
                vertice_isolado = 0;
                break;  /* interrompe loop */
            }
        }

        // alocar espaço no vetor, para adicionar vértice:
        if (vertice_isolado)
            vertice_arr[vertice_count++] = i;
    }

    vertice_arr = (int*)realloc(vertice_arr, (vertice_count+1)*sizeof(int));
    if (vertice_arr == NULL) exit(1);

    *num_vertices = vertice_count;
    return vertice_arr;
}