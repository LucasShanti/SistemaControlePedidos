#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include "../include/produto.h"
#include "../include/pedido.h"
#include "../include/interface.h"

Produto produtos[100]; 
int totalProdutos = 0;

Pedido pedidos[100];
int totalPedidos = 0;

int main()
{
    totalProdutos = carregarProdutos(produtos);
    initscr();
    mostrarMenuPrincipal();
    endwin();
    return 0;
}