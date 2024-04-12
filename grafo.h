/* Módulo grafo.h */
#include <stdio.h>

/* Funções exportadas */

/* Função importa_matriz
*/
int **importa_matriz(char *nome_arquivo, int **matriz, int *tamanho);

/* Função mostra_matriz
*/
void mostra_matriz(int **matriz, int tamanho);

/* Função verifica_simetria
*/
int verifica_simetria(int **matriz);

/* Função conexao_primeiro_ultimo

 - Verifica se há um caminho que conecte os vertices
   escolhidos
*/
int *conexao_vertices(int **matriz, int *caminho, int vertice_ini, int vertice_fim);