#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "cliente.h"

int validarCPF(char* cpf) {
    int i, j, digito1 = 0, digito2 = 0;
    int numeros[11];
    int pos = 0;

    for (i = 0; i < strlen(cpf); i++) {
        if (isdigit(cpf[i])) {
            numeros[pos] = cpf[i] - '0';
            pos++;
        }
    }

    if (pos != 11) {
        return 0; // é falso
    }

    for (i = 0; i < 10; i++) {
        if (numeros[i] != numeros[i+1]) {
            break; // se o número for diferente, o CPF pode ser válido
        }
    }
    if (i == 10) {
        return 0; // se os números forem todos iguais, CPF inválido
    }

    // calculo do primeiro dígito verificador
    for (i = 0, j = 10; i < 9; i++, j--) {
        digito1 += numeros[i] * j;
    }
    digito1 = (digito1 % 11);
    if (digito1 < 2) {
        digito1 = 0;
    } else {
        digito1 = 11 - digito1;
    }

    // calculo do segundo dígito verificador
    for (i = 0, j = 11; i < 10; i++, j--) {
        digito2 += numeros[i] * j;
    }
    digito2 = (digito2 % 11);
    if (digito2 < 2) {
        digito2 = 0;
    } else {
        digito2 = 11 - digito2;
    }

    if (numeros[9] == digito1 && numeros[10] == digito2) {
        return 1; // Verdadeiro (CPF válido)
    } else {
        return 0; // Falso (CPF inválido)
    }
}

int validarCNPJ(char* cnpj) {
    int i, j, digito1 = 0, digito2 = 0;
    int numeros[14];
    int pos = 0;

    for (i = 0; i < strlen(cnpj); i++) {
        if (isdigit(cnpj[i])) {
            numeros[pos] = cnpj[i] - '0';
            pos++;
        }
    }

    if (pos != 14) {
        return 0; // é falso
    }

    for (i = 0; i < 13; i++) {
        if (numeros[i] != numeros[i+1]) {
            break; // se o número for diferente, o CNPJ pode ser válido
        }
    }

    if (i == 13) {
        return 0; // se os números forem todos iguais, CNPJ inválido
    }

    int multiplicador = 5;
    for (i = 0; i < 12; i++) {
        digito1 += numeros[i] * multiplicador;
        multiplicador--;
        if (multiplicador < 2) {
            multiplicador = 9;
        }
    }

    digito1 = (digito1 % 11);
    if (digito1 < 2) {
        digito1 = 0;
    } else {
        digito1 = 11 - digito1;
    }

    multiplicador = 6;
    for (i = 0; i < 13; i++) {
        digito2 += numeros[i] * multiplicador;
        multiplicador--;
        if (multiplicador < 2) {
            multiplicador = 9;
        }
    }

    digito2 = (digito2 % 11);
    if (digito2 < 2) {
        digito2 = 0;
    } else {
        digito2 = 11 - digito2;
    }

    if (numeros[12] == digito1 && numeros[13] == digito2) {
        return 1; // Verdadeiro (CNPJ válido)
    } else {
        return 0; // Falso (CNPJ inválido)
    }
}

int analisarCliente(ListaClientes* lista, int id, char* cpf, char* cnpj) {
    for (int i = 0; i < lista->count; i++) {
        // Verifica duplicidade de ID
        if (lista->clientes[i].id == id) {
            printf("\nERRO: ID %d ja esta em uso!\n", id);
            return 1;
        }

        if (cpf != NULL && lista->clientes[i].tipo == tipo_PF) {
            if (strcmp(lista->clientes[i].dados.pf.cpf, cpf) == 0) {
                printf("\nERRO: CPF %s ja cadastrado!\n", cpf);
                return 1;
            }
        }

        if (cnpj != NULL && lista->clientes[i].tipo == tipo_PJ) {
             if (strcmp(lista->clientes[i].dados.pj.cnpj, cnpj) == 0) {
                printf("\nERRO: CNPJ %s ja cadastrado!\n", cnpj);
                return 1;
            }
        }
    }
    return 0;
}

