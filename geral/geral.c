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
    printf("===============================================================================================\n");
    printf("\t%s\t%s\t\t%s\n", pagina, titulo, num_pag);
    printf("===============================================================================================\n");
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

int teste_formato(char *str)
{
    int i;
    int negativo = 0;
    for (i = 0; str[i] != '\0'; i++)    /* verifica cada caracter */
    {
        if (!(str[i] >= '0' && str[i] <= '9'))  /* verifica se o caracter é numérico */
        {   
            if (i == 0 && str[i] == '-')
                negativo++;
            else
                return 0;   /* é string */
        }
    }
    if (negativo == 1)
    {
        return -1;          /* é número negativo */
    }
    return 1;               /* é número positivo */
}

int menu_principal(int **matriz, int tamanho) {
    int opcao;
    char nome_contato[35], ch_op4[3];

    cabecalho("\t\t\t", "RESPOSTAS\t", "");
    
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
            printf("\nCalculando Grau...");  delay(ATRASO);

            // calcula o grau de todos os vértices:
            int *grau = grau_vertice(matriz, tamanho);

            // armazena a informação do grau dos vértices num arquivo:
            grau_arquivo(grau, tamanho);

            while (1) {
                cabecalho("\t", "\t\tMAIOR GRAU\t", "");

                printf("Vertice(s) com maior(es) grau:\n");
                // identifica qual os vértices tem o maior grau:
                int quantidade_vertices;
                int *maiores_grau = maior_grau(grau, tamanho, &quantidade_vertices);
                for (int i = 0; i < quantidade_vertices; i++) {
                    printf("Vertice %d:  %d\n", maiores_grau[i], grau[maiores_grau[i]]);
                }


                // libera memória alocada
                free(maiores_grau);

                if (menu_voltar()) break;
            }
            free(grau);

            delay(ATRASO);
            break;
        }
        case '2': { /* Vértices Isolados */
            printf("\nAnalisando Grafo...");  delay(ATRASO);

            while (1) {
                cabecalho("\t", "\t\tVERTICES ISOLADOS\t", "");

                /* ===== VÉRTICES ISOLADOS ===== */
                int num_isolados;
                int *isolados = vertices_isolados(matriz, tamanho, &num_isolados);
                
                printf("Encontrou %d vertice(s) isolado(s):\n", num_isolados);
                if (isolados != NULL) {
                    printf("%d", isolados[0]);
                    for (int i = 1; i < num_isolados; i++) {
                        printf(" - %d", isolados[i]);
                    }
                    printf("\n");

                }

                free(isolados);

                if (menu_voltar()) break;
            }

            delay(ATRASO);
            break;
        }
        case '3': { /*Grafo com vértices múltiplo de 5 */
            printf("\nGerando Grafo Gerador...");  delay(ATRASO);

            alert(2);
            break;
        }
        case '4': { /* maior clique */
            printf("\nAnalisando Grafo...");  delay(ATRASO);

            while (1) {
                cabecalho("\t", "\t\tCLIQUE\t", "");

                printf("Vertice(s) com maior(es) clique:\n");


                if (menu_voltar()) break;
            }

            delay(ATRASO);
            break;
        }
        case '5': { /* conexão entre vértices */
            printf("\nAnalisando Tabela...");  delay(ATRASO);

            while (1) {
                cabecalho("\t", "\t\tCONEXAO ENTRE VERTICES\t", "");
                
                int *caminho = conexao_vertices(matriz, tamanho, 0, tamanho-1);

                if (caminho != NULL) {
                    printf("Caminho entres os vertices %d e %d:\n", 0, tamanho-1);
                    
                    printf("%d ", caminho[0]);
                    int i;
                    for (i = 1; caminho[i] != 0; i++) {
                        printf("-> %d ", caminho[i]);
                    }
                    printf("\n");

                } else {
                    printf("Nao ha conexao entre o primeiro e o ultimo vertice!\n");
                }
                fflush(stdin);

                if (menu_voltar()) break;
            }

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
    // alerta de processo:

    alert(0);    /* reseta marcador */
}