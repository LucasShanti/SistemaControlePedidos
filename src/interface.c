#include "curses.h"
#include "../include/produto.h"
#include "../include/pedido.h"

extern Produto produtos[100];
extern int totalProdutos;
extern Pedido pedidos[100];
extern int totalPedidos;

void mostrarMenuPrincipal() {
    initscr();
    printw("1 - Produtos\n2 - Pedidos\n0 - Sair\nEscolha: ");
    int opcao = getch();
    endwin();
    switch(opcao) {
        case '1': mostrarMenuProdutos(produtos, &totalProdutos); break;
        case '2': mostrarMenuPedidos(pedidos, &totalPedidos); break;
        case '0': break;
    }
}

void mostrarMenuProdutos(Produto produtos[], int* total) {
    initscr();
    printw("1 - Inserir Produto\n2 - Listar Produtos\n3 - Editar Produto\n4 - Remover Produto\n0 - Voltar\nEscolha: ");
    int opcao = getch();
    endwin();
    switch(opcao) {
        case '1': cadastrarProduto(produtos, *total); break;
        case '2': consultarProduto(produtos, *total); break;
        case '3': listarProduto(produtos, *total); break;
        case '4': removerProduto(produtos, total); break;
        case '0': mostrarMenuPrincipal(); break;
    }
}

void mostrarMenuPedidos() {
    initscr();
    printw("1 - Inserir Pedido\n2 - Listar Pedidos\n3 - Detalhar Pedido\n0 - Voltar\nEscolha: ");
    int opcao = getch();
    endwin();
    switch(opcao) {
        case '1': inserirPedido(); break;
        case '2': listarPedidos(); break;
        case '3': detalharPedido(); break;
        case '0': mostrarMenuPrincipal(); break;
    }
}