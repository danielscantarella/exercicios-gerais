#include <stdlib.h>
#include <stdio.h>
#include "tadgen.h"

struct generic{
    Type type;
    int numElem;
    void *vet;
};

/**
 * @brief Cria uma estrutura genérica e dinâmica que pode armazenar tanto inteiros quanto floats
 *
 * @param type - Tipo do vetor genérico. Segue o Enum definido acima.
 * @param numElem A quantidade de elementos que serão armazenados no vetor
 *
 * @return O vetor genérico
 */
tGeneric* CriaGenerico(Type type, int numElem){
    tGeneric *g = (tGeneric*) calloc (1, sizeof(struct generic));
    g->type = type;
    g->numElem = numElem;
    if (type == INT){
        g->vet = calloc(numElem, sizeof(int));
    } else {
        g->vet = calloc(numElem, sizeof(float));
    }
    return g;
}

/**
 * @brief Destroi o vetor genérico (libera a memória alocada dinamicamente)
 *
 * @param gen - O vetor genérico que terá seu conteúdo liberado/destruído
 */
void DestroiGenerico(tGeneric* gen){
    free (gen->vet);
    free (gen);
}

/**
 * @brief Lê o conteúdo do vetor genérico e salva no local adequado
 *
 * @param gen - O vetor genérico que terá seu conteúdo preenchido/lido
 */
void LeGenerico(tGeneric* gen){

    printf("\nDigite o vetor: ");
    for (int i=0; i<gen->numElem; i++){
        if (gen->type == INT){
            scanf(" %d", &((int *)gen->vet)[i]);

        } else {
            scanf(" %f", &((float *)gen->vet)[i]);
        }
    }

}

/**
 * @brief Busca uma conta na agencia que possui um id específico
 *
 * @param gen - O vetor genérico que terá seu conteúdo impresso em tela
 */
void ImprimeGenerico(tGeneric* gen){
    printf("\n");
    for (int i=0; i<gen->numElem; i++){
        if (gen->type == INT){
            printf("%d ", ((int *)gen->vet)[i]);

        } else {
            printf("%.2f ", ((float *)gen->vet)[i]);
        }
    }
    printf("\n");
}
