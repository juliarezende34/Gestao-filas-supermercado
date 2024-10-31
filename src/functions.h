#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structs.h"

// Declaração das funções
Cliente* criarItem();
void inserirFila(Cliente ** fila);
void inserirFilaComNovo(Cliente ** fila, Cliente * novo);
void removerFila(Cliente ** fila);
void imprimirFila(Cliente * fila);
void statusCaixas(Caixa * vetor);
void mudarEstado(Caixa *caixa, Caixa *vetorCaixas);

#endif