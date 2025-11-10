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