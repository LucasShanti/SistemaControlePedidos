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

