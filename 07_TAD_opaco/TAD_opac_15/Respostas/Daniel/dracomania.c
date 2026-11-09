#include <stdio.h>
#include <stdlib.h>
#include "dracomania.h"
#include "carta.h"
#include "duelo.h"

/**
 * @brief Tipo opaco que representa o jogo: as cartas cadastradas, os duelos realizados e
 * a quantidade de cartas descartadas. Não há limite para a quantidade de cartas ou de duelos 
 * (os vetores devem crescer conforme a necessidade).
 */
struct Dracomania{
    tCarta **Cartas;
    tDuelo **duelos;
    int qtdCartas, qtdDuelos;
    int qtdDescartada;
    int qtdDesempates;
    tCarta *vitoriosa;
    tDuelo *maiorDif;
};


/**
 * @brief Cria um jogo vazio (sem cartas, sem duelos e sem descartes).
 * Todos os campos da estrutura devem ser inicializados aqui. 
 * 
 * @return Ponteiro para o jogo criado.
 */
tDracomania* CriaDracomania(){
    tDracomania *d = (tDracomania*) malloc (sizeof(struct Dracomania));
    d->Cartas = NULL;
    d->duelos = NULL;
    d->vitoriosa = NULL;
    d->maiorDif = NULL;
    d->qtdDescartada = 0;
    d->qtdCartas = 0;
    d->qtdDuelos = 0;
    d->qtdDesempates = 0;
    return d;
}

tCarta* BuscaCartaPorId(tDracomania* d, int id){
    for (int i = 0; i < d->qtdCartas; i++){
        if (ObtemIdCarta(d->Cartas[i]) == id) return d->Cartas[i];
    }
    return NULL;
}

/**
 * @brief Lê toda a entrada padrão até o caractere FINALIZAR, cadastrando cartas e
 * realizando duelos.
 *
 * Esta função lê o caractere de cada operação (CADASTRAR ou LUTAR) e chama LeCarta ou
 * LeDuelo para ler o restante. Regras:
 * - carta inválida: é descartada e conta como descartada;
 * - carta válida com um ID que já existe: substitui a carta antiga, na mesma posição
 *   da lista (a antiga é liberada);
 * - carta inválida com um ID que já existe: a carta antiga é mantida e a nova conta
 *   como descartada;
 * - os duelos sempre são entre duas cartas já cadastradas.
 * O jogo passa a ser responsável por liberar as cartas e os duelos guardados.
 *
 * @param d Ponteiro para o jogo.
 */
void RodaDracomania(tDracomania* d){

    while (1){

        char op;
        scanf("%c\n", &op);

        if (op == FINALIZAR){
            break;
        }

        if (op == CADASTRAR){

            if (d->qtdCartas == 0){

                free(d->Cartas);
                d->Cartas = (tCarta**) malloc (sizeof(struct Carta*));
                d->Cartas[d->qtdCartas] = LeCarta();
                if (EhCartaValida(d->Cartas[d->qtdCartas])){
                    d->qtdCartas++;
                } else {
                    d->qtdDescartada++;
                    LiberaCarta(d->Cartas[d->qtdCartas]);
                }

            } else {

                tCarta *c = LeCarta();

                if (EhCartaValida(c)){
                    
                    int pos = -1;
                    for (int i = 0; i < d->qtdCartas; i++){
                        if (EhMesmoIdCarta(c, d->Cartas[i])){
                            pos = i;
                            break;
                        }
                    }

                    if (pos != -1){
        
                        LiberaCarta(d->Cartas[pos]);
                        d->Cartas[pos] = c;
                    } else {
                    
                        d->Cartas = (tCarta**) realloc(d->Cartas, (d->qtdCartas + 1) * sizeof(tCarta*));
                        d->Cartas[d->qtdCartas] = c;
                        d->qtdCartas++;
                    }

                } else{
                    LiberaCarta(c);
                    d->qtdDescartada++;
                }
            }
        }

        if (op == LUTAR){

            if (d->qtdDuelos == 0){

                free(d->duelos);
                d->duelos = (tDuelo**) malloc (sizeof(struct Duelo*));

                d->duelos[d->qtdDuelos] = LeDuelo();
                tCarta *c1 = BuscaCartaPorId(d, ObtemC1Duelo(d->duelos[d->qtdDuelos]));
                tCarta *c2 = BuscaCartaPorId(d, ObtemC2Duelo(d->duelos[d->qtdDuelos]));
                RealizaDuelo(d->duelos[d->qtdDuelos], c1, c2);
                if (ObtemDesempateDuelo(d->duelos[d->qtdDuelos])) d->qtdDesempates++;
                d->qtdDuelos++;

            } else {

                d->duelos = (tDuelo**) realloc (d->duelos , (d->qtdDuelos+1) * sizeof(struct Duelo*));

                d->duelos[d->qtdDuelos] = LeDuelo();
                tCarta *c1 = BuscaCartaPorId(d, ObtemC1Duelo(d->duelos[d->qtdDuelos]));
                tCarta *c2 = BuscaCartaPorId(d, ObtemC2Duelo(d->duelos[d->qtdDuelos]));
                RealizaDuelo(d->duelos[d->qtdDuelos], c1, c2);
                if (ObtemDesempateDuelo(d->duelos[d->qtdDuelos])) d->qtdDesempates++;
                d->qtdDuelos++;
            }
        }

    }
}

