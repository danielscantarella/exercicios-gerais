#include <stdio.h>
#include <stdlib.h>
#include "carta.h"


/**
 * @brief Tipo opaco que representa uma carta: identificador, nome, poderes de magia,
 * força e fogo, e número de vitórias.
 */
struct Carta{
    int id;
    int magia, forca, fogo;
    int qtdVitorias;
    char nome[MAX_NOME];
};

/**
 * @brief Lê uma carta da entrada padrão e retorna um ponteiro para ela.
 *
 * Assuma que o caractere 'C' já foi lido. Esta função lê o restante das informações da carta,
 * que ocupa três linhas: o identificador, o nome (pode conter espaços) e os poderes de magia, força e fogo, nesta ordem. 
 * A carta começa com zero vitórias.
 *
 * @return Ponteiro para a carta lida.
 */
tCarta* LeCarta(){
    tCarta *c = (tCarta*) malloc (sizeof(struct Carta));
    scanf("%d\n", &c->id);
    scanf("%[^\n]\n", c->nome);
    scanf("%d %d %d\n", &c->magia, &c->forca, &c->fogo);
    c->qtdVitorias = 0;
    return c;
}

/**
 * @brief Libera a memória alocada para uma carta.
 * @param c Ponteiro para a carta a ser liberada.
 */
void LiberaCarta(tCarta* c){
    free(c);
}

/**
 * @brief Retorna o ID de uma carta.
 * @param c Ponteiro para a carta.
 * @return Retorna o ID da carta.
 */
int ObtemIdCarta(tCarta* c){
    return c->id;
}

/**
 * @brief Retorna o nome de uma carta.
 * @param c Ponteiro para a carta.
 * @return O nome da carta (a string pertence à carta; não a libere).
 */
char * ObtemNomeCarta(tCarta* c){
    return c->nome;
}

/**
 * @brief Retorna o número de vitórias de uma carta.
 * @param c Ponteiro para a carta.
 * @return Retorna o número de vitórias da carta.
 */
int ObtemNumVitCarta(tCarta* c){
    return c->qtdVitorias;
}

/**
 * @brief Retorna o valor de magia de uma carta.
 * @param c Ponteiro para a carta.
 * @return Retorna o valor de magia da carta.
 */
int ObtemMagiaCarta(tCarta* c){
    return c->magia;
}

/**
 * @brief Retorna o valor de força de uma carta.
 * @param c Ponteiro para a carta.
 * @return Retorna o valor de força da carta.
 */
int ObtemForcaCarta(tCarta* c){
    return c->forca;
}

/**
 * @brief Retorna o valor de fogo de uma carta.
 * @param c Ponteiro para a carta.
 * @return Retorna o valor de fogo da carta.
 */
int ObtemFogoCarta(tCarta* c){
    return c->fogo;
}

/**
 * @brief Verifica se uma carta é válida: nenhum dos três poderes é maior que 30 e a
 * soma dos três não é maior que 80.
 * @param c Ponteiro para a carta.
 * @return Retorna true se a carta é válida e false caso contrário.
 */
bool EhCartaValida(tCarta* c){
    if (c->fogo <= 30 && c->forca <= 30 && c->magia <= 30 && (c->fogo+c->forca+c->magia) <= 80){
        return true;
    } else return false;
}

/**
 * @brief Verifica se duas cartas possuem o mesmo ID.
 * @param c1 Ponteiro para a primeira carta.
 * @param c2 Ponteiro para a segunda carta.
 * @return Retorna true se as cartas possuem o mesmo ID e false caso contrário.
 */
bool EhMesmoIdCarta(tCarta* c1, tCarta* c2){
    if (c1->id == c2->id) {
        return true;
    } else return false;
}

/*
 * As funções Compara*Carta abaixo comparam um valor inteiro das duas cartas e retornam
 * exatamente: -1 se o valor de c1 for menor que o de c2, 0 se forem iguais e 1 se o
 * valor de c1 for maior que o de c2.
 */

/**
 * @brief Compara duas cartas pelo ID.
 * @param c1 Ponteiro para a primeira carta.
 * @param c2 Ponteiro para a segunda carta.
 * @return -1 se o ID de c1 for menor que o de c2, 0 se forem iguais
 *         e 1 se o ID de c1 for maior que o de c2.
 */
int ComparaIdCarta(tCarta* c1, tCarta* c2){
    if (c1->id > c2->id){
        return 1;
    } else if (c1->id < c2->id){
        return -1;
    } else return 0;
}

/**
 * @brief Compara duas cartas pelo valor de magia.
 * @param c1 Ponteiro para a primeira carta.
 * @param c2 Ponteiro para a segunda carta.
 * @return -1 se a magia de c1 for menor que a de c2, 0 se forem iguais
 *         e 1 se a magia de c1 for maior que a de c2.
 */
int ComparaMagiaCarta(tCarta* c1, tCarta* c2){
    if (c1->magia > c2->magia){
        return 1;
    } else if (c1->magia < c2->magia){
        return -1;
    } else return 0;
}

/**
 * @brief Compara duas cartas pelo valor de força.
 * @param c1 Ponteiro para a primeira carta.
 * @param c2 Ponteiro para a segunda carta.
 * @return -1 se a força de c1 for menor que a de c2, 0 se forem iguais
 *         e 1 se a força de c1 for maior que a de c2.
 */
int ComparaForcaCarta(tCarta* c1, tCarta* c2){
    if (c1->forca > c2->forca){
        return 1;
    } else if (c1->forca < c2->forca){
        return -1;
    } else return 0;
}

/**
 * @brief Compara duas cartas pelo valor de fogo.
 * @param c1 Ponteiro para a primeira carta.
 * @param c2 Ponteiro para a segunda carta.
 * @return -1 se o fogo de c1 for menor que o de c2, 0 se forem iguais
 *         e 1 se o fogo de c1 for maior que o de c2.
 */
int ComparaFogoCarta(tCarta* c1, tCarta* c2){
    if (c1->fogo > c2->fogo){
        return 1;
    } else if (c1->fogo < c2->fogo){
        return -1;
    } else return 0;
}

/**
 * @brief Adiciona uma vitória para uma carta.
 * @param c Ponteiro para a carta.
 * @return Retorna o novo número de vitórias da carta.
 */
int AdicionaVitoriaCarta(tCarta* c){
    c->qtdVitorias++;
    return c->qtdVitorias;
}