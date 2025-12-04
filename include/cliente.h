#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct {
    char cpf[15];
    char nome[50];
    char dataNascimento[11];
} PessoaFisica;

typedef struct {
    char cnpj[20];
    char razaoSocial[50];
    char nome [20];
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
