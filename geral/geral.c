#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "geral.h"
#include "../grafo/grafo.c"

// const char data_hoje[11] = "01/01/2023";
#define ATRASO 200

#define TXT_red "\x1b[31m"
#define TXT_green "\x1b[32m"
#define TXT_yellow "\x1b[33m"
#define TXT_reset "\x1b[0m"
int alert_cod = 0;

void delay(double milissegundos)
{
    // Armazenando tempo inicial:
    clock_t tempo_inicial = clock();
    
    // looping till required time is not achieved
    while (milissegundos > clock() - tempo_inicial);
}

char *clear(void)
{    
    // Checking for windows OS with
    // _WIN32 macro
    #ifdef _WIN32
        return "cls";

    // Checking for mac OS with
    // __APPLE__ macro
    #elif __APPLE__
        return "clear";

    // Checking for linux OS with
    // __linux__ macro
    #elif __linux__
        return "clear";
    #endif
}

void cabecalho(char *pagina, char *titulo, char *num_pag)
{
    system(clear());
    printf("======================================================================\n");
    printf("\t%s\t%s\t\t%s\n", pagina, titulo, num_pag);
    printf("======================================================================\n");
}

int teste_input(void)
{
    char teste[100];
    int i = 0;
    while ((teste[i] = getchar()) != '\n') i++;
    teste[i] = '\0';
    int len = strlen(teste); // remove o '\n' do final da string

    if (len == 0)
        return '\n';
    else if(len == 1)    /* é esperado input com apenas 1 caracter */
        return toupper(teste[0]);

    return 0;       /* input invalido */
}

int menu_principal(int **matriz, int tamanho) {
    int opcao;
    char nome_contato[35], ch_op4[3];

    cabecalho("GRAFO\t", "RESPOSTAS\t", "");
    
    printf(">>> [1] GRAU DOS VERTICES\n");
    printf(">>> [2] VERTICES ISOLADOS\n");
    printf(">>> [3] GRAFO GERADOR COM VERTICES MULTIPLOS DE 5\n");
    printf(">>> [4] MAIOR CLIQUE\n");
    printf(">>> [5] CONEXAO ENTRE VERTICES\n");
    printf(">>> [6] SAIR\n");
    
    alert_msg();
    printf("Escolha uma opcao: ");
    opcao = teste_input();

    switch (opcao) {
        case '1': { /* Grau dos vertices */
            printf("\nCalculando Grau..."); delay(ATRASO);

            // calcula o grau de todos os vértices:
            int *grau = grau_vertice(matriz, tamanho);

            if (grau != NULL) {
                // armazena a informação do grau dos vértices num arquivo:
                grau_arquivo(grau, tamanho);

                while (1) {
                    cabecalho("GRAFO\t", "VERTICE DE MAIOR GRAU\t", "");

                    printf("Vertice(s) com maior(es) grau:\n");
                    // identifica qual os vértices tem o maior grau:
                    int quantidade_vertices = 0;
                    int *maiores_grau = maior_grau(grau, tamanho, &quantidade_vertices);
                    for (int i = 0; i < quantidade_vertices; i++) {
                        printf("Vertice %d:  %d\n", (maiores_grau[i]+1), grau[maiores_grau[i]]);
                    }

                    // libera memória alocada
                    free(maiores_grau);

                    if (menu_voltar()) break;
                }

                free(grau);
            } else {
                alert(-3);  /* Erro: matriz com tamanho 0 ou não encontrada */
            }

            delay(ATRASO);
            break;
        }
        case '2': { /* Vértices Isolados */
            printf("\nAnalisando Grafo...");  delay(ATRASO);

            while (1) {
                cabecalho("GRAFO\t", "VERTICES ISOLADOS\t", "");

                /* ===== VÉRTICES ISOLADOS ===== */
                int num_isolados = 0;
                int *isolados = vertices_isolados(matriz, tamanho, &num_isolados);
                
                printf("Encontrou %d vertice(s) isolado(s):\n", num_isolados);
                if (isolados != NULL) {
                    printf("%d", isolados[0]+1);
                    for (int i = 1; i < num_isolados; i++) {
                        printf(" - %d", isolados[i]+1);
                    }
                    printf("\n");

                }

                free(isolados);

                if (menu_voltar()) break;
            }

            delay(ATRASO);
            break;
        }
        case '3': { /* Grafo com vértices múltiplo de 5 */
            printf("\nGerando Grafo Gerador...");  delay(ATRASO);
            int tam_induzido = 0;
            int *vertices_induzido = vertices_multiplos_5(matriz, tamanho, &tam_induzido);

            int **subgrafo_multiplo_5 = subgrafo_induzido(matriz, vertices_induzido, tamanho, tam_induzido);
            if (subgrafo_multiplo_5 != NULL) {
                salva_grafo(subgrafo_multiplo_5, tam_induzido, "dados_grafo_gerador.txt");
            }

            free(vertices_induzido);
            free(subgrafo_multiplo_5);
            alert(3); /* grafo gerado com sucesso */
            break;
        }
        case '4': { /* maior clique */
            printf("\nAnalisando Grafo...");  delay(ATRASO);

            int i, j, tam_clique = 0, tam_maior_clique = 0;
            int *vertices_clique = NULL, *vertices_maior_clique = NULL;
                
            while (1) {
                cabecalho("GRAFO\t", "MAIOR CLIQUE\t", "");
                
                clock_t inicio = clock(); /* tempo inicial da execução */
                
                if (vertices_maior_clique == NULL) {
                    // testa o maior clique para todas as linhas:
                    for (i = 0; i < tamanho; i++) {
                        // vertices_clique = candidatos_clique(matriz, vertices_clique, tamanho, i, i);
                        vertices_clique = candidatos_clique(matriz, tamanho, i, i, &tam_clique);
                        // for (int i = 0; vertices_clique[i] != -1; i++) printf("%d ", vertices_clique[i]); delay(1000);
                        
                        printf("iter: %4d terminou", (i+1));
                        double tempo_sort = (double)(clock() - inicio) / CLOCKS_PER_SEC;
                        tempo_sort = tempo_sort * 1000.0; //milisegundos
                        printf(TXT_green" - Tempo de execucao: %.10lfms\n"TXT_reset, tempo_sort);

                        if (vertices_clique != NULL) {
                            if (tam_clique > tam_maior_clique) {

                                tam_maior_clique = tam_clique;
                                vertices_maior_clique = copia_vetor(vertices_maior_clique, vertices_clique, tam_maior_clique, tam_clique);
                            }
                        }
                    }
                }
                
                if (vertices_maior_clique != NULL) {

                    printf("Maior clique com %d vertices.\n", tam_maior_clique);
                    printf("Vertices do maior clique:\n");
                    
                    printf("%d", vertices_maior_clique[0]);
                    for (i = 1; i < tam_maior_clique; i++) {
                        printf(" - %d", vertices_maior_clique[i]);
                    }
                    printf("\n");

                    int **maior_clique = subgrafo_induzido(matriz, vertices_maior_clique, tamanho, tam_maior_clique);
                    salva_grafo(maior_clique, tam_maior_clique, "dado_grafo_maior_clique.txt");

                    for (i = 0; i < tam_maior_clique; i++) free(maior_clique[i]);                   
                    free(maior_clique);
                } else {
                    printf("Nao ha cliques no grafo!\n");
                }
                
                if (menu_voltar()) break;
            }

            free(vertices_maior_clique);
            delay(ATRASO);
            break;
        }
        case '5': { /* conexão entre vértices */
            printf("\nAnalisando Tabela...");  delay(ATRASO);

            int i, *caminho = NULL;
            while (1) {
                cabecalho("GRAFO\t", "CONEXAO ENTRE VERTICES\t", "");
                
                if (caminho == NULL)
                    caminho = conexao_vertices(matriz, caminho, tamanho, 0, tamanho-1);

                if (caminho != NULL) {
                    printf("Caminho entres os vertices %d e %d:\n", 1, tamanho);
                    
                    printf("%d", caminho[0]+1);
                    for (i = 1; caminho[i] != -1; i++) {
                        printf(" -> %d", caminho[i]+1);
                    }
                    printf("\n");

                } else {
                    printf("Nao ha conexao entre o primeiro e o ultimo vertice!\n");
                }

                if (menu_voltar()) break;
            }
            
            free(caminho);
            delay(ATRASO);
            break;
        }
        case '6': {
            printf("\nEncerrando programa...\n");
            delay(ATRASO);
            break;
        }
        default: {
            alert(1);
            delay(ATRASO);
            break;
        }
    }
    return opcao;
}

