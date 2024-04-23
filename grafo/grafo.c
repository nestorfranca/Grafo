#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "grafo.h"
#include "../geral/geral.h"

int **le_matriz(char *nome_arquivo, int **matriz, int *tamanho)
{
    FILE *arquivo;
    char *linha, *token;
    int tamanho_matriz, tamanho_linha;
    int i, j;

    arquivo = fopen(nome_arquivo, "rt");
    
    fscanf(arquivo, "%d", &tamanho_matriz); /* lê o tamanho da matriz */
    while (fgetc(arquivo) != '\n'); /* pula para a próxima linha */
    
    if (tamanho_matriz > 0) {
        matriz = (int**)malloc(tamanho_matriz*sizeof(int*));
        if (matriz == NULL) exit(1);
        for (i = 0; i < tamanho_matriz; i++) {
            matriz[i] = (int*)malloc(tamanho_matriz*sizeof(int));
            if (matriz[i] == NULL) exit(1);
        }
    }

    while (!feof(arquivo)) {
        for (i = 0; i < tamanho_matriz; i++) {
            for (j = 0; j < tamanho_matriz; j++) {
                fscanf(arquivo, "%d", &matriz[i][j]);
                // printf("%d ", matriz[i][j]);
            }
            while (fgetc(arquivo) != '\n');
            // printf("\n");
        }
        if (i == tamanho_matriz) break;
    }

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
                grau_vertice += matriz[i][j];
            }
            grau[i] = grau_vertice;
        }
        return grau;
    }
    
    return NULL;
}

int *maior_grau(int *grau, int tamanho, int *num_vertices)
{
    int i, vetor_count = 0, maior_grau = 0;
    int *maior_graus = (int*)malloc(tamanho*sizeof(int));

    if (maior_graus != NULL) {
        for (i = 0; i < tamanho; i++) {
            // Se o grau for igual, então o vértice é adicionado ao vetor maior_grau:
            if (grau[i] == maior_grau)
                maior_graus[vetor_count++] = i;
                
            // Se encontrar grau maior, ignora os valores antigos no vetor:
            else if (grau[i] > maior_grau) {
                if (vetor_count > 0) {
                    vetor_count = 0;    /* reinicia contagem do vetor */
                }
                maior_grau = grau[i];   /* atualiza o maior grau */
                maior_graus[vetor_count++] = i;
            }
        }
    }

    // realoca memória, para a quantidade correta de elementos no vetor:
    maior_graus = realoca_vetor(maior_graus, vetor_count);
    if (maior_graus != NULL)
        (*num_vertices) = vetor_count;  /* retorna a tamanho do vetor por ponteiro */
    
    return maior_graus;
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
    alert(2);   /* arquivo salvo com sucesso */
}

int *vertices_isolados(int **matriz, int tamanho, int *num_vertices)
{
    int *vertices_isolado = (int*)malloc(tamanho*sizeof(int));
    if (vertices_isolado == NULL) exit(1);

    int i, j, isolado;
    int isolados_count = 0;

    // Verifica cada vértice na matriz
    for (i = 0; i < tamanho; i++) {
        isolado = 1; /* Assume que o vértice é isolado inicialmente */

        // Verifica a linha correspondente ao vértice na matriz
        for (j = 0; j < tamanho; j++) {
            if (matriz[i][j] != 0) {    /* não é isolado */
                isolado = 0;
                break;  /* interrompe loop */
            }
        }

        // se for isolado, adiciona vértice ao vetor:
        if (isolado)
            vertices_isolado[isolados_count++] = i;  /* retorna a tamanho do vetor por ponteiro */
    }

    // realoca memória, para a quantidade correta de elementos no vetor:
    vertices_isolado = realoca_vetor(vertices_isolado, isolados_count);
    if (vertices_isolado != NULL)
        (*num_vertices) = isolados_count;

    return vertices_isolado;
}

int *vertices_multiplos_5(int **matriz, int tamanho, int *num_vertices)
{
    int i, tamanho_vetor = 0;
    int *vertices_5mult = (int*)malloc(tamanho*sizeof(int));
    
    for (i = 0; i < tamanho; i++) {
        if (i%5 == 0) {
            vertices_5mult[tamanho_vetor++] = i;
        } 
    }

    // realoca memória, para a quantidade correta de elementos no vetor:
    vertices_5mult = realoca_vetor(vertices_5mult, tamanho_vetor);
    if (vertices_5mult != NULL)
        (*num_vertices) = tamanho_vetor;

    return vertices_5mult;
}

int **subgrafo_induzido(int **matriz, int *vertices, int tamanho, int tamanho_induzido)
{
    int i, j;
    int **matriz_induzida = NULL;    
    
    // Alocar memória para a nova matriz
    if (tamanho > 0 && tamanho_induzido > 0) {
        matriz_induzida = (int**)malloc(tamanho_induzido*sizeof(int*));
        if (matriz_induzida == NULL) return NULL;

        for (i = 0; i < tamanho_induzido; i++) {
            matriz_induzida[i] = (int*)malloc(tamanho_induzido*sizeof(int));
            if (matriz_induzida[i] == NULL) return NULL;
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
                if (i_induzido == tamanho_induzido) break;
            }
        }
    } else
        alert(-3);  /* matriz com tamanho 0 ou não encontrada */

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
    
    if (matriz != NULL) {
        for (i = 0; i < tamanho; i++) {
            for (j = i; j < tamanho; j++) {
                if (matriz[i][j] == 0 && i != j) {
                    return 0; // Não é um clique
                }
            }
        }
        return 1; // É um clique
    }
    
    return 0;
}

