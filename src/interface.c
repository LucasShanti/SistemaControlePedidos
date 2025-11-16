#include "curses.h"
#include "produto.h"
#include "pedido.h"

void mostrarMenuPrincipal() {
    initscr();
    printw("1 - Produtos\n2 - Pedidos\n0 - Sair\nEscolha: ");
    int opcao = getch();
    endwin();
    switch(opcao) {
        case '1': mostrarMenuProdutos(); break;
        case '2': mostrarMenuPedidos(); break;
        case '0': break;
    }
}

void mostrarMenuProdutos() {
    initscr();
    printw("1 - Inserir Produto\n2 - Listar Produtos\n3 - Editar Produto\n4 - Remover Produto\n0 - Voltar\nEscolha: ");
    int opcao = getch();
    endwin();
    switch(opcao) {
        case '1': inserirProduto(); break;
        case '2': listarProdutos(); break;
        case '3': editarProduto(); break;
        case '4': removerProduto(); break;
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