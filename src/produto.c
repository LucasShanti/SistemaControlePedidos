#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/produto.h"
#include "../include/pedido.h"
#include <curses.h>
void cadastrarProduto(Produto produtos[], int* total) {
    char codigo[20];
    char descricao[100];
    float preco;
    int estoque;
    
    initscr();
    echo();
    
    
    printw("Codigo: ");
    refresh();
    getstr(codigo);
    
    // Verifica se o código já existe
    if (analisarProdutoCADASTRO(produtos, *total, codigo) != -1) {
        printw("\nERRO: Codigo ja existe!\n");
        printw("Pressione qualquer tecla...");
        refresh();
        getch();
        endwin();
        return;
    }
    
    
    printw("Descricao: ");
    refresh();
    getstr(descricao);
    
    printw("Preco: ");
    refresh();
    scanw("%f", &preco);
    
    printw("Estoque: ");
    refresh();
    scanw("%d", &estoque);
    
    
    strcpy(produtos[*total].codigo, codigo);
    strcpy(produtos[*total].descricao, descricao);
    produtos[*total].preco = preco;
    produtos[*total].estoque = estoque;
    (*total)++;
    
    
    salvarProdutos(produtos, *total);
    
    printw("\nProduto cadastrado!\n");
    printw("Pressione qualquer tecla...");
    refresh();
    getch();
    endwin();
}

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
    printw("Informe o código do produto: ");
    refresh();
    scanw("%s", codigo);

    int indice = analisarProdutoCONSULTA(produtos, total, codigo);
    if (indice == -1) {
        printw("Erro: Produto não existe.\n");
        return;
    }

    printw("Dados do produto: \n");
    printw("Código: %s\n", produtos[indice].codigo);
    printw("Descrição: %s\n", produtos[indice].descricao);
    printw("Preço: %.2f\n", produtos[indice].preco);
    printw("Estoque: %d\n", produtos[indice].estoque);
    refresh();
}


void removerProduto(Produto produtos[], int* total) {
    char codigo[20];
    char confirma[3];
    printw("Informe o código do produto: ");
    scanf("%s", codigo);

    int resultado = analisarProdutoREMOCAO(produtos, *total, codigo);
    if (resultado == -1) {
        printw("Erro: Produto não existe.\n");
        return;
    }
    if (resultado == -2) {
        printw("Erro: Produto não pode ser excluído (consta em pedidos).\n");
        return;
    }

    printw("Deseja confirmar a exclusão? (sim/não): ");
    scanw("%s", confirma);
    if (strcmp(confirma, "sim") != 0) {
        printw("Exclusão cancelada.\n");
        return;
    }

    // Remover produto do array
    for (int i = resultado; i < *total - 1; i++) {
        produtos[i] = produtos[i + 1];
    }
    (*total)--;
    salvarProdutos(produtos, *total);
    printw("Produto removido com sucesso.\n");
    refresh();
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

void listarProduto(Produto produtos[], int total) {
    initscr();
    
    if (total == 0) {
        printw("Nenhum produto cadastrado.\n");
    } else {
        for (int i = 0; i < total; i++) {
            printw("Codigo: %s\n", produtos[i].codigo);
            printw("Descricao: %s\n", produtos[i].descricao);
            printw("Preco: R$ %.2f\n", produtos[i].preco);
            printw("Estoque: %d\n", produtos[i].estoque);
            printw("\n");
        }
    }
    
    printw("Pressione qualquer tecla...");
    refresh();
    getch();
    endwin();
}