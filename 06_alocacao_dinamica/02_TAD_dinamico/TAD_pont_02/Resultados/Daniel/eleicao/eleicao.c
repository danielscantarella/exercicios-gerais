#include <stdio.h>
#include <stdlib.h>
#include "eleicao.h"

/**
 * @brief Inicializa uma eleição com valores padrão (zerando as variáveis que armazenam votos).
 * Ainda nessa função, é lido a quantidade de candidatos e os candidatos são lidos e armazenados
 * A memória necessária para os vetores "presidentes", "governadores" deve ser alocada aqui.
 * Demais ponteiros devem ser inicializado com NULL.
 * @return Eleição inicializada.
 */
tEleicao* InicializaEleicao(){
    tEleicao *eleicao = (tEleicao *) malloc (sizeof(tEleicao));

    eleicao->presidentes = (tCandidato**) malloc (sizeof(tCandidato*));
    eleicao->totalPresidentes = 0;

    eleicao->governadores = (tCandidato**) malloc (sizeof(tCandidato*));
    eleicao->totalGovernadores = 0;

    eleicao->eleitores = (tEleitor**) malloc (sizeof(tEleitor*));
    eleicao->totalEleitores = 0;

    eleicao->votosBrancosGovernador = 0;
    eleicao->votosBrancosPresidente = 0;

    eleicao->votosNulosGovernador = 0;
    eleicao->votosNulosPresidente = 0;
}


void ApagaEleicao(tEleicao* eleicao){
    for (int i=0; i < eleicao->totalEleitores; i++){
        ApagaEleitor(eleicao->eleitores[i]);
    }
    ApagaEleitor(eleicao->eleitores);

    for (int i=0; i < eleicao->totalGovernadores; i++){
        ApagaCandidato(eleicao->governadores[i]);
    }
    ApagaCandidato(eleicao->governadores);

    for (int i=0; i < eleicao->totalPresidentes; i++){
        ApagaCandidato(eleicao->presidentes[i]);
    }
    ApagaCandidato(eleicao->presidentes);

    free(eleicao);
}

/**
 * @brief Realiza uma eleição.
 * Nessa função, é lido a quantidade de eleitores e os eleitores são lidos e armazenados.
 * @param eleicao Eleição a ser realizada. 
 */
void RealizaEleicao(tEleicao* eleicao){

    scanf("%d\n", &eleicao->totalEleitores);

    eleicao->eleitores = (tEleitor**) realloc (eleicao->eleitores, eleicao->totalEleitores * sizeof(tEleitor*));
    for (int i=0; i<eleicao->totalEleitores; i++){
        LeEleitor(eleicao->eleitores[i]);
    }
}

/**
 * @brief Imprime o resultado da eleição na tela a partir da aparucao dos votos.
 * @param eleicao Eleição a ser impressa.
 */
void ImprimeResultadoEleicao(tEleicao* eleicao){

    for (int i=0; i<eleicao->totalGovernadores; i++){
        for (int j=0; j<eleicao->totalEleitores; j++){

            if (ObtemVotoPresidente(eleicao->eleitores[j]) == 0){
                eleicao->votosBrancosGovernador++;

            } else if (VerificaIdCandidato(eleicao->governadores[i], ObtemVotoGovernador(eleicao->eleitores[j]))){
                IncrementaVotoCandidato(eleicao->governadores[j]);

            } else eleicao->votosNulosGovernador++;
        }
    }

    for (int i=0; i<eleicao->totalPresidentes; i++){
        for (int j=0; j<eleicao->totalEleitores; j++){

            if (ObtemVotoPresidente(eleicao->eleitores[j]) == 0){
                eleicao->votosBrancosPresidente++;

            } else if (VerificaIdCandidato(eleicao->presidentes[i], ObtemVotoPresidente(eleicao->eleitores[j]))){
                IncrementaVotoCandidato(eleicao->presidentes[j]);

            } else eleicao->votosNulosPresidente++;
        }
    }


}