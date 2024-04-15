/* Módulo grafo.h */
#include <stdio.h>

/* Funções exportadas */

/* Função importa_matriz
 - Importa dados da matriz de um arquivo externo
*/
int **importa_matriz(char *nome_arquivo, int **matriz, int *tamanho);

/* Função mostra_matriz
 - Exibe os valores da matriz na interface
*/
void mostra_matriz(int **matriz, int tamanho);

/* Função verifica_simetria
 - Verifica se a matriz é simétrica
*/
int verifica_simetria(int **matriz);

/* Função conexao_primeiro_ultimo
 - Verifica se há um caminho que conecte os vertices
   escolhidos
*/
int *conexao_vertices(int **matriz, int tamanho, int vertice_ini, int vertice_fim);

/* Função vertices_isolados
 - Verifica vetor com os vértices isolados, se existir
*/
int *vertices_isolados(int **matriz, int tamanho, int *num_vertices);

/* Função grau_vertice
  - Retorna o grau de cada vertice
*/
int *grau_vertice(int **matriz, int tamanho);

/* Função maior_vertice
  - Retona um vetor com os maiores vertices
*/
int *maior_grau(int *grau, int tamanho, int *quantidade_vertices);

/* Função grau_arquivo
  - Cria um arquivo e escreve qual o grau de cada vertice
*/
void grau_arquivo(int *grau, int tamanho);

int **subgrafo_induzido(int **matriz, int tamanho, char *nome_arquivo);
