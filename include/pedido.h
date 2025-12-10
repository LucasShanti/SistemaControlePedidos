#ifndef PEDIDO_H
#define PEDIDO_H

typedef struct {
    int id;
    int clienteid;
    char data [11];
    double total;
} Pedido;

typedef struct {
    int pedidoid;
    int produtoid;
    int quantidade;
    double subtotal;
} ItemPedido;

int carregarPedidos(Pedido pedidos[]);
void salvarPedidos(Pedido pedidos[], int total);
void inserirPedido();
void listarPedidos();
void detalharPedido();

#endif
