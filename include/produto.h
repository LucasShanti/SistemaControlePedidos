#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char codigo[20];
    char descricao[100];
    float preco;
    int estoque;
} Produto;

int carregarProdutos(Produto produtos[]);
void salvarProdutos(Produto produtos[], int total);
int analisarProdutoCONSULTA(Produto produtos[], int total, const char* codigo);
int analisarProdutoREMOCAO(Produto produtos[], int total, const char* codigo);
void consultarProduto(Produto produtos[], int total);
void removerProduto(Produto produtos[], int* total);

