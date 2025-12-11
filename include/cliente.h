#ifndef CLIENTE_H
#define CLIENTE_H

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

typedef struct {
    int id;
    char nome  [100];
    char endereco [100];
    char telefone [20];
    int tipo;
    PessoaFisica pf;
    PessoaJuridica pj;
} Cliente;

#endif
