#ifndef STRUCTS_H
#define STRUCTS_H

#define NUM_CAIXAS 5

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cliente{
    char nome[100];
    int cpf, prioridade, nItens;
    struct Cliente * proximo;
} Cliente;

typedef struct Caixa{
    int id, nClientes;
    bool estado;
    Cliente * fila;
} Caixa;

extern int caixasAbertos;

#endif