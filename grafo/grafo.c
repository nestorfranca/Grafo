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
    while (fgetc(arquivo) != '\n');

    tamanho_linha = 2*tamanho_matriz+1; /* tamanho da linha */

    matriz = (int**)malloc(tamanho_matriz*sizeof(int*));
    if (matriz == NULL) exit(1);
    for (i = 0; i < tamanho_matriz; i++) {
        matriz[i] = (int*)malloc(tamanho_matriz*sizeof(int));
        if (matriz[i] == NULL) exit(1);
    }
    
    linha = (char*)malloc(tamanho_linha*sizeof(char));
    
    i = 0;
    while (i < tamanho_matriz) {
        linha = fgets(linha, tamanho_linha, arquivo);
        // linha[tamanho_linha] = '\0';
        while (fgetc(arquivo) != '\n');
        
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

int verifica_simetria(int **matriz, int tamanho)
{
    int i, j;
    int count1 = 0, count2 = 0;
    for (i = 0; i < tamanho; i++) {
        for (j = 0; j < tamanho; j++) {
            // printf("m[%d][%d] = %d e m[%d][%d] = %d\n", i, j, matriz[i][j], j, i, matriz[j][i]); delay(1000);
            if (matriz[i][j] != matriz[j][i])
                return 0;
            
            count2++;
        }
        count1++;
    }
    // printf("%d ", count1);
    // printf("%d ", count2);
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
    int i, tamanho_induzido = 0;
    int *vertices_5mult = (int*)malloc(tamanho*sizeof(int));
    
    for (i = 0; i < tamanho; i++) {
        if (i%5 == 0) {
            vertices_5mult[tamanho_induzido++] = i;
        } 
    }

    if (tamanho_induzido > 0) {
        vertices_5mult = (int*)realloc(vertices_5mult, (tamanho_induzido)*sizeof(int));
        if (vertices_5mult == NULL) exit(1);
    }

    (*num_vertices) = tamanho_induzido;

    return vertices_5mult;
}

int **subgrafo_induzido(int **matriz, int *vertices, int tamanho, int tamanho_induzido)
{
    // Determinar o tamanho da nova matriz (vértices múltiplos de 5)
    int i, j;
    
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

int verifica_clique(int **matriz, int tamanho)
{
    int i, j;
    for (i = 0; i < tamanho; i++) {
        for (j = (i+1); j < tamanho; j++) {
            if (matriz[i][j] == 0) {
                return 0; // Não é um clique
            }
        }
    }
    return 1; // É um clique
}

int *copia_vetor(int *vetor_dst, int *vetor_src, int tamanho_vetor)
{
    if (vetor_dst == NULL)
        vetor_dst = (int*)malloc((tamanho_vetor)*sizeof(int));

    int i;
    if (tamanho_vetor > 0)
        for (i = 0; i < tamanho_vetor; i++) {
            vetor_dst[i] = vetor_src[i];
        }
    
    return vetor_dst;
}

// int *candidatos_clique(int **matriz, int tamanho, int vertice_ini, int *tamanho_clique)
int *candidatos_clique(int **matriz, int tamanho, int vertice_linha, int vertice_iter, int *tamanho_clique)
{
    static int *vertices_maior_clique = NULL, tam_maior_clique = 0, recursao = 0;
    // for (int i = 0; i < tam_maior_clique; i++) printf("%d ", vertices_maior_clique[i]); printf("caca\n");
    static int *candidatos = NULL, id_candidatos = 0;
    int id_candidatos_ant = 0;

    // printf("id = %d\n", id_candidatos); delay(1000);
    if (id_candidatos == 0) {
        // printf("comeco\n\n");
        
        candidatos = (int*)malloc((tamanho)*sizeof(int));
        if (candidatos == NULL) exit(1);
    }

    if (matriz == NULL) /* matriz vazia */
        return NULL;

    candidatos[id_candidatos++] = vertice_iter;
    id_candidatos_ant = id_candidatos;

    
    // for (int i = 0; i < id_candidatos; i++) printf("%d ", candidatos[i]); printf("\n");
    if (id_candidatos > 1) {
        int **clique = subgrafo_induzido(matriz, candidatos, tamanho, id_candidatos);
        if (verifica_clique(clique, id_candidatos)) {
            // printf(" - eh clique\n");
            if (id_candidatos > tam_maior_clique) {
                tam_maior_clique = id_candidatos;
                vertices_maior_clique = copia_vetor(vertices_maior_clique, candidatos, tam_maior_clique);
                // printf("tam_max: %d\n", tam_maior_clique); delay(1000);
                // for (int i = 0; i < tam_maior_clique; i++) printf("%d ", vertices_maior_clique[i]); printf("caca\n");

            }
            free(clique);

        } else {

            free(clique);
            return NULL;        /* os vértices NÃO formam um clique */
        }
    }

    // testa todos os cliques possíveis que possua o "vertice_iter"
    int i, j;
    for (i = (vertice_iter+1); i < tamanho; i++) {
        if (matriz[vertice_linha][i] != 0) {
            // printf("m[%d][%d] = %d\n", vertice_linha, i, matriz[vertice_linha][i]); delay(1000);

            recursao++;
            candidatos_clique(matriz, tamanho, vertice_linha, i, &tam_maior_clique);
            recursao--;

            id_candidatos = id_candidatos_ant;

        }
        
        if (recursao == 0 && i == tamanho-1) {
            // printf("tam_max: %d\n", tam_maior_clique);
            (*tamanho_clique) = tam_maior_clique;

            // for (int i = 0; i < tam_maior_clique; i++) printf("%d ", vertices_maior_clique[i]); printf("caca\n"); delay(1000);
            
            // reseta os parâmetros estáticos:
            id_candidatos = 0; recursao = 0; tam_maior_clique = 0;
            free(candidatos);
            
            // printf("fim dentro\n"); delay(2000);
            return vertices_maior_clique;
        }
    }
    // free(candidatos);
    /* Não há um candidatos ligando o primeiro e o último vértice */
    return NULL;
}

int *conexao_vertices(int **matriz, int tamanho, int vertice_ini, int vertice_fim)
{
    static int *caminho, id_caminho = 0;
    int id_caminho_ant = 0;

    if (matriz == NULL) /* matriz vazia */
        return NULL;

    if (id_caminho == 0) {
        caminho = (int*)malloc(tamanho+1*sizeof(int));
        if (caminho == NULL) exit(1);
    }

    caminho[id_caminho++] = vertice_ini; /* adiciona vértice no caminho */
    id_caminho_ant = id_caminho;    /* salva o vértice de origem dessa recursão */

    if (matriz[vertice_ini][vertice_fim] == 1) { /* há conexão direta entre o primeiro e o último vértice */
        caminho[id_caminho++] = vertice_fim;
        caminho[id_caminho] = 0;
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