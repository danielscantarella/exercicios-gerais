#include "gerenciadorpacotes.h"
#include <stdio.h>
#include <stdlib.h>

struct gerenciadorpacotes{
    tPacote **pacotes;
    int numPacotes;
};

/**
 * @brief Cria uma TAD que gerencia pacotes. O pacote é um TAD genérico.
 *
 *
 * @return O gerenciador de pacotes
 */
tGerenciador* CriaGerenciador(){
    tGerenciador *g = (tGerenciador *) malloc (sizeof(struct gerenciadorpacotes));
    g->pacotes = NULL;
    g->numPacotes = 0;
    return g;
}

/**
 * @brief Adiciona um pacote ao gerenciador de pacotes.
 *
 * @param geren O gerenciador de pacotes que armazenará o pacote 
 * @param pac O pacote que queremos adicionar no gerenciador.
 *
 */
void AdicionaPacoteNoGerenciador(tGerenciador* geren, tPacote* pac){
    int qtd = geren->numPacotes;

    if (geren->numPacotes == 0){
        geren->pacotes = (tPacote **) calloc (1, sizeof(tPacote*));
        geren->pacotes[qtd] = pac;
        geren->numPacotes++;

    } else {
        geren->pacotes = (tPacote **) realloc (geren->pacotes, (qtd+1) * sizeof(tPacote*));
        geren->pacotes[qtd] = pac;
        geren->numPacotes++;
    }
}


/**
 * @brief Destrói um gerenciador de pacotes
 *
 * @param geren O gerenciador de pacotes que será destruído (memória liberada)
 *
 */
void DestroiGerenciador(tGerenciador* geren){
    for (int i=0; i<geren->numPacotes; i++){
        DestroiPacote(geren->pacotes[i]);
    }
    free(geren->pacotes);
    free(geren);
}

/**
 * @brief Imprime um pacote específico do gerenciador de pacotes.
 *
 * @param geren - O gerenciador de pacotes que terá um pacote impresso
 * @param idx - O índice do pacote a ser impresso (começa em zero!)
 *
 */
void ImprimirPacoteNoIndice(tGerenciador* geren, int idx){
    ImprimePacote(geren->pacotes[idx]);
}


/**
 * @brief Imprime todos os pacotes de um gerenciador de pacotes
 *
 * @param geren O gerenciador de pacotes que terá seus pacotes impressos
 *
 */
void ImprimirTodosPacotes(tGerenciador* geren){
    for (int i=0; i<geren->numPacotes; i++){
        ImprimePacote(geren->pacotes[i]);
    }
}