int *copia_vetor(int *vetor_dst, int *vetor_src, int tam_vetor_dst, int tam_vetor_src)
{
    if (vetor_dst == NULL)
        vetor_dst = (int*)malloc((tam_vetor_src)*sizeof(int));

    if (tam_vetor_src > tam_vetor_dst) {
        vetor_dst = realoca_vetor(vetor_dst, tam_vetor_src);
        tam_vetor_dst = tam_vetor_src;
    }

    int i;
    if (vetor_dst != NULL && tam_vetor_dst > 0)
        for (i = 0; i < tam_vetor_dst; i++) {
            vetor_dst[i] = vetor_src[i];
        }
    
    // free(vetor_src);
    return vetor_dst;
}

int *candidatos_clique(int **matriz, int tamanho, int vertice_linha, int vertice_iter, int *tamanho_clique)
{
    // Tipo estático para não repetir inicialização em caso se entrar na recursão:
    static int *vertices_maior_clique = NULL, tam_maior_clique, recursao;
    static int *vetor_candidatos = NULL, id_candidatos = 0;
    int **clique = NULL;

    if (matriz == NULL) /* matriz vazia */
        return NULL;

    // no início da execução da função, aloca espaço do vetor de candidatos:
    if (id_candidatos == 0) {
        vetor_candidatos = (int*)malloc((tamanho)*sizeof(int));
        if (vetor_candidatos == NULL) return NULL;
    }

    vetor_candidatos[id_candidatos++] = vertice_iter; /* adiciona o vertice à lista de candidatos */
    
    if (id_candidatos > 1) {    /* o teste de clique ocorre apenas com 2 ou mais vértices */

        // cria um subgrafo com os vértices candidatos:
        clique = subgrafo_induzido(matriz, vetor_candidatos, tamanho, id_candidatos);
        if (verifica_clique(clique, id_candidatos)) { /* testa se é clique */
            
            // cliques menores ou igual ao maior clique não importam
            if (id_candidatos > tam_maior_clique) {
                
                tam_maior_clique = id_candidatos;   /* atualiza as variáveis do maior clique */
                vertices_maior_clique = copia_vetor(vertices_maior_clique, vetor_candidatos, id_candidatos, tam_maior_clique);
                free(clique);
            } 
        } else {
            free(clique);
            return NULL;        /* os vértices NÃO formam um clique */
        }
    }


    // testa todos os cliques possíveis que possua o "vertice_iter"
    int i, j;
    for (i = (vertice_iter+1); i < tamanho; i++) {
        if (matriz[vertice_linha][i] != 0) {
            
            recursao++; /* incrementa antes de entrar na recursão */
            candidatos_clique(matriz, tamanho, vertice_linha, i, tamanho_clique);
            recursao--; /* decrementa ao voltar */
            id_candidatos--; /* retorna o id a posição anterior à recursão */
        }
    }
    
    // assim que voltar para o nível original, retorna maior vetor encontrado:
    if (recursao == 0) {
        
        (*tamanho_clique) = tam_maior_clique;
        
        // reseta os parâmetros estáticos:
        id_candidatos = 0;
        free(vetor_candidatos);
        return vertices_maior_clique;
    }
    
    /* Não há um candidatos ligando o primeiro e o último vértice */
    return NULL;
}

int *conexao_vertices(int **matriz, int *vetor_caminho, int tamanho, int vertice_ini, int vertice_fim)
{
    // Tipo estático para não repetir inicialização em caso se entrar na recursão
    static int id_caminho = 0;
    int id_caminho_origem;
    // printf("id: %d\n", id_caminho); delay(100);

    if (matriz == NULL) /* matriz vazia */
        return NULL;

    if (id_caminho == 0) {
        vetor_caminho = (int*)malloc(tamanho+1*sizeof(int));
        if (vetor_caminho == NULL) return NULL;
    }

    vetor_caminho[id_caminho++] = vertice_ini; /* adiciona vértice no caminho */
    id_caminho_origem = id_caminho;    /* salva o vértice de origem dessa recursão */

    if (matriz[vertice_ini][vertice_fim] == 1) { /* há conexão direta entre o primeiro e o último vértice */
        vetor_caminho[id_caminho++] = vertice_fim;
        vetor_caminho[id_caminho] = -1; /* marcador de parada no fim */
        id_caminho = 0;
        return vetor_caminho;
    }

    // verifica os vértices vizinhos, recursivamente:
    int i, *caminho_temp;
    for (i = vertice_ini+1; i <= vertice_fim; i++) {
        if (matriz[vertice_ini][i] == 1) {
            caminho_temp = conexao_vertices(matriz, vetor_caminho, tamanho, i, vertice_fim);

            if (caminho_temp != NULL) { /* encontrou uma conexão */
                vetor_caminho = caminho_temp;

                if (id_caminho > 0) {
                    vetor_caminho = (int*)realloc(vetor_caminho, id_caminho*sizeof(int));

                    if (vetor_caminho == NULL) return NULL;
                }

                id_caminho = 0;
                
                return vetor_caminho;         /* finaliza busca */
            } 

            else { /* entrou numa ramificação que não se conecta ao último vértice */
                id_caminho = id_caminho_origem;    /* índice retorna ao vértice de origem do ramo */
                /* a busca continua */
            }
        }
    }
    
    /* Não há um caminho ligando o primeiro e o último vértice */
    return NULL;
}