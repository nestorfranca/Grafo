# 1. Análise de Grafos

## Introdução
O estudo de grafos é fundamental em diversas áreas da computação e matemática, incluindo redes sociais, sistemas de transporte, otimização e muito mais. Este projeto visa oferecer uma ferramenta simples e eficiente para análise de grafos através de matrizes de adjacência, permitindo aos usuários realizar diversas operações e análises sobre os grafos.

## Problemática
A análise de grafos pode se tornar uma tarefa complexa e demorada, especialmente quando se trata de grafos grandes. Ferramentas que auxiliam na análise e manipulação de grafos podem facilitar o processo, mas muitas vezes são complexas demais ou não oferecem as funcionalidades desejadas. Além disso, a falta de uma ferramenta simples e acessível para análise de grafos através de matrizes de adjacência pode limitar o estudo e aplicação dessa importante área da matemática e da computação.

## Descrição
Este projeto consiste em uma implementação para análise de grafos representados por matrizes de adjacência. O projeto oferece uma variedade de funcionalidades que permitem aos usuários realizar diferentes tipos de análises e operações em grafos, como verificação de simetria, cálculo de grau dos vértices, identificação de vértices de maior grau, entre outros.

## Estruturação do projeto
grafo.h: Definições das funções e estruturas para operações de grafos.
grafo.c: Implementação das funções de operações de grafos.
main.c: Funções auxiliares para leitura e escrita de arquivos, etc.
dados_matriz.txt: Arquivo de exemplo contendo uma matriz de adjacência para teste.

# 2. Módulos utilizados
## grafo.h
Neste módulo, implementamos todas as principais funções referentes à manipulação e análise do grafo.

##  geral.h
Nesse módulo, implementamos o conjunto das funções usandas na interface do menu para a tabela Hash e nas tratativas realizadas.

## Funções em hash.h
### Função importa_matriz
* **Descrição:** Importa uma matriz de adjacência de um arquivo externo.
```c
int **le_matriz(char *nome_arquivo, int **matriz, int *tamanho);
```
### Função mostra_matriz
* **Descrição:** Exibe os valores da matriz na interface
```c
void mostra_matriz(int **matriz, int tamanho);
```
### Função verifica_simetria
* **Descrição:** Verifica se a matriz é simétrica
```c
int verifica_simetria(int **matriz, int tamanho);
```
### Função grau_vertice
* **Descrição:** Retorna o grau de cada vertice
```c
int *grau_vertice(int **matriz, int tamanho);
```
### Função maior_vertice
* **Descrição:** Retona um vetor com os maiores vertices
```c
int *maior_grau(int *grau, int tamanho, int *quantidade_vertices);
```
### Função grau_arquivo
* **Descrição:** Cria um arquivo e escreve qual o grau de cada vertice
```c
void grau_arquivo(int *grau, int tamanho);
```
### Função vertices_isolados
* **Descrição:** Verifica vetor com os vértices isolados, se existir
```c
int *vertices_isolados(int **matriz, int tamanho, int *num_vertices);
```
### Função vertices_multiplos_5
* **Descrição:** Retorna um vetor com os vértices múltiplos de 5.
```c
int *vertices_multiplos_5(int **matriz, int tamanho, int *num_vertices);
```
### Função subgrafo_induzido
* **Descrição:** Gera um subgrafo induzido, a partir dos vértices inseridos.
```c
int **subgrafo_induzido(int **matriz, int *vertices, int tamanho, int tamanho_induzido);
```
### Função salva_grafo
* **Descrição:** Escreve a matriz booleana do grafo em um arquivo.
```c
void salva_grafo(int **matriz_subgrafo, int tamanho, char *nome_arquivo);
```
### Função verifica_clique
* **Descrição:** Testa se a matriz do subgrafo inserido é um clique.
```c
int verifica_clique(int **matriz, int tamanho);
```
### Função copia_vetor
* **Descrição:** Faz a cópia de um vetor, elemento por elemento.
```c
int *copia_vetor(int *vetor_dst, int *vetor_src, int tam_vetor_dst, int tam_vetor_src);
```
### Função candidator_clique
* **Descrição:** Testa todas as possibilidades de cominação entre vértices conectados ao vértice de uma linha, até achar o maior clique.
```c
int *candidatos_clique(int **matriz, int tamanho, int vertice_linha, int vertice_iter, int *tamanho_clique);
```
### Função conexao_primeiro_ultimo
* **Descrição:** Verifica se há um caminho que conecte os vertices escolhidos
```c
int *conexao_vertices(int **matriz, int *vetor_caminho, int tamanho, int vertice_ini, int vertice_fim);
```


## Funções em geral.h
### Função delay
* **Descrição:** Gera um atraso, em milissegundos, na resposta do programa.
```c
void delay(double milissegundos);
```
### Função clear
* **Descrição:** Limpa o terminal de acordo com o SO do usuário.
```c
char *clear(void);
```
### Função cabecalho
* **Descrição:** Adiciona o cabeçalho do menu atual.
```c
void cabecalho(char *pagina, char *titulo, char *num_pag);
```
### Função menu_principal
* **Descrição:** Exibe o menu principal.
```c
int menu_principal(Contato *arr_contatos);
```
### Função teste_input
* **Descrição:** Verifica se o valor é uma string, número positivo ou negativo.
```c
int teste_input(void);
```
### Função teste_formato
* **Descrição:** Verifica o tipo da entrada
```c
int teste_formato(char *str);
```
### Função alert
* **Descrição:** Modifica o código de erro atual do sistema.
```c
void alert(int cod);
```
### Função alert_msg
* **Descrição:** Exibe uma mensagem de erro referente ao código de 
   erro salvo no sistema.
```c
void alert_msg(void);
```
