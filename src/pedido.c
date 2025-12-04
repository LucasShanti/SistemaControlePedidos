#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/curses.h"
#include "../include/pedido.h"
#include "../include/produto.h"

extern Produto produtos[100];
extern int totalProdutos;
extern Pedido pedidos[100];
extern int totalPedidos;

int buscarPedidoPorId(Pedido arr[], int total, int id) {
    for (int i = 0; i < total; i++) {
        if (arr[i].id == id) return i;
    }
    return -1;
}

int carregarPedidos(Pedido arr[]) {
    FILE *arquivo = fopen("data/Pedidos.csv", "r");
    if (!arquivo) return 0;
    int total = 0;
    char linha[256];
    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        fclose(arquivo);
        return 0;
    }
    while (fgets(linha, sizeof(linha), arquivo) && total < 100) {
        linha[strcspn(linha, "\n")] = 0;
        char *token = strtok(linha, ",");
        if (!token) break;
        arr[total].id = atoi(token);
        token = strtok(NULL, ",");
        if (!token) break;
        arr[total].clienteid = atoi(token);
        token = strtok(NULL, ",");
        if (!token) break;
        strncpy(arr[total].data, token, sizeof(arr[total].data));
        arr[total].data[sizeof(arr[total].data) - 1] = '\0';
        token = strtok(NULL, ",");
        if (!token) break;
        arr[total].total = atof(token);
        total++;
    }
    fclose(arquivo);
    return total;
}

void salvarPedidos(Pedido arr[], int total) {
    FILE *arquivo = fopen("data/Pedidos.csv", "w");
    if (!arquivo) return;
    fprintf(arquivo, "id,clienteid,data,total\n");
    for (int i = 0; i < total; i++) {
        fprintf(arquivo, "%d,%d,%s,%.2f\n", arr[i].id, arr[i].clienteid, arr[i].data, arr[i].total);
    }
    fclose(arquivo);
}

static int analisarCliente(int clienteid) {
    if (clienteid > 0) return 1;
    return -1;
}

void inserirPedido() {
    initscr();
    echo();
    totalPedidos = carregarPedidos(pedidos);
    char buffer[128];
    int id;
    printw("Codigo do Pedido: ");
    refresh();
    getnstr(buffer, sizeof(buffer) - 1);
    id = atoi(buffer);
    if (buscarPedidoPorId(pedidos, totalPedidos, id) != -1) {
        printw("\nERRO: Codigo de pedido ja existe\n");
        printw("Pressione qualquer tecla...");
        refresh();
        getch();
        endwin();
        return;
    }
    int clienteid;
    printw("Codigo do Cliente: ");
    refresh();
    getnstr(buffer, sizeof(buffer) - 1);
    clienteid = atoi(buffer);
    if (analisarCliente(clienteid) == -1) {
        printw("\nERRO: Cliente nao existe\n");
        printw("Pressione qualquer tecla...");
        refresh();
        getch();
        endwin();
        return;
    }
    char data[16];
    printw("Data (YYYY-MM-DD): ");
    refresh();
    getnstr(data, sizeof(data) - 1);
    int qtdItens;
    printw("Quantidade de itens: ");
    refresh();
    getnstr(buffer, sizeof(buffer) - 1);
    qtdItens = atoi(buffer);
    double total = 0.0;
    for (int i = 0; i < qtdItens; i++) {
        char codigo[32];
        int quant;
        printw("Codigo do Produto #%d: ", i + 1);
        refresh();
        getnstr(codigo, sizeof(codigo) - 1);
        int idx = analisarProdutoCONSULTA(produtos, totalProdutos, codigo);
        if (idx == -1) {
            printw("\nERRO: Produto nao existe\n");
            printw("Pressione qualquer tecla...");
            refresh();
            getch();
            endwin();
            return;
        }
        printw("Quantidade: ");
        refresh();
        getnstr(buffer, sizeof(buffer) - 1);
        quant = atoi(buffer);
        double subtotal = quant * produtos[idx].preco;
        total += subtotal;
        produtos[idx].estoque -= quant;
        if (produtos[idx].estoque < 0) produtos[idx].estoque = 0;
    }
    salvarProdutos(produtos, totalProdutos);
    pedidos[totalPedidos].id = id;
    pedidos[totalPedidos].clienteid = clienteid;
    strncpy(pedidos[totalPedidos].data, data, sizeof(pedidos[totalPedidos].data));
    pedidos[totalPedidos].data[sizeof(pedidos[totalPedidos].data) - 1] = '\0';
    pedidos[totalPedidos].total = total;
    totalPedidos++;
    salvarPedidos(pedidos, totalPedidos);
    printw("\nPedido cadastrado\n");
    printw("Pressione qualquer tecla...");
    refresh();
    getch();
    endwin();
}

void listarPedidos() {
    initscr();
    totalPedidos = carregarPedidos(pedidos);
    if (totalPedidos == 0) {
        printw("Nenhum pedido cadastrado\n");
    } else {
        for (int i = 0; i < totalPedidos; i++) {
            printw("ID: %d\n", pedidos[i].id);
            printw("Cliente: %d\n", pedidos[i].clienteid);
            printw("Data: %s\n", pedidos[i].data);
            printw("Total: R$ %.2f\n\n", pedidos[i].total);
        }
    }
    printw("Pressione qualquer tecla...");
    refresh();
    getch();
    endwin();
}

void detalharPedido() {
    initscr();
    echo();
    totalPedidos = carregarPedidos(pedidos);
    char buffer[64];
    printw("Informe o ID do pedido: ");
    refresh();
    getnstr(buffer, sizeof(buffer) - 1);
    int id = atoi(buffer);
    int idx = buscarPedidoPorId(pedidos, totalPedidos, id);
    if (idx == -1) {
        printw("\nPedido nao encontrado\n");
        printw("Pressione qualquer tecla...");
        refresh();
        getch();
        endwin();
        return;
    }
    printw("\nID: %d\n", pedidos[idx].id);
    printw("Cliente: %d\n", pedidos[idx].clienteid);
    printw("Data: %s\n", pedidos[idx].data);
    printw("Total: R$ %.2f\n", pedidos[idx].total);
    printw("\nPressione qualquer tecla...");
    refresh();
    getch();
    endwin();
}
