#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"



int analisarProdutoCADASTRO(Produto produtos[], int total, const char* codigo) {
    for (int i = 0; i < total; i++) {
        if (strcmp(produtos[i].codigo, codigo) == 0) {
            return i;
        }
    }
    return -1; // o codigo do produto nao existe
}

int carregarProdutos(Produto produtos[]) {
    FILE *arquivo = fopen("data/Produtos.csv", "r");
    int total = 0;
    char linha[300];


fgets(linha, sizeof(linha), arquivo);

while (fgets(linha, sizeof(linha), arquivo) != NULL && total < 100) {
    linha[strcspn(linha, "\n")] = 0;
    
    // Separa os dados utilizando strtok(ele delimita os caracteres)
    char *token = strtok(linha, ",");
    if (token != NULL) strcpy(produtos[total].codigo, token);
    
    token = strtok(NULL, ",");
    if (token != NULL) strcpy(produtos[total].descricao, token);
    
    token = strtok(NULL, ",");
    if (token != NULL) produtos[total].preco = atof(token);
    
    token = strtok(NULL, ",");
    if (token != NULL) produtos[total].estoque = atoi(token);
    
    total++;
}

fclose(arquivo);
return total;
}

void salvarProdutos(Produto produtos[], int total) {
    FILE *arquivo = fopen("data/Produtos.csv", "w");
    
    
    fprintf(arquivo, "codigo,descricao,preco,estoque\n");
    
    for (int i = 0; i < total; i++) {
        fprintf(arquivo, "%s,%s,%.2f,%d\n", 
                produtos[i].codigo, 
                produtos[i].descricao, 
                produtos[i].preco, 
                produtos[i].estoque);
    }
    
    fclose(arquivo);
}