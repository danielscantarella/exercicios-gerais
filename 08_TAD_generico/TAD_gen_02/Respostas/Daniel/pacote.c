#include <stdio.h>
#include <stdlib.h>
#include "pacote.h"

struct pacote{
    int type;
    int numElementos;
    int soma;
    void *vet;
};

/**
 * @brief Cria uma estrutura genérica e dinâmica que pode armazenar um pacote a ser transmitido
 *
 * @param type - Tipo do vetor genérico. Segue o Enum definido acima.
 * @param numElem A quantidade de elementos que serão armazenados no vetor
 *
 * @return O vetor genérico
 */
tPacote* CriaPacote(Type type, int numElem){
    
    tPacote *p = (tPacote *) calloc (1, sizeof(struct pacote));
    p->soma = 0;
    p->numElementos = numElem;
    p->type = type;
    if (type == INT){
        p->vet = (int *) calloc (numElem, sizeof(int));
    } else p->vet = (char *) calloc (numElem + 1, sizeof(char));
    return p;
}

/**
 * @brief Destroi o vetor genérico (libera a memória alocada dinamicamente)
 *
 * @param pac - O vetor genérico que terá seu conteúdo liberado/destruído
 */
void DestroiPacote(tPacote* pac){
    free (pac->vet);
    free (pac);
}

/**
 * @brief Lê o conteúdo do vetor genérico e salva no local adequado
 *
 * @param pac - O vetor genérico que terá seu conteúdo preenchido/lido
 */
void LePacote(tPacote* pac){

    if (pac->type == CHAR){
        scanf("%[^\n]\n", ((char *)pac->vet));
    } else {
        for (int i=0; i<pac->numElementos; i++){
            scanf(" %d", &((int *)pac->vet)[i]);
        }
    }
}

/**
 * @brief Imprime na tela um pacote que possui um id específico com seu valor calculado
 *
 * @param pac - O vetor genérico que terá seu conteúdo impresso em tela
 */
void ImprimePacote(tPacote* pac){

    CalculaSomaVerificacaoPacote(pac);

    printf("%d ", pac->soma);
    if (pac->type == CHAR){

        for (int i=0; i<pac->numElementos; i++){
            printf("%c", ((char *)pac->vet)[i]);
        }
        printf("\n");

    } else {
        
        for (int i=0; i<pac->numElementos; i++){
            printf("%d ", ((int *)pac->vet)[i]);
        }
        printf("\n");
    }
}

/**
 * @brief Calcula a soma de verificacao de um pacote e a armazena internamente
 *
 * @param pac - O vetor genérico que terá sua soma de verificacao calculada
 */
void CalculaSomaVerificacaoPacote(tPacote* pac){

    for (int i = 0; i < pac->numElementos; i++){
        if (pac->type == CHAR)
            pac->soma += ((char *)pac->vet)[i];
        else
            pac->soma += ((int *)pac->vet)[i];
    }
}