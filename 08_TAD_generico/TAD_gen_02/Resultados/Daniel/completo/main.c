#include "gerenciadorpacotes.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

    tGerenciador *geren = CriaGerenciador();

    while(1){

        int op;

        printf("\n");
        printf("Escolha uma opcao:\n(1) Cadastrar um novo pacote\n(2) Imprimir um pacote especifico\n(3) Imprimir todos os pacotes e sair\n");
        scanf("%d\n", &op);

        if (op == 1){

            int tipo, num;

            printf("Digite o tipo (0-char, 1-int) e o numero de elementos do pacote/mensagem: ");
            scanf("%d %d\n", &tipo, &num);

            if (tipo != 0 && tipo != 1){
                printf("Digite um tipo valido!\n");
                continue;
            }

            tPacote *pac= CriaPacote(tipo, num);
            LePacote(pac);
            AdicionaPacoteNoGerenciador(geren, pac);
        }

        if (op == 2){
            int idx;
            scanf("%d\n", &idx);
            ImprimirPacoteNoIndice(geren, idx);
        }

        if (op == 3){
            ImprimirTodosPacotes(geren);
            break;
        }
    }

    DestroiGerenciador(geren);

    return 0;
}