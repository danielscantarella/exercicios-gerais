#include "banco.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Cria um novo banco, com 5 contas alocadas e nenhuma conta aberta.
 * Se não for possível alocar memória, o programa é encerrado.
 * 
 * @return Um ponteiro para o novo banco criado.
 */
tBanco *CriaBanco(){
    tBanco *b = (tBanco*) malloc (sizeof(tBanco));
    b->contasAlocadas = 5;
    b->contas = (tConta**) malloc (b->contasAlocadas * sizeof(tConta*));
    b->qtdContas = 0;
    return b;
}

/**
 * @brief Desaloca a memória de um banco e de todas as suas contas.
 * 
 * @param banco Ponteiro para o banco a ser destruído.
 */
void DestroiBanco(tBanco *banco){
    for (int i=0; i<banco->qtdContas; i++){
        DestroiConta(banco->contas[i]);
    }
    free(banco->contas);
    free(banco);
}

/**
 * @brief Abre uma nova conta no banco e a adiciona ao vetor de contas.
 * 
 * @param banco Ponteiro para o banco onde a conta será aberta.
 */
void AbreContaBanco(tBanco *banco){
    if (banco->qtdContas >= banco->contasAlocadas){
        banco->contas = (tConta**) realloc (banco->contas, (banco->contasAlocadas+1) * sizeof(tConta*));
        banco->contasAlocadas += 1;
    }
    banco->contas[banco->qtdContas] = CriaConta();
    LeConta(banco->contas[banco->qtdContas]);
    banco->qtdContas++;
}

/**
 * @brief Realiza um saque em uma conta do banco se ela existir e tiver saldo suficiente.
 * 
 * @param banco Ponteiro para o banco onde a conta será sacada.
 */
void SaqueContaBanco(tBanco *banco){
    int numConta;
    float valor;
    scanf("%d %f", &numConta, &valor);

    for (int i=0; i<banco->qtdContas; i++){
        if (VerificaConta(banco->contas[i], numConta)){
            SaqueConta(banco->contas[i], valor);
        }
    }
}

/**
 * @brief Realiza um depósito em uma conta do banco se ela existir.
 * 
 * @param banco Ponteiro para o banco onde a conta será depositada.
 */
void DepositoContaBanco(tBanco *banco){
    int numConta;
    float valor;
    scanf("%d %f", &numConta, &valor);

    for (int i=0; i<banco->qtdContas; i++){
        if (VerificaConta(banco->contas[i], numConta)){
            DepositoConta(banco->contas[i], valor);
        }
    }
}

/**
 * @brief Realiza uma transferência entre duas contas do banco se elas existirem e a conta de origem tiver saldo suficiente.
 * 
 * @param banco Ponteiro para o banco onde as contas estão.
 */
void TransferenciaContaBanco(tBanco *banco){
    int origem, destino;
    float valor;
    scanf("%d %d %f", &destino, &origem, &valor);

    for (int i=0; i<banco->qtdContas; i++){
        if (VerificaConta(banco->contas[i], origem)){
            for (int j=0; j<banco->qtdContas; j++){
                if (VerificaConta(banco->contas[j], destino)){
                    TransferenciaConta(banco->contas[j], banco->contas[i], valor);
                }
            }
        }
    }
}

/**
 * @brief Imprime o relatório do banco, com todas as contas e seus respectivos dados.
 * 
 * @param banco Ponteiro para o banco a ser impresso.
 */
void ImprimeRelatorioBanco(tBanco *banco){
    printf("===| Imprimindo Relatorio |===\n");
    for (int i=0; i<banco->qtdContas; i++){
        ImprimeConta(banco->contas[i]);
    }
}