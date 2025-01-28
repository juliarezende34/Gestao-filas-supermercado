#include "src/structs.h"
#include "src/functions.h"

int main(){
    Caixa vetor_caixas[NUM_CAIXAS];
    int op = -1, caixa;

    for(int i = 0; i < NUM_CAIXAS; i++){
        vetor_caixas[i].id = i;
        vetor_caixas[i].estado = true;
        vetor_caixas[i].fila = NULL;
        vetor_caixas[i].nClientes = 0;
    }

    while(op != 0){
        printf("\nDigite a opção desejada:\n[0] Sair\n[1] Cadastrar cliente\n[2] Atender cliente\n[3] Abrir ou fechar caixa\n[4] Imprimir clientes\n[5] Status dos caixas\n>");
        if(scanf("%d", &op) != 1){
            printf("Opção inválida!\n");
            break;
        }
        switch(op){
            case 0:
                system("clear");
            break;

            case 1:
                printf("\nEm qual caixa [1 - %d]?\n>", NUM_CAIXAS);
                scanf("%d", &caixa);
                if(vetor_caixas[caixa-1].estado){
                    inserirFila(&vetor_caixas[caixa-1].fila);
                    vetor_caixas[caixa-1].nClientes++;
                }
                else{
                    printf("\nCaixa fechado!\n");
                }
                system("clear");
            break;

            case 2:
                printf("\nEm qual caixa [1 - %d]?\n>", NUM_CAIXAS);
                scanf("%d", &caixa);
                if(vetor_caixas[caixa-1].estado){
                    removerFila(&vetor_caixas[caixa-1].fila);
                    vetor_caixas[caixa-1].nClientes--;
                    if(vetor_caixas[caixa-1].nClientes < 0){
                        vetor_caixas[caixa-1].nClientes = 0;
                    }
                }
                else{
                    printf("\nCaixa fechado!\n");
                }
            break;

            case 3:
                printf("\nQual caixa [1 - %d]?\n>", NUM_CAIXAS);
                scanf("%d", &caixa);
                mudarEstado(&vetor_caixas[caixa-1], vetor_caixas);
            break;

            case 4:
                for(int i = 0; i < NUM_CAIXAS; i++){
                    printf("\n -------- Caixa %d --------\n", i+1);
                    imprimirFila(vetor_caixas[i].fila);
                }
            break;

            case 5:
                statusCaixas(vetor_caixas);
            break;

            default:
                printf("Opção inválida!\n");
            break;
        }
    }

    return 0;
}