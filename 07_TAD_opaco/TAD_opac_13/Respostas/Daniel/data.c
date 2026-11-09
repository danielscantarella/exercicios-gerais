#include <stdio.h>
#include <stdlib.h>
#include "data.h"

/**
 * @brief Tipo opaco que representa uma data que possui pelo menos os seguintes atributos:
 * dia, mês e ano.
 */
struct Data{
    int dia, mes, ano;
};

/**
 * @brief Cria uma data a partir do dia, mês e ano fornecidos.
 * Todos os campos da estrutura devem ser inicializados aqui.
 *
 * @param dia Dia da data.
 * @param mes Mês da data.
 * @param ano Ano da data.
 * @return tData* Ponteiro para a data criada.
 */
tData *criaData(int dia, int mes, int ano){
    tData *d = (tData*) malloc (sizeof(struct Data));
    d->dia = dia;
    d->mes = mes;
    d->ano = ano;
    return d;
}

/**
 * @brief Lê uma data no formato DD/MM/AAAA da entrada padrão.
 * A quebra de linha depois da data também é consumida.
 *
 * @return tData* Ponteiro para a data lida.
 */
tData *lerData(){
    int dia, mes, ano;
    scanf("%d/%d/%d\n", &dia, &mes, &ano);
    tData *d = criaData(dia, mes, ano);
    return d;
}

/**
 * @brief Função que calcula a diferença em anos entre duas datas. A diferença é calculada como o número de anos completos entre a data inicial e a data atual.
 * Ex: Se a data inicial for 15/08/2000 e a data atual for 14/08/2023, a diferença será 22 anos.
 *  
 * @param inicial: Data inicial.
 * @param atual: Data atual.
 * @return Diferença em anos entre as duas datas.
*/
int diferencaAnoData(tData *inicial, tData *atual){
    int anos = atual->ano - inicial->ano;

    if (atual->mes < inicial->mes ||
       (atual->mes == inicial->mes && atual->dia < inicial->dia)) {
        anos--;
    }
    return anos;
}

/**
 * @brief Imprime uma data no formato DD/MM/AAAA.
 *
 * @param d Ponteiro para a data a ser impressa.
 */
void imprimeData(tData *d){
    printf("%02d/%02d/%04d\n", d->dia, d->mes, d->ano);
}

/**
 * @brief Libera a memória de uma data.
 *
 * @param d Ponteiro para a data a ser liberada.
 */
void liberaData(tData *d){
    free(d);
}