int menu_voltar()
{
    char op[3];

    alert_msg();
    printf("Aperte ENTER para Retornar ao Menu: ");

    int i = 0;
    while ((op[i] = getchar()) != '\n') i++;
    op[i] = '\0';

    if (strlen(op) == 0) {          /* verifica se está vazio */
        alert(0);   /* voltando para o menu (sem mensagem de erro) */
        return 1;
    }
    alert(4);   /* página não solicita entrada */
    return 0;
}

int *realoca_vetor(int *vetor, int tamanho)
{
    int i, *novo_vetor = NULL;
    if (tamanho > 0)
        novo_vetor = (int*)malloc(tamanho*sizeof(int));
    
    if (novo_vetor == NULL) {
        free(vetor);
        return NULL;
    }

    // memcpy(novo_vetor, vetor, tamanho);
    for (i = 0; i < tamanho; i++) {
        novo_vetor[i] = vetor[i];
    }

    free(vetor);
    return novo_vetor;
}

void alert(int cod)
{
    alert_cod = cod;
}

void alert_msg(void)
{
    // mensagem limpa, sem erro:
    if (alert_cod == 0) printf("\n\n");
    
    // alerta de formato: 
    else if (alert_cod == 1) printf(TXT_yellow"\nInsira uma opcao valida!\n"TXT_reset);
    else if (alert_cod == 2) printf(TXT_green"\nArquivo salvo com sucesso!\n"TXT_reset);
    else if (alert_cod == 3) printf(TXT_green"\nGrafo gerado e salvo com sucesso!\n"TXT_reset);
    else if (alert_cod == 4) printf(TXT_yellow"\nPagina nao solicita entrada!\n"TXT_reset);
    // alerta de processo:
    else if (alert_cod == -3) printf(TXT_red"\nMatriz nao encontrada!\n"TXT_reset);

    alert(0);    /* reseta marcador */
}