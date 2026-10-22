#include <stdio.h>
#include <stdlib.h>
#include "cidade.h"
#include "defesa.h"
#include "missil.h"

/**
 * @brief Estrutura que representa uma cidade.
 * 
 * A estrutura tCidade contém o nome da cidade, a quantidade de mísseis e defesas, e as listas de mísseis e defesas.
 * 
 */
struct cidade{
    char *nome;
    int qtdMissil, qtdDefesa;
    float x, y;
    tMissil *listaMisseis;
    tDefesa *listaDefesas;
    float danoTotal, danoRecebido;
};

/**
 * @brief Lê os limites da cidade da entrada padrão e cria uma nova cidade.
 * 
 * @return tCidade Ponteiro para a cidade criada.
 */
tCidade CriaCidade(){

    tCidade c = (tCidade) malloc (sizeof(struct cidade));
    c->nome = (char *) calloc (MAX_NOME,  sizeof(char));
    scanf("%s %f %f", c->nome, &c->x, &c->y);
    c->qtdDefesa = 0;
    c->qtdMissil = 0;
    c->danoRecebido = 0;
    c->danoTotal = 0;
    c->listaDefesas = (tDefesa*) calloc (QTD_DEF, sizeof(tDefesa*));
    c->listaMisseis = (tMissil*) calloc (QTD_MIS, sizeof(tMissil*));
    return c;
}

/**
 * @brief Lê defesas e mísseis da entrada padrão e os acrescenta à cidade. 
 * Além disso, essa função também é responsável por ler o último caractere da entrada.
 * 
 * @param cidade Ponteiro para a cidade que será preenchida.
 * @return tCidade Ponteiro para a cidade preenchida.
 */
tCidade LeEntrada(tCidade cidade){

    while (1){
        char op;

        scanf("%c", &op);

        if (op == ENCERRAR){
            break;
        }

        else if (op == DEFESA){

            if (cidade->qtdDefesa >= QTD_DEF){
                printf("MAX DE DEFESAS CADASTRADAS!\n");
                return cidade;
            }

            cidade->listaDefesas[cidade->qtdDefesa] = LeDefesa();
            cidade->qtdDefesa++;
        }

        else if (op == MISSIL){

            if (cidade->qtdMissil >= QTD_MIS){
                printf("MAX DE MISSEIS CADASTRADAS!\n");
                return cidade;
            }

            cidade->listaMisseis[cidade->qtdMissil] = LeMissil();
            cidade->qtdMissil++;
        }
    }

    return cidade;
}

/**
 * @brief Imprime as informações da cidade.
 * 
 * @param cidade Ponteiro para a cidade que será impressa.
 */
// void ImprimeCidade(tCidade cidade);

/**
 * @brief Libera a memória alocada para a cidade.
 * 
 * @param cidade Ponteiro para a cidade que terá a memória liberada.
 */
void LiberaCidade(tCidade cidade){

    for (int i=0; i<cidade->qtdDefesa; i++){
    LiberaDefesa(cidade->listaDefesas[i]);
    }
    free(cidade->listaDefesas);

    for (int i=0; i<cidade->qtdMissil; i++){
        LiberaMissil(cidade->listaMisseis[i]);
    }
    free(cidade->listaMisseis);

    free(cidade->nome);
    
    free(cidade);
}

/**
 * @brief Processa os ataques na cidade na ordem em que foram cadastrados.
 * 
 * @param cidade Ponteiro para a cidade que será atacada.
 */
void ProcessaAtaques(tCidade cidade){

    for (int i=0; i<cidade->qtdMissil; i++){
        float xM = GetMissilX(cidade->listaMisseis[i]);
        float yM = GetMissilY(cidade->listaMisseis[i]);

        if ((xM > 0 && xM < cidade->x) && (yM > 0 && yM < cidade->y)){

            cidade->danoTotal += GetMissilPoder(cidade->listaMisseis[i]);
            
            for (int j=0; j<cidade->qtdDefesa; j++){
                if (VerificaSeDentroArea(cidade->listaDefesas[j], xM, yM) && PodeDefender(cidade->listaDefesas[j])){
                    ReduzPoder(cidade->listaMisseis[i], GetDefesaPoder(cidade->listaDefesas[j]));
                    UsaDefesa(cidade->listaDefesas[j]);
                }   
            }
            cidade->danoRecebido += GetMissilPoder(cidade->listaMisseis[i]);
        }
    }
}

/**
 * @brief Imprime o relatório final na saída padrão, sem processar ataques.
 * 
 * @param cidade Ponteiro para a cidade que terá os dados impressos.
 */
void ImprimeDados(tCidade cidade){

    for (int i=0; i<cidade->qtdDefesa; i++){
        ImprimeDefesa(cidade->listaDefesas[i]);
    }
    for (int i=0; i<cidade->qtdMissil; i++){
        ImprimeMissil(cidade->listaMisseis[i]);
    }
    float efetividade = ((cidade->danoTotal - cidade->danoRecebido) / cidade->danoTotal) * 100;
    printf("Efetividade: %.2f%%\n",efetividade);
}