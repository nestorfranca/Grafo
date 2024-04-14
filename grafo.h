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

int *vertices_isolados(int **matriz, int *vertice_arr, int tamanho, int *num_vertices);

/* Função grau_vertices

  - Retorna o grau de cada vertice
*/
int *grau_vertices(int **matriz, int tamanho);

/* Função maior_vertice

  - Retona um vetor com os maiores vertices
*/
int *maior_vertice(int *grau, int tamanho, int *quantidade_vertices);

/* Função realocar_memoria

  - Realoca a memoria para o tamanho especificado
*/
int *realocar_memoria(int *vetor, int tamanho_vetor);

/* Função grau_arquivo

  - Cria um arquivo e escreve qual o grau de cada vertice
*/
void grau_arquivo(int *grau, int tamanho);