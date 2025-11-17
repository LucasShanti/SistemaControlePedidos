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