void cadastrarCliente(ListaClientes* lista) {
    if (lista->count >= MAX_CLIENTES) {
        printf("Erro: Memoria cheia! Não é possivel cadastrar mais clientes.\n");
        return;
    }
    Cliente novoCliente;

    printf("Digite o ID do cliente: ");
    scanf("%d", &novoCliente.id);
    getchar();

    if (analisarCliente(lista, novoCliente.id, NULL, NULL) == 1) {
        return; // Sai da função se o ID já existir
    }

    printf("Digite o Endereco: ");
    scanf(" %[^\n]", novoCliente.endereco);
    getchar();

    printf("Digite o Telefone: ");
    scanf(" %[^\n]", novoCliente.telefone);
    getchar();

    printf("Digite o E-mail: ");
    scanf(" %[^\n]", novoCliente.email);
    getchar();
    
    // Definição do Tipo

    int tipoInput;
    printf("Tipo de Cliente (1 - Fisica, 2 - Juridica): ");
    scanf("%d", &tipoInput);
    getchar();

    if (tipoInput == 1) {
        novoCliente.tipo = tipo_PF;

        printf("Digite o Nome Completo: ");
        scanf(" %[^\n]", novoCliente.dados.pf.nome);
        getchar();

        printf("Digite o Celular: ");
        scanf(" %[^\n]", novoCliente.dados.pf.celular);
        getchar();

        printf("Digite o CPF (Apenas Números): ");
        scanf(" %[^\n]", novoCliente.dados.pf.cpf);
        getchar();

        if (validarCPF(novoCliente.dados.pf.cpf) == 0) {
            printf("\nERRO: CPF invalido!\n");
            return;
        }
        
        if (analisarCliente(lista, 0, novoCliente.dados.pf.cpf, NULL) == 1) {
            return;
        }

    } else if (tipoInput == 2) {
        novoCliente.tipo = tipo_PJ;

        printf("Digite a Razao Social: ");
        scanf(" %[^\n]", novoCliente.dados.pj.razaoSocial);
        getchar();

        printf("Digite o Nome do Contato: ");
        scanf(" %[^\n]", novoCliente.dados.pj.nomeContato);
        getchar();

        printf("Digite o CNPJ (Apenas Números): ");
        scanf(" %[^\n]", novoCliente.dados.pj.cnpj);
        getchar();

        if (validarCNPJ(novoCliente.dados.pj.cnpj) == 0) {
            printf("\nERRO: CNPJ invalido!\n");
            return;
        }

        if (analisarCliente(lista, 0, NULL, novoCliente.dados.pj.cnpj) == 1) {
            return;
        }

    } else {
        printf("\nERRO: Tipo de cliente invalido!\n");
        return;
    }
    
    lista->clientes[lista->count] = novoCliente;
    
    lista->count++;

    printf("\nCliente cadastrado com o ID %d.\n", novoCliente.id);
}

void listarClientes(ListaClientes* lista) {
    if (lista->count == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    for (int i = 0; i < lista->count; i++) {
        Cliente c = lista->clientes[i];
        printf("ID: %d\n", c.id);
        printf("Endereco: %s\n", c.endereco);
        printf("Telefone: %s\n", c.telefone);
        printf("E-mail: %s\n", c.email);

        if (c.tipo == tipo_PF) {
            printf("Tipo: Pessoa Fisica\n");
            printf("Nome: %s\n", c.dados.pf.nome);
            printf("Celular: %s\n", c.dados.pf.celular);
            printf("CPF: %s\n", c.dados.pf.cpf);
        } else if (c.tipo == tipo_PJ) {
            printf("Tipo: Pessoa Juridica\n");
            printf("Razao Social: %s\n", c.dados.pj.razaoSocial);
            printf("Nome do Contato: %s\n", c.dados.pj.nomeContato);
            printf("CNPJ: %s\n", c.dados.pj.cnpj);
        }
    }
}

void consultarCliente(ListaClientes* lista) {
    int idConsulta;
    printf("Digite o ID do cliente para consulta: ");
    scanf("%d", &idConsulta);
    getchar();

    for (int i = 0; i < lista->count; i++) {
        if (lista->clientes[i].id == idConsulta) {
            Cliente c = lista->clientes[i];
            printf("ID: %d\n", c.id);
            printf("Endereco: %s\n", c.endereco);
            printf("Telefone: %s\n", c.telefone);
            printf("E-mail: %s\n", c.email);

            if (c.tipo == tipo_PF) {
                printf("Tipo: Pessoa Fisica\n");
                printf("Nome: %s\n", c.dados.pf.nome);
                printf("Celular: %s\n", c.dados.pf.celular);
                printf("CPF: %s\n", c.dados.pf.cpf);
            } else if (c.tipo == tipo_PJ) {
                printf("Tipo: Pessoa Juridica\n");
                printf("Razao Social: %s\n", c.dados.pj.razaoSocial);
                printf("Nome do Contato: %s\n", c.dados.pj.nomeContato);
                printf("CNPJ: %s\n", c.dados.pj.cnpj);
            }
            return;
        }
    }
    printf("Cliente com ID %d nao encontrado.\n", idConsulta);
}

void removerCliente(ListaClientes* lista) {
    int idRemover;
    printf("Digite o ID do cliente para remover: ");
    scanf("%d", &idRemover);
    getchar();

    for (int i = 0; i < lista->count; i++) {
        if (lista->clientes[i].id == idRemover) {
            for (int j = i; j < lista->count - 1; j++) {
                lista->clientes[j] = lista->clientes[j + 1];
            }
            lista->count--;
            printf("Cliente com ID %d removido com sucesso.\n", idRemover);
            return;
        }
    }
    printf("Cliente com ID %d nao encontrado.\n", idRemover);
}