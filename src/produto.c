#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/produto.h"
#include "../include/pedido.h"



int analisarProdutoCADASTRO(Produto produtos[], int total, const char* codigo) {
    for (int i = 0; i < total; i++) {
        if (strcmp(produtos[i].codigo, codigo) == 0) {
            return i;
        }
    }
    return -1; // o codigo do produto nao existe
}


int analisarProdutoCONSULTA(Produto produtos[], int total, const char* codigo) {
    return analisarProdutoCADASTRO(produtos, total, codigo); // Verifica apenas existência
}


int analisarProdutoREMOCAO(Produto produtos[], int total, const char* codigo) {
    int indice = analisarProdutoCADASTRO(produtos, total, codigo);
    if (indice == -1) return -1;

    
    Pedido pedidos[100];
    ItemPedido itens[200];
    int totalPedidos = 0; 
    int totalItens = 0; 

    for (int i = 0; i < totalItens; i++) {
        if (itens[i].produtoid == atoi(produtos[indice].codigo)) {
            return -2; // Produto está em pedidos
        }
    }
    return indice;
}


void consultarProduto(Produto produtos[], int total) {
    char codigo[20];
    printf("Informe o código do produto: ");
    scanf("%s", codigo);

    int indice = analisarProdutoCONSULTA(produtos, total, codigo);
    if (indice == -1) {
        printf("Erro: Produto não existe.\n");
        return;
    }

    printf("Dados do produto: \n");
    printf("Código: %s\n", produtos[indice].codigo);
    printf("Descrição: %s\n", produtos[indice].descricao);
    printf("Preço: %.2f\n", produtos[indice].preco);
    printf("Estoque: %d\n", produtos[indice].estoque);
}


void removerProduto(Produto produtos[], int* total) {
    char codigo[20];
    char confirma[3];
    printf("Informe o código do produto: ");
    scanf("%s", codigo);

    int resultado = analisarProdutoREMOCAO(produtos, *total, codigo);
    if (resultado == -1) {
        printf("Erro: Produto não existe.\n");
        return;
    }
    if (resultado == -2) {
        printf("Erro: Produto não pode ser excluído (consta em pedidos).\n");
        return;
    }

    printf("Deseja confirmar a exclusão? (sim/não): ");
    scanf("%s", confirma);
    if (strcmp(confirma, "sim") != 0) {
        printf("Exclusão cancelada.\n");
        return;
    }

    // Remover produto do array
    for (int i = resultado; i < *total - 1; i++) {
        produtos[i] = produtos[i + 1];
    }
    (*total)--;
    salvarProdutos(produtos, *total);
    printf("Produto removido com sucesso.\n");
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
int main() {
    return 0;
}
