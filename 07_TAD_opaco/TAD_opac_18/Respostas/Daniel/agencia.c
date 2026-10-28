#include <stdio.h>
#include <stdlib.h>
#include "operacao.h"
#include "agencia.h"

struct Agencia{
    tConta **contas;
    int qtdContas;
    tOperacao **op;
    int qtdOp;
};

/**
 * @brief Cria uma variável (alocada dinamicamente) do tipo tAgencia. Ponteiros devem ser inicializados com NULL e variáveis numéricas com valor zero.
 *
 * @return A variável do tipo Agencia inicializada.
 */
tAgencia* CriaAgencia(){
    tAgencia *a = (tAgencia*) malloc (sizeof(tAgencia));
    a->contas =  NULL;
    a->op = NULL;
    a->qtdContas = 0;
    a->qtdOp = 0;
    return a;
}

/**
 * @brief Libera toda a memória alocada para armazenar dados de uma agencia.
 *
 * @param A variável do tipo Agencia que será apagada.
 */
void DestroiAgencia(tAgencia* agencia){
    for (int i=0; i<agencia->qtdContas; i++){
        DestroiConta(agencia->contas[i]);
    }
    free(agencia->contas);

    for (int i=0; i<agencia->qtdOp; i++){
        DestroiOperacao(agencia->op[i]);
    }
    free(agencia->op);

    free (agencia);
}

/**
 * @brief Le as informações de uma agencia - contas e operações, no formato especificado no roteiro. 
 * Assim como imprime as possíveis mensagens de erro para essa ação.
 *
 * @param agencia - A variável do tipo agencia que salvará os dados lidos
 */
void LeOperacoes(tAgencia *agencia){

    scanf("%d\n", &agencia->qtdContas);

    free (agencia->contas);
    agencia->contas = (tConta**)  calloc (agencia->qtdContas, sizeof(struct Conta*));
    int id;
    for (int i=0; i<agencia->qtdContas; i++){
        scanf("%d\n", &id);
        if (id > 0){
            if (BuscaContaPorId(agencia, id) != NULL){
                printf("\nEste id ja esta cadastrado na agencia. Digite um id diferente!");
                i--;
                continue;
            }
            agencia->contas[i] = CriaConta(id);
        } else{
            printf("\nDigite um id valido para a conta a ser cadastrada!");
            i--;
        }
    }

    scanf("%d\n", &agencia->qtdOp);

    free(agencia->op);
    agencia->op = (tOperacao**) calloc (agencia->qtdOp, sizeof(struct Operacao*));
    float valor;
    
    for (int i=0; i<agencia->qtdOp; i++){
        scanf("%d %f\n", &id, &valor);

        for (int j=0; j<agencia->qtdContas; j++){
            if  (agencia->contas[j] != NULL && ConfereIdConta(agencia->contas[j], id )){
                agencia->op[i] = CriaOperacao(agencia->contas[j], valor);
                AlteraSaldoConta(agencia->contas[j], valor);
                break;
            }
        }
    }
}

/**
 * @brief Busca uma conta na agencia que possui um id específico
 *
 * @param agencia - A agencia na qual queremos buscar a conta com o id específico
 * @param id - o ID da conta que queremos buscar
 *conferido
 * @return A conta, caso exista, e NULL, caso contrário
 */
tConta* BuscaContaPorId(tAgencia *agencia, int id){
    for (int i=0; i<agencia->qtdContas; i++){
        if (agencia->contas[i] != NULL && RetornaIdConta(agencia->contas[i]) == id){
            return agencia->contas[i];
        }
    }
    return NULL;
}

/**
 * @brief Função que imprime em tela as operações suspeitas de uma agência
 *
 * @param agencia A Agência na qual as operações suspeitas serão impressas em tela.
 */
void ImprimeOperacoesSuspeitas(tAgencia* agencia){

    printf("\nA lista de operações suspeitas:");
    for (int i=0; i<agencia->qtdOp; i++){
        if (agencia->op[i] == NULL){
            continue;
        }
        if (ConsultaValorOperacao(agencia->op[i]) > 20000 || ConsultaValorOperacao(agencia->op[i]) < -20000){
            ImprimeOperacao(agencia->op[i]);
        }
    }
}

/**
 * @brief Função que imprime em tela os dois correntistas com maior saldo
 *
 * @param agencia A Agência na qual os dois correntistas com maior saldo impressos em tela.
 */
void ImprimeDoisCorrentistasComMaiorSaldo(tAgencia* agencia){
    int primeiro = -1, segundo = -1;

    for (int i=0; i<agencia->qtdContas; i++){

        if (agencia->contas[i] == NULL){
            continue;
        }

        if (primeiro == -1 || RetornaSaldoConta(agencia->contas[i]) > RetornaSaldoConta(agencia->contas[primeiro])){
            segundo = primeiro;
            primeiro = i;
        } else if (segundo == -1 || RetornaSaldoConta(agencia->contas[i]) > RetornaSaldoConta(agencia->contas[segundo])){
            segundo = i;
        }
    }

    printf("\nOs dois correntistas com maior saldo são:");
    if (primeiro != -1){
        printf("\nId: %d, Saldo: %.2f", RetornaIdConta(agencia->contas[primeiro]), RetornaSaldoConta(agencia->contas[primeiro]));
    }
    if (segundo != -1){
        printf("\nId: %d, Saldo: %.2f", RetornaIdConta(agencia->contas[segundo]), RetornaSaldoConta(agencia->contas[segundo]));
    }
}

/**
 * @brief Função que imprime em tela o saldo total da agência
 *
 * @param agencia A Agência na qual o saldo total impresso em tela.
 */
void ImprimeSaldoTotal(tAgencia* agencia){
    float total = 0;
    for (int i=0; i<agencia->qtdContas; i++){
        if (agencia->contas[i] != NULL)  total += RetornaSaldoConta(agencia->contas[i]);
    }
    printf("\nO saldo total da agencia eh: %.2f", total);
}