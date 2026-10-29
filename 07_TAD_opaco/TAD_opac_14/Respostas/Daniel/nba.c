#include "nba.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "franquia.h"
#include "partida.h"


/**
 * @brief Tipo opaco que representa o campeonato: as franquias e as partidas cadastradas.
 * Não há limite para a quantidade de franquias ou de partidas 
 * (os vetores devem crescer conforme a necessidade).
 */
struct Nba{
    tFranquia **franquia;
    tPartida **partida;
    int numFranquias, numPartidas;
};

/**
 * @brief Cria um campeonato vazio (sem franquias e sem partidas).
 *
 * Todos os campos da estrutura devem ser inicializados aqui. Em particular, as listas
 * (vetores de ponteiros) de franquias e de partidas começam vazias: o ponteiro de cada
 * lista deve valer NULL e a quantidade de elementos de cada lista deve valer 0.
 * Como realloc(NULL, tamanho) funciona como malloc(tamanho), a primeira inserção
 * pode usar realloc normalmente.
 *
 * @return tNBA* Ponteiro para o campeonato criado. 
 */
tNBA* CriaNBA(){
    tNBA *nba = (tNBA*) malloc (sizeof(struct Nba));
    nba->franquia = NULL;
    nba->partida = NULL;
    nba->numFranquias = 0;
    nba->numPartidas = 0;
    return nba;
}

tFranquia *ComparaNome (tNBA *nba, char *nome){

    for (int i=0; i<nba->numFranquias; i++){
        if (strcmp(nome, GetNomeFranquia(nba->franquia[i])) == 0){
            return nba->franquia[i];
        }
    }
    return NULL;
}

void ComputaPartida (tNBA *nba, tPartida *p){
    tFranquia *t1 = ComparaNome(nba, GetTimeForaPartida(p));
    tFranquia *t2 = ComparaNome(nba, GetTimeCasaPartida(p));

    if (GetVencedorPartida(p) == 1){
        AdicionaVitoriaCasaFranquia(t2);
        AdicionaDerrotaForaFranquia(t1);
    } else {
        AdicionaVitoriaForaFranquia(t1);
        AdicionaDerrotaCasaFranquia(t2);
    }
}

/**
 * @brief Lê toda a entrada padrão, cadastrando as franquias e processando as partidas,
 * até ler o caractere ENCERRAR.
 *
 * Esta função lê o caractere de cada linha (CAD_FRANQUIA ou CAD_PARTIDA) e chama
 * LeFranquia ou LePartida para ler o restante da linha. Pode-se assumir que as partidas
 * só citam times já cadastrados. O campeonato passa a ser responsável por liberar as
 * franquias e as partidas lidas.
 *
 * @param nba Ponteiro para o campeonato.
 */
void RodaNBA(tNBA* nba){

    while(1){

        char op;

        scanf("%c ", &op);

        if (op == ENCERRAR){
            break;
        }

        if (op == CAD_FRANQUIA){

            if (nba->numFranquias == 0){
                free(nba->franquia);
                nba->franquia = (tFranquia**) malloc (sizeof(struct Franquia*));
                nba->franquia[nba->numFranquias] = LeFranquia();
                nba->numFranquias++;

            } else {
                nba->franquia = (tFranquia**) realloc (nba->franquia, (nba->numFranquias+1) * sizeof(struct Franquia*));
                nba->franquia[nba->numFranquias] = LeFranquia();
                nba->numFranquias++;
            }
        }

        if (op == CAD_PARTIDA){

            if (nba->numPartidas == 0){
                free(nba->partida);
                nba->partida = (tPartida**) malloc (sizeof(struct Partida*));
                nba->partida[nba->numPartidas] = LePartida();
                ComputaPartida(nba, nba->partida[nba->numPartidas]);
                nba->numPartidas++;

            } else {
                nba->partida = (tPartida**) realloc (nba->partida, (nba->numPartidas+1) * sizeof(struct Partida*));
                nba->partida[nba->numPartidas] = LePartida();
                ComputaPartida(nba, nba->partida[nba->numPartidas]);
                nba->numPartidas++;
            }
        }
    }
}

/**
 * @brief Imprime o relatório final do campeonato: uma linha por franquia, na ordem de
 * cadastro (ver ImprimeFranquia), seguida de uma linha para cada conferência, sempre
 * nesta ordem e mesmo que a conferência não tenha nenhum time:
 * "LESTE V D APR\n" e "OESTE V D APR\n" (V e D são as somas das vitórias e das derrotas
 * dos times da conferência e APR é o aproveitamento em %, inteiro, calculado como em
 * ImprimeFranquia: (V * 100) / (V + D) com divisão inteira, 0 se não houve jogos).
 *
 * @param nba Ponteiro para o campeonato.
 */
void ImprimeRelatorioNBA(tNBA* nba){
    for (int i=0; i<nba->numFranquias; i++){
        ImprimeFranquia(nba->franquia[i]);
    }

    int vLeste = 0, vOeste = 0;
    int dLeste = 0, dOeste = 0;
    for (int i=0; i<nba->numFranquias; i++){
        if (strcmp(GetConferenciaFranquia(nba->franquia[i]), "LESTE") == 0){
            vLeste += GetVitoriaCasaFranquia(nba->franquia[i]) + GetVitoriaForaFranquia(nba->franquia[i]);
            dLeste += GetDerrotaCasaFranquia(nba->franquia[i]) + GetDerrotaForaFranquia(nba->franquia[i]);
        } else {
            vOeste += GetVitoriaCasaFranquia(nba->franquia[i]) + GetVitoriaForaFranquia(nba->franquia[i]);
            dOeste += GetDerrotaCasaFranquia(nba->franquia[i]) + GetDerrotaForaFranquia(nba->franquia[i]);
        }
    }
    int apLeste = 0, apOeste = 0;
    if (vLeste + dLeste > 0){
        apLeste = (vLeste * 100) / (vLeste+dLeste);
    }
    if (vOeste + dOeste > 0){
        apOeste = (vOeste * 100) / (vOeste+dOeste);
    }
    printf("LESTE %d %d %d\n", vLeste, dLeste, apLeste);
    printf("OESTE %d %d %d\n", vOeste, dOeste, apOeste);
}

/**
 * @brief Libera a memória alocada para o campeonato, inclusive as franquias e as partidas.
 *
 * @param nba Ponteiro para o campeonato a ser liberado.
 */
void LiberaNBA(tNBA* nba){
    for (int i=0; i<nba->numFranquias; i++){
        LiberaFranquia(nba->franquia[i]);
    }
    free(nba->franquia);

    for (int i=0; i<nba->numPartidas; i++){
        LiberaPartida(nba->partida[i]);
    }
    free(nba->partida);

    free(nba);
}