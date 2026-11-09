#include <stdlib.h>
#include <stdio.h>
#include "duelo.h"

/**
 * @brief Tipo opaco que representa um duelo (luta) entre duas cartas. O duelo deve guardar
 * pelo menos as seguintes informações: identificador do duelo, identificador da carta 1,
 * identificador da carta 2, atributo a ser comparado, se houve desempate (bool) e a
 * diferença (int) entre os valores do atributo comparado das duas cartas.
 */
struct Duelo{
    int id;
    int c1, c2;
    char atributo;;
    bool desempate;
    int dif;
};

/**
 * @brief Lê um duelo da entrada padrão.
 *
 * Assuma que o caractere 'L' já foi lido. Esta função lê o restante do cadastro,
 * que ocupa duas linhas: o identificador do duelo e, na linha seguinte, o ID da carta 1,
 * o ID da carta 2 e o atributo (MAGIA, FORCA ou FOGO).
 *
 * @return Ponteiro para o duelo lido.
 */
tDuelo* LeDuelo(){
    tDuelo *d = (tDuelo*) malloc (sizeof(struct Duelo));
    scanf("%d\n", &d->id);
    scanf("%d %d %c\n", &d->c1, &d->c2, &d->atributo);
    d->desempate = false;
    d->dif = 0;
    return d;
}

/**
 * @brief Libera a memória alocada para um duelo.
 * @param d Ponteiro para o duelo a ser liberado.
 */
void LiberaDuelo(tDuelo* d){
    free(d);
}

/**
 * @brief Realiza um duelo entre duas cartas, comparando o atributo do duelo.
 *
 * Vence a carta com o maior valor no atributo. Em caso de empate, o duelo é marcado
 * como desempatado e vence a carta com o MENOR ID. 
 * A carta vencedora recebe uma vitória.
 * Esta função também calcula e guarda no duelo se houve desempate e a diferença
 * entre os valores do atributo comparado das duas cartas.
 *
 * @param d Ponteiro para o duelo.
 * @param c1 Ponteiro para a carta cujo ID é ObtemC1Duelo(d).
 * @param c2 Ponteiro para a carta cujo ID é ObtemC2Duelo(d).
 */
void RealizaDuelo(tDuelo* d, tCarta* c1, tCarta* c2){
    if (d->atributo == MAGIA){
        int result = ComparaMagiaCarta(c1, c2);
        if (result == 1){
            d->dif = ObtemMagiaCarta(c1) - ObtemMagiaCarta(c2);
            AdicionaVitoriaCarta(c1);
        } else if (result == -1){
            d->dif = ObtemMagiaCarta(c2) - ObtemMagiaCarta(c1);
            AdicionaVitoriaCarta(c2);
        } else {
            d->desempate = true;
            if (ComparaIdCarta(c1, c2) == 1){
                AdicionaVitoriaCarta(c2);
            } else if (ComparaIdCarta(c1, c2) == -1){
                AdicionaVitoriaCarta(c1);
            }
        }

    } else if (d->atributo == FORCA){
        int result = ComparaForcaCarta(c1, c2);
        if (result == 1){
            d->dif = ObtemForcaCarta(c1) - ObtemForcaCarta(c2);
            AdicionaVitoriaCarta(c1);
        } else if (result == -1){
            d->dif = ObtemForcaCarta(c2) - ObtemForcaCarta(c1);
            AdicionaVitoriaCarta(c2);
        } else {
            d->desempate = true;
            if (ComparaIdCarta(c1, c2) == 1){
                AdicionaVitoriaCarta(c2);
            } else if (ComparaIdCarta(c1, c2) == -1){
                AdicionaVitoriaCarta(c1);
            }
        }
        
    } else if (d->atributo == FOGO){
        int result = ComparaFogoCarta(c1, c2);
        if (result == 1){
            d->dif = ObtemFogoCarta(c1) - ObtemFogoCarta(c2);
            AdicionaVitoriaCarta(c1);
        } else if (result == -1){
            d->dif = ObtemFogoCarta(c2) - ObtemFogoCarta(c1);
            AdicionaVitoriaCarta(c2);
        } else {
            d->desempate = true;
            if (ComparaIdCarta(c1, c2) == 1){
                AdicionaVitoriaCarta(c2);
            } else if (ComparaIdCarta(c1, c2) == -1){
                AdicionaVitoriaCarta(c1);
            }
        }
        
    }
}

/**
 * @brief Retorna o ID da primeira carta do duelo.
 * @param d Ponteiro para o duelo.
 * @return Retorna o ID da primeira carta do duelo.
 */
int ObtemC1Duelo(tDuelo* d){
    return d->c1;
}

/**
 * @brief Retorna o ID da segunda carta do duelo.
 * @param d Ponteiro para o duelo.
 * @return Retorna o ID da segunda carta do duelo.
 */
int ObtemC2Duelo(tDuelo* d){
    return d->c2;
}

/**
 * @brief Retorna se houve desempate no duelo.
 * @param d Ponteiro para o duelo.
 * @return true se as cartas empataram no atributo comparado e false caso contrário.
 */
bool ObtemDesempateDuelo(tDuelo* d){
    return d->desempate;
}

/**
 * @brief Retorna a diferença de pontos entre as cartas no duelo para o atributo comparado.
 * @param d Ponteiro para o duelo.
 * @return O módulo da diferença entre os valores do atributo comparado das duas cartas.
 */
int ObtemDiferencaDuelo(tDuelo* d){
    return d->dif;
}

/**
 * @brief Retorna o ID do duelo.
 * @param d Ponteiro para o duelo.
 * @return Retorna o ID do duelo.
 */
int ObtemIdDuelo(tDuelo* d){
    return d->id;
}