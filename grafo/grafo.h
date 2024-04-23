/* Módulo grafo.h */
#include <stdio.h>

/* Funções exportadas */

/* Função importa_matriz
 - Importa dados da matriz de um arquivo externo
*/
int **le_matriz(char *nome_arquivo, int **matriz, int *tamanho);

/* Função mostra_matriz
 - Exibe os valores da matriz na interface
*/
void mostra_matriz(int **matriz, int tamanho);

/* Função verifica_simetria
 - Verifica se a matriz é simétrica
*/
int verifica_simetria(int **matriz, int tamanho);

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

/* Função vertices_isolados
 - Verifica vetor com os vértices isolados, se existir
*/
int *vertices_isolados(int **matriz, int tamanho, int *num_vertices);

/* Função vertices_multiplos_5
 - Retorna um vetor com os vértices múltiplos de 5.
*/
int *vertices_multiplos_5(int **matriz, int tamanho, int *num_vertices);

/* Função subgrafo_induzido
 - Gera um subgrafo induzido, a partir dos vértices inseridos.
*/
int **subgrafo_induzido(int **matriz, int *vertices, int tamanho, int tamanho_induzido);

/* Função salva_grafo
 - Escreve a matriz booleana do grafo em um arquivo.
*/
void salva_grafo(int **matriz_subgrafo, int tamanho, char *nome_arquivo);

/* Função verifica_clique
 - Testa se a matriz do subgrafo inserido é um clique.
*/
int verifica_clique(int **matriz, int tamanho);

/* Função copia_vetor
 - Faz a cópia de um vetor, elemento por elemento.
*/
int *copia_vetor(int *vetor_dst, int *vetor_src, int tam_vetor_dst, int tam_vetor_src);

/* Função candidator_clique
 - Testa todas as possibilidades de cominação entre vértices conectados
   ao vértice de uma linha, até achar o maior clique.
*/
// int *candidatos_clique(int **matriz, int *vetor_candidatos, int tamanho, int vertice_linha, int vertice_iter);
int *candidatos_clique(int **matriz, int tamanho, int vertice_linha, int vertice_iter, int *tamanho_clique);

/* Função conexao_primeiro_ultimo
 - Verifica se há um caminho que conecte os vertices
   escolhidos
*/
int *conexao_vertices(int **matriz, int *vetor_caminho, int tamanho, int vertice_ini, int vertice_fim);