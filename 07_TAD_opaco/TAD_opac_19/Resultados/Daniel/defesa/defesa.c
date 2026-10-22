#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "defesa.h"

/**
 * @brief Estrutura que representa uma defesa.
 * 
 * A estrutura tDefesa contém o tipo da defesa, as coordenadas do centro, o tamanho e o poder de defesa.
 * 
 */
struct defesa{
    char *nome;
    char tipo;
    float x;
    float y;
    float tamanho;
    float poder;
    int quantidade;
};

/**
 * @brief Lê a entrada do usuário e cria uma nova defesa.
 * 
 * @return tDefesa Ponteiro para a defesa criada.
 */
tDefesa LeDefesa(){
    tDefesa d = (tDefesa) malloc (sizeof(struct defesa));
    d->nome = (char*) malloc (MAX_TAM * sizeof(char));
    scanf("%s %f %f %c %f %f %d", d->nome, &d->x, &d->y, &d->tipo, &d->tamanho, &d->poder, &d->quantidade);
    return d;
}

/**
 * @brief Imprime as informações da defesa.
 * 
 * @param defesa Ponteiro para a defesa que será impressa.
 */
void ImprimeDefesa(tDefesa defesa){
    printf("D-%s: %d\n", defesa->nome, defesa->quantidade);
}

/**
 * @brief Libera a memória alocada para a defesa.
 * 
 * @param defesa Ponteiro para a defesa que terá a memória liberada.
 */
void LiberaDefesa(tDefesa defesa){
    free(defesa->nome);
    free(defesa);
}

/**
 * @brief Verifica se um ponto está dentro da área de defesa.
 * 
 * @param defesa Ponteiro para a defesa que será verificada.
 * @param x Coordenada x do ponto.
 * @param y Coordenada y do ponto.
 * @return int 1 se o ponto está dentro da área de defesa, 0 caso contrário.
 */
int VerificaSeDentroArea(tDefesa defesa, float x, float y){
    float dCirculo = sqrt(pow(x - defesa->x, 2) + pow (y - defesa->y, 2));
    if (defesa->tipo == CIRCULO){
        if ( dCirculo <= defesa->tamanho){
            return 1;
        } else return 0;

    } else if (defesa->tipo == QUADRADO){
        float lado = (defesa->tamanho * 2) / sqrt(2);
        float mLado = lado/2;
        if ((x > defesa->x - mLado) && (x < defesa->x + mLado) && (y > defesa->y - mLado) && (y < defesa->y + mLado)){
            return 1;
        } else return 0;

    }
}

/**
 * @brief Consome uma unidade de míssil da defesa.
 * 
 * @param defesa Ponteiro para a defesa que será usada.
 */
void UsaDefesa(tDefesa defesa){
    defesa->quantidade--;
}

/**
 * @brief Obtém o poder de defesa da defesa.
 * 
 * @param defesa Ponteiro para a defesa que terá o poder de defesa obtido.
 * @return float Poder de defesa da defesa.
 */
float GetDefesaPoder(tDefesa defesa){
    return defesa->poder;
}

/**
 * @brief Verifica exclusivamente se a quantidade de munição é maior que zero.
 * 
 * @param defesa Ponteiro para a defesa que será verificada.
 * @return int 1 se a defesa pode defender, 0 caso contrário.
 */
int PodeDefender(tDefesa defesa){
    if (defesa->quantidade > 0){
        return 1;
    } else return 0;
}