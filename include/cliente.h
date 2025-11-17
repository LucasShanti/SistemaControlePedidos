#ifndef cliente_h //se a variável cliente_h já foi definida, vai direto pro endif
#define cliente_h

typedef struct {
    char nome[100];
    char cpf[15];
    char celular[20];
} PessoaFisica;
typedef struct {
    char razaoSocial[150];
    char cnpj[19];
    char nomeContato[100];
} PessoaJuridica;

typedef enum {
    tipo_PF, // valor 0
    tipo_PJ // valor 1
} TipoCliente; //é só pra definir os tipos de cliente

typedef struct {
    int id;
    char endereco[200];
    char telefone[20];
    char email[100];

    TipoCliente tipo; // indica se é PF ou PJ

    union {
        PessoaFisica pf;
        PessoaJuridica pj;
    } dados;

} Cliente;

int validarCPF(char* cpf); //função para validar CPF (cliente.c)
int validarCNPJ(char* cnpj); //função para validar CNPJ (cliente.c)

void cadastrarCliente();
void consultarCliente();
void removerCliente();
void listarClientes();
void analisarCliente(); //CRUD


#endif 