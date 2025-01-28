#include "functions.h"

int caixasAbertos = NUM_CAIXAS;

Cliente* criarItem(){
    Cliente *novo = malloc(sizeof(Cliente));
    char nome[100];
    int cpf, prioridade, nItens;

    printf("Digite o nome:\n>");
    getchar();
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';
    printf("Digite o CPF:\n>");
    scanf("%d", &cpf);
    printf("Digite a prioridade:\n[1] Alta | [2] Média | [3] Baixa | [10] Sem prioridade\n>");
    scanf("%d", &prioridade);
    printf("Digite a quantidade de itens no carrinho:\n>");
    scanf("%d", &nItens);

    novo->cpf = cpf;
    novo->nItens = nItens;
    strcpy(novo->nome, nome);
    novo->prioridade = prioridade;
    novo->proximo = NULL;

    return novo;
}

void inserirFila(Cliente ** fila){ //Passar com &
    Cliente *aux, *novo = criarItem();    

    if(novo){
        if((*fila == NULL) || ((*fila)->prioridade) > novo->prioridade){
            novo->proximo = *fila;
            *fila = novo;
        }
        else{
            aux = *fila;
            while((aux->proximo != NULL) && aux->proximo->prioridade <= novo->prioridade){
                aux = aux->proximo;
            }
            novo->proximo = aux->proximo;
            aux->proximo = novo;
        }
    }
}

void inserirFilaComNovo(Cliente ** fila, Cliente * novo){ 
    Cliente *aux;    
    novo->proximo = NULL;

    if(novo){
        if((*fila == NULL) || ((*fila)->prioridade) > novo->prioridade){
            novo->proximo = *fila;
            *fila = novo;
        }
        else{
            aux = *fila;
            while((aux->proximo != NULL) && aux->proximo->prioridade <= novo->prioridade){
                aux = aux->proximo;
            }
            novo->proximo = aux->proximo;
            aux->proximo = novo;
        }
    }
}

void removerFila(Cliente ** fila){ 
    if(*fila == NULL){
        printf("A fila está vazia!\n");
    }
    else{
        *fila = (*fila)->proximo;
    }
}

void imprimirFila(Cliente * fila){
    Cliente * aux = fila;
    int cont = 1;
    while(aux != NULL){
        printf("Posição: %d | Nome: %s | CPF: %d | Prioridade: %d | Itens no carrinho: %d\n", cont, aux->nome, aux->cpf, aux->prioridade, aux->nItens);
        aux = aux->proximo;
        cont++;
    }
    printf("\n");
}

void statusCaixas(Caixa * vetor){
    char status[5];
    printf("\n");
    for(int i = 0; i < NUM_CAIXAS; i++){
        if(vetor[i].estado){
            strcpy(status, "Sim");
        }
        else{
            strcpy(status, "Não");
        }
        printf("Caixa %d | Aberto? %s | Clientes em espera: %d\n", i+1, status, vetor[i].nClientes);
    }
}

void mudarEstado(Caixa *caixa, Caixa *vetorCaixas) {
    if (caixa->estado == false) {
        caixa->estado = true;
        printf("\nCaixa %d aberto!\n", caixa->id+1);
        caixasAbertos++;
        if(caixasAbertos > NUM_CAIXAS){
            caixasAbertos = NUM_CAIXAS;
        }
    } 
    else {
        if(caixasAbertos == 1){
            printf("\nPelo menos 1 caixa deve permanecer aberto!\n");
        }
        else{
            if (caixa->nClientes == 0) {
                caixa->estado = false;
                printf("\nCaixa %d fechado!\n", caixa->id+1);
            } 
            else {
                // Encontrar a caixa com menos clientes
                int nCaixa, menor = 100000;
                for (int i = 0; i < NUM_CAIXAS; i++) {
                    if ((vetorCaixas[i].nClientes < menor) && (vetorCaixas[i].estado) && (i != caixa->id)) {
                        nCaixa = i;
                        menor = vetorCaixas[i].nClientes;
                    }
                }

                // Realocar clientes
                Cliente *aux = caixa->fila;
                Cliente *temp;

                while (aux != NULL) {
                    temp = aux;  // Guardar o cliente atual para liberar depois
                    aux = aux->proximo;  // Avançar para o próximo cliente

                    // Inserir cliente na nova fila
                    inserirFilaComNovo(&vetorCaixas[nCaixa].fila, temp);
                    vetorCaixas[nCaixa].nClientes++;
                }

                // Limpar a fila original
                caixa->fila = NULL;
                caixa->nClientes = 0;
                caixa->estado = false;

                printf("\nClientes realocados para o caixa %d!\n", nCaixa + 1);
                printf("\nCaixa %d fechado!\n", caixa->id+1);
            }
            caixasAbertos--;
        }
    }
}