/**
 * @brief Imprime o relatório final do jogo, uma informação por linha:
 *     Quantidade de Cartas: <cartas cadastradas>
 *     Quantidade de descartadas: <cartas descartadas>
 *     Quantidade de lutas: <duelos realizados>
 * Se houve pelo menos um duelo, imprime também:
 *     Lutas que foram desempatadas: <duelos decididos pelo menor ID>
 *     Carta mais vitoriosa: <nome da carta com mais vitórias>
 *     Luta com Maior Diferenca: <ID do duelo com a maior diferença>
 * Empates: a carta mais vitoriosa é a primeira na ordem de cadastro e a luta com maior
 * diferença é a primeira na ordem em que os duelos foram realizados.
 * @param d Ponteiro para o jogo.
 */
void ImprimeRelatorioDracomania(tDracomania* d){

    for (int i=0; i<d->qtdCartas; i++){

        if (i == 0){
            d->vitoriosa = d->Cartas[i];

        } else {
            if (ObtemNumVitCarta(d->Cartas[i]) > ObtemNumVitCarta(d->vitoriosa)){
                d->vitoriosa = d->Cartas[i];
            }
        }
    }

    for (int i=0; i<d->qtdDuelos; i++){

        if (i == 0){
            d->maiorDif = d->duelos[i];

        } else {
            if (ObtemDiferencaDuelo(d->duelos[i]) > ObtemDiferencaDuelo(d->maiorDif)){
                d->maiorDif = d->duelos[i];
            }
        }
    }

    printf("Quantidade de Cartas: %d\n", d->qtdCartas);
    printf("Quantidade de descartadas: %d\n", d->qtdDescartada);
    printf("Quantidade de lutas: %d\n", d->qtdDuelos);
    if (d->qtdDuelos > 0){
        printf("Lutas que foram desempatadas: %d\n", d->qtdDesempates);
        printf("Carta mais vitoriosa: %s\n", ObtemNomeCarta(d->vitoriosa));
        printf("Luta com Maior Diferenca: %d\n", ObtemIdDuelo(d->maiorDif));
    }
}
/**
 * @brief Libera a memória alocada para o jogo, inclusive as cartas e os duelos.
 * @param d Ponteiro para o jogo.
 */
void LiberaDracomania(tDracomania* d){

    for (int i=0; i<d->qtdCartas; i++){
        LiberaCarta(d->Cartas[i]);
    }
    free(d->Cartas);

    for (int i=0; i<d->qtdDuelos; i++){
        LiberaDuelo(d->duelos[i]);
    }
    free(d->duelos);

    free(d);
}