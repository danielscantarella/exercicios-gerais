#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "franquia.h"

#define MAX_CONF 6
#define MAX_NOME 33
/**
 * @brief Estrutura que representa uma franquia.
 * 
 * A estrutura franquia contém informações sobre o nome da franquia, sua conferência e seu desempenho em casa e fora.
 * 
 */
struct Franquia{
    char nome[MAX_NOME];
    char conferencia[MAX_CONF];
    int vCasa, vFora;
    int dCasa, dFora;
};

/**
 * @brief Lê uma franquia da entrada padrão e retorna um ponteiro para ela.
 *
 * Esta função lê apenas as informaçoes de uma franquia: o nome do time e a conferência (LESTE ou OESTE). 
 * Ou seja, ela não é responsável por ler o caractere 'F' da entrada padrão.
 * A franquia começa sem vitórias e sem derrotas.
 *
 * @return tFranquia* Ponteiro para a franquia lida (alocada dinamicamente). 
 */
tFranquia* LeFranquia(){
    tFranquia *f = (tFranquia*) malloc (sizeof(struct Franquia));
    scanf("%s %s\n", f->nome, f->conferencia);
    f->dCasa = 0;
    f->dFora = 0;
    f->vCasa = 0;
    f->vFora = 0;
    return f;
}

/**
 * @brief Libera a memória alocada para uma franquia.
 *
 * @param f Ponteiro para a franquia a ser liberada.
 */
void LiberaFranquia(tFranquia* f){
    free(f);
}

/**
 * @brief Imprime as informações de uma franquia em uma linha, no formato
 * "NOME [CL] V D APR VC VF\n", onde [CL] é a conferência leste ([CO] para a oeste),
 * V e D são o total de vitórias e de derrotas, APR é o aproveitamento em %, um número
 * inteiro calculado com divisão inteira, (V * 100) / (V + D), ou seja, a parte fracionária
 * é descartada (0 se não jogou), VC são as vitórias em casa e VF as vitórias fora.
 * Ex.: "CELTICS [CL] 5 5 50 3 2\n"; com 2 vitórias e 1 derrota, APR = 66.
 *
 * @param f Ponteiro para a franquia a ser impressa.
 */
void ImprimeFranquia(tFranquia* f){
    int ap;
    if (f->vCasa+f->vFora+f->dCasa+f->dFora > 0){
        ap = ((f->vCasa+f->vFora) * 100) / (f->vCasa+f->vFora+f->dCasa+f->dFora);
    } else ap = 0;
    printf("%s ", f->nome);
    if (f->conferencia[0] == 'L'){
        printf("[CL] ");
    } else printf("[CO] ");
    printf("%d %d %d %d %d\n", (f->vCasa+f->vFora), (f->dCasa+f->dFora), ap, f->vCasa, f->vFora);
}

/**
 * @brief Retorna o nome da franquia.
 *
 * @param f Ponteiro para a franquia.
 * @return char* O nome da franquia.
 */
char * GetNomeFranquia(tFranquia* f){
    return f->nome;
}

/**
 * @brief Retorna a conferência da franquia.
 *
 * @param f Ponteiro para a franquia.
 * @return char* "LESTE" ou "OESTE".
 */
char * GetConferenciaFranquia(tFranquia* f){
    return f->conferencia;
}

/**
 * @brief Adiciona uma vitória em casa para a franquia.
 *
 * @param f Ponteiro para a franquia.
 */
void AdicionaVitoriaCasaFranquia(tFranquia* f){
    f->vCasa++;
}

/**
 * @brief Adiciona uma vitória fora de casa para a franquia.
 *
 * @param f Ponteiro para a franquia.
 */
void AdicionaVitoriaForaFranquia(tFranquia* f){
    f->vFora++;
}

/**
 * @brief Adiciona uma derrota em casa para a franquia.
 *
 * @param f Ponteiro para a franquia.
 */
void AdicionaDerrotaCasaFranquia(tFranquia* f){
    f->dCasa++;
}

/**
 * @brief Adiciona uma derrota fora de casa para a franquia.
 *
 * @param f Ponteiro para a franquia.
 */
void AdicionaDerrotaForaFranquia(tFranquia* f){
    f->dFora++;
}

/**
 * @brief Retorna o número de vitórias em casa da franquia.
 *
 * @param f Ponteiro para a franquia.
 * @return int Retorna o número de vitórias em casa da franquia.
 */
int GetVitoriaCasaFranquia(tFranquia* f){
    return f->vCasa;
}

/**
 * @brief Retorna o número de vitórias fora de casa da franquia.
 *
 * @param f Ponteiro para a franquia.
 * @return int Retorna o número de vitórias fora de casa da franquia.
 */
int GetVitoriaForaFranquia(tFranquia* f){
    return f->vFora;
}

/**
 * @brief Retorna o número de derrotas em casa da franquia.
 *
 * @param f Ponteiro para a franquia.
 * @return int Retorna o número de derrotas em casa da franquia.
 */
int GetDerrotaCasaFranquia(tFranquia* f){
    return f->dCasa;
}

/**
 * @brief Retorna o número de derrotas fora de casa da franquia.
 *
 * @param f Ponteiro para a franquia.
 * @return int Retorna o número de derrotas fora de casa da franquia.
 */
int GetDerrotaForaFranquia(tFranquia* f){
    return f->dFora;
}