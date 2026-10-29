#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "partida.h"

/**
 * @brief Tipo opaco que representa uma partida: os dois times e os pontos de cada um.
 */
struct Partida{
    char t1[MAX_NOME];
    char t2[MAX_NOME];
    int p1, p2;
    int vencedor;
};

/**
 * @brief Lê uma partida da entrada padrão.
 *
 * Esta função lê apenas informações de uma partida: o time visitante (fora de casa), o caractere '@', 
 * o time da casa, os pontos do visitante e os pontos do time da casa.
 *
 * @return tPartida* Ponteiro para a partida lida (alocado dinamicamente).
 */
tPartida* LePartida(){
    tPartida *p = (tPartida*) malloc (sizeof(struct Partida));
    scanf("%s @ %s %d %d", p->t1, p->t2, &p->p1, &p->p2);
    if (p->p1 > p->p2){
        p->vencedor = TIME_FORA;
    } else p->vencedor = TIME_CASA;
    return p;
}

/**
 * @brief Libera a memória alocada para uma partida.
 *
 * @param p Ponteiro para a partida a ser liberada.
 */
void LiberaPartida(tPartida* p){
    free(p);
}

/**
 * @brief Retorna o nome do time da casa.
 *
 * @param p Ponteiro para a partida.
 * @return char* O nome do time da casa.
 */
char * GetTimeCasaPartida(tPartida* p){
    return p->t2;
}

/**
 * @brief Retorna o nome do time visitante.
 *
 * @param p Ponteiro para a partida.
 * @return char* O nome do time visitante.
 */
char * GetTimeForaPartida(tPartida* p){
    return p->t1;
}

/**
 * @brief Retorna o vencedor da partida (o time que fez mais pontos; não há empate).
 *
 * @param p Ponteiro para a partida.
 * @return int TIME_CASA se o time da casa venceu, TIME_FORA caso contrário.
 */
int GetVencedorPartida(tPartida* p){
    return p->vencedor;
}