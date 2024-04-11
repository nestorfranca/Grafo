#include <stdio.h>

#define tamanho 3782
void lerarquivo (const char *dados_matriz){
    FILE *arquivo;
    char linha[tamanho];

    arquivo =fopen(dados_matriz, "r");

    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo \n");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL){
        printf ("%s", linha);

    }

    fclose(arquivo);

    
}

int main(void){

    
    lerarquivo ("dados_matriz.txt");
    return 0;

}