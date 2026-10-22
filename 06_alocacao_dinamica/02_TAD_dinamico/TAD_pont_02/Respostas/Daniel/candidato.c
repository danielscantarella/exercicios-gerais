#include "candidato.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Cria um candidato "vazio".
 * Os ponteiros devem ser inicializados com NULL e os campos numéricos com o valor -1.
 * @return Candidato criado.
 */
tCandidato* CriaCandidato(){
    tCandidato *c = (tCandidato*) malloc (sizeof(tCandidato));
    c->nome = NULL;
    c->partido = NULL;
    c->cargo = -1;
    c->id = -1;
    c->votos = -1;
    return c;
}

/**
 * @brief Apaga toda a memória alocada dinamicamente para guardar as informações de um candidato
 * @param candidato Ponteiro para o candidato que terá a memória desalocada
 * @return Candidato criado.
 */
void ApagaCandidato(tCandidato* candidato){
    free(candidato->nome);
    free(candidato->partido);
    free(candidato);
}

/**
 * @brief Lê um candidato. O número de votos de um candidato deve ser zerado aqui.
 * @param candidato Candidato a ser lido.
 */
void LeCandidato(tCandidato *candidato){

    free(candidato->nome);
    free(candidato->partido);
    
    int tamInicial = 10, incremento = 10;
    candidato->nome = (char*) malloc ((tamInicial + 1) * sizeof(char));
    candidato->partido = (char*) malloc ((tamInicial + 1) * sizeof(char));

    char c;
    int i=0;
    int tamNome = tamInicial;

    scanf(" ");

    while (scanf("%c", &c) == 1 && c != ','){
        candidato->nome[i] = c;
        if (i >= tamNome-1){
            candidato->nome = (char*) realloc (candidato->nome, (tamNome + incremento + 1) * sizeof(char));
            tamNome += incremento;
        }
        i++;
    }
    candidato->nome[i] = '\0';

    scanf(" ");

    int tamPartido = tamInicial;
    i = 0;
    while (scanf("%c", &c) == 1 && c != ','){
        candidato->partido[i] = c;
        if (i >= tamPartido-1){
            candidato->partido = (char*) realloc (candidato->partido, (tamPartido + incremento + 1) * sizeof(char));
            tamPartido += incremento;
        }
        i++;
    }
    candidato->partido[i] = '\0';

    scanf(" %c, %d", &candidato->cargo, &candidato->id);

    candidato->votos = 0;

}

/**
 * @brief Verifica se o identificador do candidato é igual ao informado.
 * @param candidato Candidato a ser verificado.
 * @param id Identificador a ser comparado.
 * @return 1 se o identificador é igual, 0 caso contrário.
 */
int VerificaIdCandidato(tCandidato *candidato, int id){
    if (candidato->id == id){
        return 1;
    } else return 0;
}

/**
 * @brief Verifica se dois candidatos são iguais (dica: utilize essa função para verificar se houve empate).
 * @param candidato1 Primeiro candidato a ser comparado.
 * @param candidato2 Segundo candidato a ser comparado.
 * @return 1 se os candidatos são iguais, 0 caso contrário.
 */
int EhMesmoCandidato(tCandidato *candidato1, tCandidato *candidato2){
    if (candidato1->id == candidato2->id){
        return 1;
    } else return 0;
}

/**
 * @brief Obtém o cargo do candidato.
 * @param candidato Candidato a ser verificado.
 * @return Cargo do candidato.
 */
char ObtemCargo(tCandidato* candidato){
    return candidato->cargo;
}

/**
 * @brief Incrementa 1 voto ao candidato.
 * @param candidato Candidato a ter os votos incrementados.
 */
void IncrementaVotoCandidato(tCandidato* candidato){
    candidato->votos++;
}

/**
 * @brief Obtém a quantidade de votos do candidato.
 * @param candidato Candidato a ser verificado.
 * @return Quantidade de votos do candidato.
 */
int ObtemVotos(tCandidato* candidato){
    return candidato->votos;
}

/**
 * @brief Calcula o percentual de votos do candidato em relação ao total de votos (do mesmo cargo).
 * @param candidato Candidato a ser verificado.
 * @param totalVotos Total de votos da eleição.
 * @return Percentual de votos do candidato.
 */
float CalculaPercentualVotos(tCandidato* candidato, int totalVotos){

    if (totalVotos == 0) return 0;

    float votoC = candidato->votos;
    return (votoC / totalVotos) * 100;
}

/**
 * @brief Imprime os dados do candidato na tela.
 * @param candidato Candidato a ser impresso.
 * @param percentualVotos Percentual de votos do candidato.
 */
void ImprimeCandidato (tCandidato* candidato, float percentualVotos){
    printf("%s (%s), %d voto(s), %.2f%%\n", candidato->nome, candidato->partido,candidato->votos, percentualVotos);
}