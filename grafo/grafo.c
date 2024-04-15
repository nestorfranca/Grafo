#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "grafo.h"
#include "../geral/geral.h"

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

int verifica_simetria(int **matriz)
{
    int i, j;
    for (i = 0; i < 20; i++) {
        for (j = 0; j < 20; j++) {
            if (matriz[i][j] != matriz[j][i])
                return 0;
        }
        
    }
    return 1;
}

int *grau_vertice(int **matriz, int tamanho)
{
    int i, j, *grau;

    if (tamanho > 0) {
        grau = (int*)malloc(tamanho * sizeof(int));
        if (grau == NULL) exit(1);

        for (i = 0; i < tamanho; i++) {
            int grau_vertice = 0;

            for(j = 0; j < tamanho; j++) {
                if (matriz[i][j] == 1) {
                    grau_vertice++;
                }
            }
            grau[i] = grau_vertice;
        }
        return grau;
    }
    
    return NULL;
}

int *maior_grau(int *grau, int tamanho, int *num_vertices)
{
    int i, vetor_count = 0, maior_grau;
    int *maiores_vertices = (int*)malloc(tamanho*sizeof(int));

    maior_grau = grau[0];
    maiores_vertices[vetor_count++] = 0;
    
    for (i = 1; i < tamanho; i++) {
        // Se o grau for igual, então o vértice é adiciona ao vetor maior_grau:
        if (grau[i] == maior_grau)
            maiores_vertices[vetor_count++] = i;
            
        // Se encontrar grau maior, o vetor de valor antigo é descosiderado:
        else if (grau[i] > maior_grau) {
            if (vetor_count > 0) {
                vetor_count = 0;    /* reinicia contagem do vetor */
            }
            maior_grau = grau[i];   /* atualiza o maior grau */
            maiores_vertices[vetor_count++] = i;
        }
    }

    maiores_vertices = (int*)realloc(maiores_vertices, (vetor_count+1)*sizeof(int));
    if (maiores_vertices == NULL) exit(1);

    (*num_vertices) = vetor_count;

    return (vetor_count > 0) ? maiores_vertices : NULL;
}

void grau_arquivo(int *grau, int tamanho)
{
    FILE *arquivo = fopen("dados_grafos_graus.txt", "wt");
    if(arquivo == NULL) exit(1);

    fprintf(arquivo, "%-8s\t%-4s\n", "Vertice", "Grau");

    int i;
    for (i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%-8d\t%-4d\n", (i+1), grau[i]);
    }

    fclose(arquivo);
    alert(2);
}

int *vertices_isolados(int **matriz, int tamanho, int *num_vertices)
{
    int *vertice_arr = (int*)malloc(tamanho*sizeof(int));
    if (vertice_arr == NULL) exit(1);

    int i, j, vertice_isolado;
    int isolados_count = 0;

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
            vertice_arr[isolados_count++] = i;
    }

    (*num_vertices) = isolados_count;

    if (isolados_count > 0) {
        vertice_arr = (int*)realloc(vertice_arr, (isolados_count)*sizeof(int));
        if (vertice_arr == NULL) exit(1);
        return vertice_arr;
    }

    return NULL;
}

int *vertices_multiplos_5(int **matriz, int tamanho, int *num_vertices)
{
    int i, tamanho_induzido = tamanho / 5;
    int *vertices_5mult = NULL;

    vertices_5mult = (int*)malloc(tamanho_induzido*sizeof(int));
    if (vertices_5mult == NULL) exit(1);

    int vertice_count = 0;
    for (i = 0; i < tamanho; i++) {
        if ((i+1) % 5 == 0) {
            vertices_5mult[vertice_count++] = i;
        }
    }

    (*num_vertices) = vertice_count;

    return vertices_5mult;
}

int **subgrafo_induzido(int **matriz, int *vertices, int tamanho, int tamanho_induzido)
{
    // Determinar o tamanho da nova matriz (vértices múltiplos de 5)
    int i, j;
    
    // printf("%d - %d\n", tamanho, tamanho_induzido);
    int **matriz_induzida = NULL;
    
    // Alocar memória para a nova matriz
    if (tamanho_induzido > 0) {
        matriz_induzida = (int**)malloc(tamanho_induzido*sizeof(int*));
        if (matriz_induzida == NULL) exit(1);

        for (i = 0; i < tamanho_induzido; i++) {
            matriz_induzida[i] = (int*)malloc(tamanho_induzido*sizeof(int));
            if (matriz_induzida[i] == NULL) exit(1);
        }
        
        // Preencher a nova matriz com os elementos de índice múltiplo de 5 da matriz original
        int i_induzido = 0;
        printf("\n");

        for (i = 0; i < tamanho; i++) {
            if (i == vertices[i_induzido]) {
                int j_induzido = 0;
                for (j = 0; j < tamanho; j++) {
                    if (j == vertices[j_induzido]) {
                        matriz_induzida[i_induzido][j_induzido] = matriz[i][j];
                        j_induzido++;
                        if (j_induzido >= tamanho_induzido) break;
                    }
                }
                i_induzido++;
                if (i_induzido >= tamanho_induzido) break;
            }
        }
    }

    return matriz_induzida;
}

void salva_grafo(int **matriz_subgrafo, int tamanho, char *nome_arquivo)
{
    // Abrir o arquivo para escrita
    FILE *arquivo = fopen(nome_arquivo, "wt");
    if (arquivo == NULL) exit(1);

    // Escrever a nova matriz no arquivo
    fprintf(arquivo, "%d %d\n", tamanho, tamanho);
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            fprintf(arquivo, "%d ", matriz_subgrafo[i][j]);
        }
        fprintf(arquivo, "\n"); // Nova linha para cada linha da matriz
    }

    fclose(arquivo); // Fechar o arquivo após a escrita
}


int *conexao_vertices(int **matriz, int tamanho, int vertice_ini, int vertice_fim)
{
    static int *caminho, id_caminho = 0;
    int id_caminho_ant = 0;

    if (id_caminho == 0) {
        caminho = (int*)malloc(tamanho*sizeof(int));
        if (caminho == NULL) exit(1);
    }

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
            caminho_temp = conexao_vertices(matriz, tamanho, i, vertice_fim);

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