#include "../grafo/grafo.h"

/* Funções Exportadas */

/* Função delay
 - Gera um atraso, em milissegundos, na resposta do 
   programa.
*/
void delay(double milissegundos);

/* Função clear
 - Limpa o terminal de acordo com o SO do usuário.
*/
char *clear(void);

/* Função cabecalho
 - Adiciona o cabeçalho do menu atual.
*/
void cabecalho(char *pagina, char *titulo, char *num_pag);

/* Função menu_principal 
 - Exibe o menu principal.
*/
int menu_principal(int **matriz, int tamanho);

/* Função menu_voltar
 - Aguarda até o usuário apertar ENTER para voltar ao menu anterior.
*/
int menu_voltar();

/* Função teste_input
 - Verifica se o valor é uma string, número positivo ou   
   negativo.
*/
int teste_input(void);

/* Função alert
 - Modifica o código de erro atual do sistema.
*/
void alert(int cod);

/* Função alert_msg
 - Exibe uma mensagem de erro referente ao código de 
   erro salvo no sistema.
*/
void alert_msg(void);

